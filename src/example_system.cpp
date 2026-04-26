#include "ecs/definitions.hpp"
#include "ecs/registry.hpp"

struct Position {
    int x;
    int y;
};

struct Velocity {
    int dx;
    int dy;
};

void MovementSystem(ecs::Entity entity, Position& pos, Velocity& vel);

void mainloop(ecs::Registry& registry) {
    registry.view<Position, Velocity>().each([](ecs::Entity entity, Position& pos, Velocity& vel) {
        MovementSystem(entity, pos, vel);
    });
}

void MovementSystem(ecs::Entity entity, Position& pos, Velocity& vel) {
        pos.x += vel.dx;
        pos.y += vel.dy;
}
