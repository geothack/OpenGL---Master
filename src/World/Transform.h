#pragma once


class Transform
{
public:
	Transform(const glm::vec3& position = glm::vec3(0.0), const glm::vec3& rotation = glm::vec3(0.0), const glm::vec3& scale = glm::vec3(1.0));
	~Transform();


public:
	glm::vec3& GetPosition() { return mPosition; }
	glm::vec3& GetRotation() { return mRotation; }
	glm::vec3& GetScale() { return mScale; }

	void SetPosition(const glm::vec3& position) { mPosition = position; }
	void SetRotation(const glm::vec3& rotation) { mPosition = rotation; }
	void SetScale(const glm::vec3& scale) { mPosition = scale; }

private:
	glm::vec3 mPosition;
	glm::vec3 mRotation;
	glm::vec3 mScale;
};

