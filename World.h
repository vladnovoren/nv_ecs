#pragma once

#include "Component/IComponentBucket.h"
#include <memory>
#include <unordered_set>
#include <cassert>
#include <vector>

class World {
public:
	Entity CreateEntity();

  void ScheduleEntityDeletion(Entity ent);

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

  void Update(float dt);

  bool IsAlive(Entity ent);

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

  void DeleteComponent(Entity ent, IdT comp);

  template<typename T>
  void DeleteComponent(Entity ent) {
    DeleteComponent(ent, TypeId<T>::Get());
  }

  void DeleteEntity(Entity ent);

  void DeleteScheduled();

private:
	std::unordered_set<IdT> entities_;
  std::unordered_map<Entity, std::unordered_set<IdT>> ents_to_comps_;
	IdT entity_counter_ = 0;

	std::unordered_map<IdT, std::shared_ptr<IComponentBucket>> comp_buckets_;

  std::unordered_set<Entity> to_die_list_;

};
