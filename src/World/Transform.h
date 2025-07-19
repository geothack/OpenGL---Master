#pragma once


class Transform
{
public:
	Transform(const glm::vec3& position = glm::vec3(0.0), const glm::vec3& rotation = glm::vec3(0.0), const glm::vec3& scale = glm::vec3(1.0));
	~Transform();


public:
	inline const glm::vec3* const GetPosition() const { return &mPosition; }
	inline const glm::vec3* const GetRotation() const { return &mRotation; }
	inline const glm::vec3* const GetScale() const { return &mScale; }

	inline const void const SetPosition(const glm::vec3* position) { mPosition = *position; }
	inline const void const SetRotation(const glm::vec3* rotation) { mPosition = *rotation; }
	inline const void const SetScale(const glm::vec3* scale) { mPosition = *scale; }

private:
	glm::vec3 mPosition;
	glm::vec3 mRotation;
	glm::vec3 mScale;
};

