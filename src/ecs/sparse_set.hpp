#pragma once

#include "definitions.hpp"

#include <cstddef>
#include <vector>

namespace ecs {
  template <typename T>
  class SparseSet {
  public:
    void add(Entity entity, T component);
    void remove(Entity entity);
    T* get(Entity entity);
    bool contains(Entity entity);

    auto begin() { return dense.begin(); }
    auto end() { return dense.end(); }
    auto cbegin() { return dense.cbegin(); }
    auto cend() { return dense.cend(); }

    const std::vector<Entity>& getEntities() const { return indices; }
    size_t size() const { return dense.size(); }

  private:
    std::vector<Entity> sparse;
    std::vector<Entity> indices;
    std::vector<T> dense;
  }; // class: SparseSet

  template <typename T>
  void SparseSet<T>::add(Entity entity, T component) {
    if (entity >= sparse.size())
      sparse.resize(entity + 1, NULL_ENTITY);

    sparse[entity] = dense.size();

    dense.push_back(component);
    indices.push_back(entity);
  }

  template <typename T>
  void SparseSet<T>::remove(Entity entity) {
    if (dense.empty() || sparse[entity] == NULL_ENTITY)
      return;

    size_t holeIndex = sparse[entity];
    size_t lastIndex = dense.size() - 1;
    size_t swappedEntity = indices[lastIndex];

    dense[holeIndex] = dense[lastIndex];
    indices[holeIndex] = indices[lastIndex];

    sparse[entity] = NULL_ENTITY;

    dense.pop_back();
    indices.pop_back();

    sparse[swappedEntity] = holeIndex;
  }
} // namespace: ecs
