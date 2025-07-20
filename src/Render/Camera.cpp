#include "Core/Core.h"
#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : mFront(glm::vec3(0.0f, 0.0f, -1.0f)), mMovementSpeed(2.5f), mMouseSensitivity(0.1f), mZoom(45.0f)
{
    mPosition = position;
    mWorldUp = up;
    mYaw = yaw;
    mPitch = pitch;
    UpdateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : mFront(glm::vec3(0.0f, 0.0f, -1.0f)), mMovementSpeed(2.5f), mMouseSensitivity(0.1f), mZoom(45.0f)
{
    mPosition = glm::vec3(posX, posY, posZ);
    mWorldUp = glm::vec3(upX, upY, upZ);
    mYaw = yaw;
    mPitch = pitch;
    UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(mPosition, mPosition + mFront, mUp);
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= mMouseSensitivity;
    yoffset *= mMouseSensitivity;

    mYaw += xoffset;
    mPitch += yoffset;

    if (constrainPitch)
    {
        if (mPitch > 89.0f)
        {
            mPitch = 89.0f;
        }
        if (mPitch < -89.0f)
        {
            mPitch = -89.0f;
        }
    }

    UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    mZoom -= (float)yoffset;
    if (mZoom < 1.0f)
    {
        mZoom = 1.0f;
    }
    if (mZoom > 45.0f)
    {
        mZoom = 45.0f;
    }
}

void Camera::MoveForward(float amt)
{
    mPosition += -mFront * amt;
}

void Camera::MoveBack(float amt)
{
    mPosition += mFront * amt;
}

void Camera::MoveDown(float amt)
{
    mPosition -= mUp * amt;
}

void Camera::MoveUp(float amt)
{
    mPosition += mUp * amt;
}

void Camera::MoveRight(float amt)
{
    mPosition += glm::cross(mUp, mFront) * amt;
}

void Camera::MoveLeft(float amt)
{
    mPosition -= glm::cross(mUp, mFront) * amt;
}

void Camera::UpdateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    front.y = sin(glm::radians(mPitch));
    front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    mFront = glm::normalize(front);

    mRight = glm::normalize(glm::cross(mFront, mWorldUp)); 
    mUp = glm::normalize(glm::cross(mRight, mFront));
}