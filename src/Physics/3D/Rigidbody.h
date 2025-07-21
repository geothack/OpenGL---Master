#pragma once


#include "World/Transform.h"

class Rigidbody
{
public:
    Rigidbody(std::string_view modelId = "", const Transform& transform = {}, float mass = 1.0f);

    void Update(float dt);

    void ApplyForce(const glm::vec3& force);
    void ApplyForce(const glm::vec3& direction, float magnitude);

    void ApplyAcceleration(const glm::vec3& acceleration);
    void ApplyAcceleration(const glm::vec3& direction, float magnitude);

    void ApplyImpulse(const glm::vec3& force, float dt);
    void ApplyImpulse(const glm::vec3& direction, float magnitude, float dt);

    void TransferEnergy(float joules, const glm::vec3& direction);

    void HandleCollision(const Rigidbody* inst, const glm::vec3& norm);

private:
    unsigned char mState;

    float mMass;

    Transform mTransform;
    glm::vec3 mVelocity;
    glm::vec3 mAcceleration;


    glm::mat4 mModel;
    glm::mat3 mNormalModel;

    std::string mModelId;
    std::string mInstanceId;

    float mLastCollision;
    std::string mLastCollisionID;

    bool operator==(Rigidbody rb);
    bool operator==(std::string id);
};

