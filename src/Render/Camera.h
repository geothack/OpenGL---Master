#pragma once


class Camera
{
public:
    Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f), const float yaw = -90.0f, const float pitch = 0.0f);

    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

    void ProcessMouseScroll(float yoffset);

    void MoveForward(float amt);
    void MoveBack(float amt);
    void MoveDown(float amt);
    void MoveUp(float amt);
    void MoveRight(float amt);
    void MoveLeft(float amt);

    

    glm::mat4 GetViewMatrix();

    glm::vec3& GetPos() { return mPosition; }
    glm::vec3& GetFront() { return mFront; }

private:
    void UpdateCameraVectors();

    glm::vec3 mPosition;
    glm::vec3 mFront;
    glm::vec3 mUp;
    glm::vec3 mRight;
    glm::vec3 mWorldUp;

    float mYaw;
    float mPitch;

    float mMovementSpeed;
    float mMouseSensitivity;
    float mZoom;
};

