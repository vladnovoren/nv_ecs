#include "PrintSystem.h"
#include "../World.h"

void PrintSystem::Update(World &world, float dt) {
  auto filter = world.Filter<Age>();
  std::cout << "with Age: ";
  for (auto e : filter)
    std::cout << e << ' ';
  std::cout << '\n';

  filter = world.Filter<Position>();
  std::cout << "with Position: ";
  for (auto e : filter)
    std::cout << e << ' ';
  std::cout << '\n';

  filter = world.Filter<Age, Position>();
  std::cout << "with both: ";
  for (auto e : filter)
    std::cout << e << ' ';
  std::cout << '\n';
}