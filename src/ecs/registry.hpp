#pragma once

#include "definitions.hpp"
#include "sparse_set.hpp"

#include <unordered_map>
#include <typeindex>
#include <typeinfo>
#include <memory>

namespace ecs {
  class Registry {
  public:
    Registry() = default;
    ~Registry() = default;

    Entity createEntity();

    template<typename T>
    void add(Entity entity, T component);

    template<typename T>
    void rm(Entity entity);

    template<typename T>
    T* get(Entity entity);

    template<typename T>
    bool has(Entity entity);
  private:
    Entity nextEntityID = 0;
    std::unordered_map<std::type_index, std::unique_ptr<ISparseSet>> componentSets;
  }; // class: Registry

  Entity Registry::createEntity() {
    return nextEntityID++;
  }

  template<typename T>
  void Registry::add(Entity entity, T component) {
    auto [it, inserted] = componentSets.emplace(typeid(T), nullptr);

    if (inserted || !it->second) {
      it->second = std::make_unique<SparseSet<T>>();
    }

    static_cast<SparseSet<T>*>(it->second.get())->add(entity, component);
  }

  template<typename T>
  void Registry::rm(Entity entity) {
    auto it = componentSets.find(typeid(T));
    if (it != componentSets.end())
      static_cast<SparseSet<T>*>(it->second.get())->remove(entity);
  }

  template<typename T>
  T* Registry::get(Entity entity) {
    auto it = componentSets.find(typeid(T));
    if (it != componentSets.end())
      return static_cast<SparseSet<T>*>(it->second.get())->get(entity);
    
    return nullptr;
  }

  template<typename T>
  bool Registry::has(Entity entity) {
    auto it = componentSets.find(typeid(T));
    if (it != componentSets.end())
      return static_cast<SparseSet<T>*>(it->second.get())->contains(entity);
    
    return false;
  }
} // namespace: ecs
