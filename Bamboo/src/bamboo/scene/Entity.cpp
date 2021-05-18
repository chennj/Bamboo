#include "Base.h"
#include "Entity.h"

namespace BAMBOO
{
	Entity::Entity(entt::entity entityHandle, Scene * scene)
		:_EntityHandle(entityHandle), _Scene(scene)
	{
	}
}
