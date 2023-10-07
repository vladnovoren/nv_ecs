#include <iostream>
#include "World.h"
#include "System/PrintSystem.h"



int main() {
  World w;
  auto e0 = w.CreateEntity();
  w.SetComponent(e0, Position{1.0f});

  auto e1 = w.CreateEntity();
  w.SetComponent(e1, Age{});

  auto e2 = w.CreateEntity();
  w.SetComponent(e2, Position{});
  w.SetComponent(e2, Age{});

  w.AddSystem<PrintSystem>();

  w.Update(0.f);

  auto& pos = w.GetComponent<Position>(e0);
  std::cout << pos.val << '\n';

  return 0;
}
