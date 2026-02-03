#include <cassert>
#include <vector>
#include <algorithm>
#include "ecs/registry.hpp"

struct TagA { int value; };
struct TagB { int value; };
struct TagC { int value; };

int main() {
    ecs::Registry registry;

    auto e1 = registry.createEntity();
    auto e2 = registry.createEntity();
    auto e3 = registry.createEntity();
    auto e4 = registry.createEntity();

    // Setup:
    // e1: A, B
    // e2: A
    // e3: B
    // e4: A, B, C

    registry.add(e1, TagA{1});
    registry.add(e1, TagB{2});

    registry.add(e2, TagA{3});

    registry.add(e3, TagB{4});

    registry.add(e4, TagA{5});
    registry.add(e4, TagB{6});
    registry.add(e4, TagC{7});

    // Test Single View (TagA) -> e1, e2, e4
    int countA = 0;
    std::vector<ecs::Entity> entitiesA;
    registry.view<TagA>().each([&](ecs::Entity e, TagA& a) {
        countA++;
        entitiesA.push_back(e);
        assert(a.value > 0);
    });
    assert(countA == 3);
    assert(std::find(entitiesA.begin(), entitiesA.end(), e1) != entitiesA.end());
    assert(std::find(entitiesA.begin(), entitiesA.end(), e2) != entitiesA.end());
    assert(std::find(entitiesA.begin(), entitiesA.end(), e4) != entitiesA.end());

    // Test Multi View (TagA, TagB) -> e1, e4
    int countAB = 0;
    std::vector<ecs::Entity> entitiesAB;
    registry.view<TagA, TagB>().each([&](ecs::Entity e, TagA& a, TagB& b) {
        countAB++;
        entitiesAB.push_back(e);
        assert(a.value > 0);
        assert(b.value > 0);
    });
    assert(countAB == 2);
    assert(std::find(entitiesAB.begin(), entitiesAB.end(), e1) != entitiesAB.end());
    assert(std::find(entitiesAB.begin(), entitiesAB.end(), e4) != entitiesAB.end());

    // Test Multi View with mismatch (TagA, TagC) -> e4
    int countAC = 0;
    registry.view<TagA, TagC>().each([&](ecs::Entity e, TagA& a, TagC& c) {
        countAC++;
        assert(e == e4);
    });
    assert(countAC == 1);

    return 0;
}
