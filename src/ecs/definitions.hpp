#pragma once

#include <cstdint>
#include <limits>

namespace ecs {
  using Entity = std::uint32_t;
  constexpr Entity NULL_ENTITY = std::numeric_limits<Entity>::max();
} // namespace: ecs