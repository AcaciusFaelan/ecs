#include <print>
#include "ecs/registry.hpp"
#include "components/test_component.hpp"
#include "components/test_component_1.hpp"

int main() {
  ecs::Registry registry;

  auto e1 = registry.createEntity();
  auto e2 = registry.createEntity();
  auto e3 = registry.createEntity();

  registry.add(e1, ecs::TestComponent{.value = 10, .active = true});
  registry.add(e1, ecs::TestComponent1{.x = 1.0f, .y = 2.0f});

  registry.add(e2, ecs::TestComponent{.value = 20, .active = false});
  // e2 only has TestComponent

  registry.add(e3, ecs::TestComponent{.value = 30, .active = true});
  registry.add(e3, ecs::TestComponent1{.x = 3.0f, .y = 4.0f});

  std::println("Iterating over entities with TestComponent and TestComponent1:");
  registry.view<ecs::TestComponent, ecs::TestComponent1>().each([](ecs::Entity entity, ecs::TestComponent& tc, ecs::TestComponent1& tc1) {
    std::println("Entity {}: Value = {}, X = {}, Y = {}", entity, tc.value, tc1.x, tc1.y);
  });
  
  std::println("\nIterating over entities with TestComponent:");
  registry.view<ecs::TestComponent>().each([](ecs::Entity entity, ecs::TestComponent& tc) {
      std::println("Entity {}: Value = {}, Active = {}", entity, tc.value, tc.active);
  });

  return 0;
}
