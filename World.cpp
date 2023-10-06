#include "World.h"

IdT World::CreateEntity()
{
	IdT id = entity_counter_++;
	entities_.insert(id);
	return id;
}
