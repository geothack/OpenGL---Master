#pragma once


#include "World/Level.h"
#include "Core/Error.h"

class Entity
{
public:
	Entity() = default;

	Entity(const Entity& other) = default;

	Entity(entt::entity entity, Level& level);

	virtual ~Entity() {};

	virtual void Start() {};

	virtual void Update() {};

	template<typename T>
	bool HasComponent()
	{
		return mLevel->GetRegister().any_of<T>(mHandle);
	}

	template<typename T, typename ... Args>
	T& AddComponent(Args&& ... args)
	{
		if (HasComponent<T>())
		{
			Error error{ "Entity already has component" };
		}
		return mLevel->GetRegister().emplace<T>(mHandle, std::forward<Args>(args)...);
	}

	template<typename T>
	T& GetComponent()
	{
		if (!HasComponent<T>())
		{
			Error error{ "Entity does not have component" };
		}

		return mLevel->GetRegister().get<T>(mHandle);
	}

	template<typename T>
	void RemoveComponent()
	{
		if (!HasComponent<T>())
		{
			Error error{ "Entity does not have component" };
		}

		mLevel->GetRegister().erase<T>(mHandle);
	}

	template<typename T, typename ... Args>
	void UpdateComponent(Args&& ... args)
	{
		if (!HasComponent<T>())
		{
			Error error{ "Entity does not have component" };
		}

		mLevel->GetRegister().replace<T>(mHandle, std::forward<Args>(args)...);
	}

	Transform& GetTransform()
	{
		if (!HasComponent<Transform>())
		{
			Error error{ "Entity does not have transform component" };
		}

		return GetComponent<Transform>();
	}

	void SetTransform(const Transform& transform)
	{
		if (!HasComponent<Transform>())
		{
			Error error{ "Entity does not have transform component" };
		}

		UpdateComponent<Transform>(transform);
	}

	glm::vec3& GetPosition()
	{
		if (!HasComponent<Transform>())
		{
			Error error{ "Entity does not have transform component" };
		}

		return GetComponent<Transform>().GetPosition();
	}

	void SetPosition(const glm::vec3& position)
	{
		if (!HasComponent<Transform>())
		{
			Error error{ "Entity does not have transform component" };
		}

		GetComponent<Transform>().SetPosition(position);
	}

	glm::vec3& GetRotation()
	{
		if (!HasComponent<Transform>())
		{
			Error error{ "Entity does not have transform component" };
		}

		return GetComponent<Transform>().GetRotation();
	}

	void SetRotation(const glm::vec3& rotation)
	{
		if (!HasComponent<Transform>())
		{
			Error error{ "Entity does not have transform component" };
		}

		GetComponent<Transform>().SetPosition(rotation);
	}

	glm::vec3& GetScale()
	{
		if (!HasComponent<Transform>())
		{
			Error error{ "Entity does not have transform component" };
		}

		return GetComponent<Transform>().GetScale();
	}

	void SetScale(const glm::vec3& scale)
	{
		if (!HasComponent<Transform>())
		{
			Error error{ "Entity does not have transform component" };
		}

		GetComponent<Transform>().SetScale(scale);
	}

private:
	entt::entity mHandle;

	Level* mLevel;
};

