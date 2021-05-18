#pragma once

#include "Scene.h"

namespace BAMBOO
{
	class Entity
	{
	private:
		entt::entity _EntityHandle{ entt::null };
		Scene* _Scene = nullptr;

	public:
		Entity() = default;
		Entity(entt::entity entityHandle, Scene* scene);
		Entity(const Entity& other) = default;

	public:
		template<typename T>
		bool HasComponent()
		{
			return _Scene->_Registry.any_of<T>(_EntityHandle);
		}

		template<typename T, typename...Args>
		T& AddComponent(Args&&... args)
		{
			BB_CORE_ASSERT(!HasComponent<T>(), "Entity already has component");
			T& component = _Scene->_Registry.emplace<T>(_EntityHandle, std::forward<Args>(args)...);
			_Scene->OnComponentAdded<T>(*this, component);
			return component;
		}

		template<typename T>
		T& GetComponent()
		{
			BB_CORE_ASSERT(HasComponent<T>(), "Entity doesn't have component");
			return _Scene->_Registry.get<T>(_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			BB_CORE_ASSERT(HasComponent<T>(), "Entity doesn't have component");
			_Scene->_Registry.remove<T>(_EntityHandle);
		}

		operator bool()const { return _EntityHandle != entt::null; }
		operator uint32_t() const { return (uint32_t)_EntityHandle; }
		operator entt::entity()const { return _EntityHandle; }

		bool operator ==(const Entity& other) const 
		{ 
			return _EntityHandle == other._EntityHandle && _Scene == other._Scene; 
		}
		bool operator !=(const Entity& other) const
		{
			//return !operator==(other);
			return !(*this==other);
		}

	};

}