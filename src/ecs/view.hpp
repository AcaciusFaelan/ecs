#pragma once

#include "sparse_set.hpp"

#include <tuple>

namespace ecs {
  template <typename... Components>
  class View {
  public:
    View(SparseSet<Components>&... sets) : sets(&sets...) {}

    template <typename Func>
    void each(Func func);

  private:
    std::tuple<SparseSet<Components>*...> sets;
  }; // class: View

  template <typename... Components>
  template <typename Func>
  void View<Components...>::each(Func func)
  {
    auto* driverSet = std::get<0>(sets);
    const auto& entities = driverSet->getEntities();

    for (Entity entity : entities) {
      if ((std::get<SparseSet<Components>*>(sets)->contains(entity) && ...)) {
        func(entity, *std::get<SparseSet<Components>*>(sets)->get(entity)...);
      }
    }
  }
} // namespace: ecs