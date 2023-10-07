#include <iostream>
#include "World.h"

struct Position {
  float val = 0;
};

struct Age {
  int val = 0;
};

int main() {
  World w;
  auto e = w.CreateEntity();
  w.SetComponent(e, Position{});
  std::cout << w.HasComponents<Position>(e) << '\n';
  std::cout << w.HasComponents<Age>(e) << '\n';
  std::cout << w.HasComponents<Position, Age>(e) << '\n';
  std::cout << w.HasComponents<Position>(e) << '\n';
  std::cout << w.HasComponents<Age>(e) << '\n';
  w.ScheduleEntityDeletion(e);
  w.Update(0.f);
  std::cout << w.IsAlive(e) << '\n';
  return 0;
}
