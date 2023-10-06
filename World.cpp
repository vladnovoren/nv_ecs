#include "World.h"

Entity World::CreateEntity() {
	IdT id = entity_counter_++;
	entities_.insert(id);
	return id;
}

void World::ScheduleEntityDeletion(Entity ent) {
  to_die_list_.insert(ent);
}

void World::DeleteComponent(Entity ent, IdT comp) {
  comp_buckets_[comp]->EraseEntity(ent);
  ents_to_comps_[ent].erase(comp);
}

void World::DeleteEntity(Entity ent) {
  entities_.erase(ent);
  for (auto comp : ents_to_comps_[ent]) {
    DeleteComponent(ent, comp);
  }
}
