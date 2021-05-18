#pragma once

#include "entt.hpp"
#include "bamboo/core/Timestep.h"

namespace BAMBOO
{
	using registry_et = entt::basic_registry<entt::entity>;

	class Entity;
	class Scene
	{
		friend class Entity;
		friend class SceneHierarchyPanel;
	private:
		//entt::registry _Registry;
		registry_et _Registry;

		uint32_t _ViewportWidth = 0;
		uint32_t _ViewportHeight = 0;

	public:
		Scene();
		~Scene();

	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

	public:
		void OnUpdate(Timestep ts);
		void OnViewportResize(uint32_t width, uint32_t height);
		Entity CreateEntity(const std::string& name = std::string());
		void DestroyEntity(Entity entity);
	};

}