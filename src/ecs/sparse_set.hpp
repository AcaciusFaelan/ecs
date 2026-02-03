#pragma once

#include "definitions.hpp"

#include <cstddef>
#include <vector>

namespace ecs {

  class ISparseSet {
  public:
    virtual ~ISparseSet() = default;
    virtual void remove(Entity entity) = 0;
  };

  template <typename T>
  class SparseSet : public ISparseSet {
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

    if (holeIndex != lastIndex) {
      size_t swappedEntity = indices[lastIndex];

      dense[holeIndex] = dense[lastIndex];
      indices[holeIndex] = indices[lastIndex];

      sparse[swappedEntity] = holeIndex;
    }

    sparse[entity] = NULL_ENTITY;

    dense.pop_back();
    indices.pop_back();
  }

  template <typename T>
  T* SparseSet<T>::get(Entity entity) {
    if (entity >= sparse.size() || sparse[entity] == NULL_ENTITY)
      return nullptr;

    return &dense[sparse[entity]];
  }

  template <typename T>
  bool SparseSet<T>::contains(Entity entity) {
    return entity < sparse.size() && sparse[entity] != NULL_ENTITY;
  }
} // namespace: ecs
