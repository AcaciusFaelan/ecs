#pragma once

namespace ecs {
  struct TestComponent {
    const char* name = "TestComponent";
    int value;
    bool active;
  };
}