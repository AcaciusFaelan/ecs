#include <cassert>
#include "ecs/registry.hpp"

struct Position {
    float x, y;
};

struct Velocity {
    float dx, dy;
};

int main() {
    ecs::Registry registry;

    // Test createEntity
    auto e1 = registry.createEntity();
    auto e2 = registry.createEntity();
    assert(e1 != e2);

    // Test add and has
    registry.add(e1, Position{10.0f, 20.0f});
    assert(registry.has<Position>(e1));
    assert(!registry.has<Velocity>(e1));
    assert(!registry.has<Position>(e2));

    // Test get
    Position* pos = registry.get<Position>(e1);
    assert(pos != nullptr);
    assert(pos->x == 10.0f);
    assert(pos->y == 20.0f);
    
    // Test get on non-existent component
    assert(registry.get<Velocity>(e1) == nullptr);
    assert(registry.get<Position>(e2) == nullptr);

    // Test rm (remove)
    registry.rm<Position>(e1);
    assert(!registry.has<Position>(e1));
    assert(registry.get<Position>(e1) == nullptr);

    // Test re-adding
    registry.add(e1, Position{5.0f, 5.0f});
    assert(registry.has<Position>(e1));
    assert(registry.get<Position>(e1)->x == 5.0f);

    return 0;
}
