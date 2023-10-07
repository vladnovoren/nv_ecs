#pragma once

class World;

class ISystem {
public:
  virtual ~ISystem() = 0;

  virtual void Update(World& world, float dt) = 0;
};