#pragma once

#include "System.h"
#include "../Components.h"
#include <iostream>

class PrintSystem : public ISystem {
public:
  ~PrintSystem() override = default;

  void Update(World& world, float dt) override;
};
