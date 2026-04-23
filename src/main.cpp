#include <print>
#include "ecs/registry.hpp"

struct Position {
    float x, y;
};

struct Velocity {
    float dx, dy;
};

struct Tag {
    const char* name;
};

int main() {
    ecs::Registry registry;

    // Create entities with various components
    auto e1 = registry.createEntity();
    registry.add(e1, Tag{"Player"});
    registry.add(e1, Position{10.0f, 10.0f});
    registry.add(e1, Velocity{1.5f, 0.0f});

    auto e2 = registry.createEntity();
    registry.add(e2, Tag{"Enemy"});
    registry.add(e2, Position{50.0f, 50.0f});
    registry.add(e2, Velocity{-1.0f, -1.0f});

    auto e3 = registry.createEntity();
    registry.add(e3, Tag{"Static Object"});
    registry.add(e3, Position{100.0f, 100.0f});

    std::println("--- Initial State ---");
    registry.view<Tag, Position>().each([](ecs::Entity entity, Tag& tag, Position& pos) {
        std::println("Entity {}: {} at ({}, {})", entity, tag.name, pos.x, pos.y);
    });

    // Update positions based on velocity
    std::println("\n--- Updating Positions ---");
    registry.view<Position, Velocity>().each([](ecs::Entity entity, Position& pos, Velocity& vel) {
        pos.x += vel.dx;
        pos.y += vel.dy;
        std::println("Updated Entity {} position to ({}, {})", entity, pos.x, pos.y);
    });

    std::println("\n--- Final State ---");
    registry.view<Tag, Position>().each([](ecs::Entity entity, Tag& tag, Position& pos) {
        std::println("Entity {}: {} at ({}, {})", entity, tag.name, pos.x, pos.y);
    });

    return 0;
}