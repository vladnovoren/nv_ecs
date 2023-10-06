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
  return 0;
}
