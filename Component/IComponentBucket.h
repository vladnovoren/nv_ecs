#pragma once

#include "../Entity/Entity.h"
#include <unordered_map>

class IComponentBucket {
public:
  virtual void EraseEntity(Entity ent) = 0;

	virtual ~IComponentBucket() = 0;
};

template<typename T>
class ComponentBucket : public IComponentBucket {
public:
	~ComponentBucket() override = default;

	bool HasEntity(Entity ent) const {
		return ent_to_comp_.find(ent) != ent_to_comp_.end();
	}

	void EraseEntity(Entity ent) override {
		ent_to_comp_.erase(ent);
	}

	T& Get(Entity ent) {
		return ent_to_comp_[ent];
	}

	void Set(Entity ent, T&& comp) {
		ent_to_comp_[ent] = std::forward<T>(comp);
	}

private:
	std::unordered_map<Entity, T> ent_to_comp_;
};
