#pragma once

#include "Component/IComponentBucket.h"
#include <memory>
#include <unordered_set>
#include <cassert>
#include <vector>
#include "System/System.h"

class World {
public:
	Entity CreateEntity();

  void ScheduleEntityDeletion(Entity ent);

  template<typename T>
  T& GetComponent(Entity ent) {
    return GetCastedBucket<T>()->Get(ent);
  }

	template<typename T>
	void SetComponent(Entity ent, T&& comp) {
		assert(entities_.find(ent) != entities_.end());

		auto comp_id = TypeId<T>::Get();
		AddBucket<T>();
		auto bucket = GetCastedBucket<T>();
		bucket->Set(ent, std::forward<T>(comp));

    ents_to_comps_[ent].insert(comp_id);
	}

	template<typename T, typename... CompsT>
	bool HasComponents(Entity ent) {
		if constexpr (sizeof...(CompsT) == 0)
			return HasComponent<T>(ent);
		else
			return HasComponent<T>(ent) && HasComponents<CompsT...>(ent);
	}

  template<typename... CompsT>
  std::vector<Entity> Filter() {
    if constexpr (sizeof...(CompsT) == 0)
      return {entities_.begin(), entities_.end()};

    std::vector<Entity> res;
    for (auto ent : entities_) {
      if (HasComponents<CompsT...>(ent))
        res.emplace_back(ent);
    }

    return res;
  }

  void Update(float dt = 0);

  bool IsAlive(Entity ent);

  template<typename T, typename... ArgsT>
  void AddSystem(ArgsT&&... args) {
    systems_.emplace_back(std::make_unique<T>(std::forward<ArgsT>(args)...));
  }

private:

	template<typename T>
	bool HasComponent(Entity ent) {
		return BucketExists<T>() && GetCastedBucket<T>()->HasEntity(ent);
	}

	template<typename T>
	void AddBucket() {
		auto id = TypeId<T>::Get();
		if (!BucketExists<T>()) {
			comp_buckets_[id] = std::make_shared<ComponentBucket<T>>();
		}
	}

	template<typename T>
	bool BucketExists() const {
		auto id = TypeId<T>::Get();
		return comp_buckets_.find(id) != comp_buckets_.end();
	}

	template<typename T>
	auto GetCastedBucket() {
		return std::static_pointer_cast<ComponentBucket<T>>(comp_buckets_[TypeId<T>::Get()]);
	}

  void DeleteComponent(Entity ent, CompIdT comp);

  template<typename T>
  void DeleteComponent(Entity ent) {
    DeleteComponent(ent, TypeId<T>::Get());
  }

  void DeleteEntity(Entity ent);

  void DeleteScheduled();

private:
	std::unordered_set<Entity> entities_;
  std::unordered_map<Entity, std::unordered_set<CompIdT>> ents_to_comps_;
	Entity entity_counter_ = 0;

	std::unordered_map<CompIdT, std::shared_ptr<IComponentBucket>> comp_buckets_;

  std::unordered_set<Entity> to_die_list_;

  std::vector<std::unique_ptr<ISystem>> systems_;

};
