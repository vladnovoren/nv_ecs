#pragma once

#include "Component/IComponentBucket.h"
#include <memory>
#include <unordered_set>
#include <cassert>

class World {
public:
	IdT CreateEntity();

	template<typename T>
	void SetComponent(Entity ent, T&& comp) {
		assert(entities_.find(ent) != entities_.end());

		auto comp_id = TypeId<T>::Get();
		AddBucket<T>();
		auto bucket = GetCastedBucket<T>();
		bucket->Set(ent, std::forward<T>(comp));
	}

	template<typename T, typename... CompsT>
	bool HasComponents(Entity ent) {
		if constexpr (sizeof...(CompsT) == 0)
			return HasComponent<T>(ent);
		else
			return HasComponent<T>(ent) && HasComponents<CompsT...>(ent);
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

private:
	std::unordered_set<IdT> entities_;
	IdT entity_counter_ = 0;

	std::unordered_map<IdT, std::shared_ptr<IComponentBucket>> comp_buckets_;
	IdT comp_counter_ = 0;

};