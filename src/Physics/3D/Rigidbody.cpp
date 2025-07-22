#include "Core/Core.h"
#include "Rigidbody.h"

Rigidbody::Rigidbody(std::string_view modelId, const Transform& transform, float mass) : mModelId(modelId.data()), mTransform(transform), mMass(mass), mVelocity(0.0f), mAcceleration(0.0f), mState(0),
	mLastCollision(0.05f), mLastCollisionID("")
{
	Update(0.0f);
}

void Rigidbody::Update(float dt)
{
    mTransform.SetPosition(mTransform.GetPosition() += mVelocity * dt + 0.5f * mAcceleration * (dt * dt));
    mVelocity += mAcceleration * dt;

    //glm::mat4 rotMat = glm::toMat4(glm::quat(mTransform.GetRotation()));
    //
    //mModel = glm::translate(glm::mat4(1.0f), mTransform.GetPosition());
    //mModel = mModel * rotMat; 
    //mModel = glm::scale(mModel, mTransform.GetScale());
    //
    //mNormalModel = glm::transpose(glm::inverse(glm::mat3(mModel)));
    //
    //mLastCollision += dt;
}

void Rigidbody::ApplyForce(const glm::vec3& force)
{
    mAcceleration += force / mMass;
}

void Rigidbody::ApplyForce(const glm::vec3& direction, float magnitude)
{
    ApplyForce(direction * magnitude);
}

void Rigidbody::ApplyAcceleration(const glm::vec3& a)
{
    mAcceleration += a;
}

void Rigidbody::ApplyAcceleration(const glm::vec3& direction, float magnitude)
{
    ApplyAcceleration(direction * magnitude);
}

void Rigidbody::ApplyImpulse(const glm::vec3& force, float dt)
{
    mVelocity += force / mMass * dt;
}

void Rigidbody::ApplyImpulse(const glm::vec3& direction, float magnitude, float dt) 
{
    ApplyImpulse(direction * magnitude, dt);
}

void Rigidbody::TransferEnergy(float joules, const glm::vec3& direction)
{
    if (joules == 0) 
    {
        return;
    }

    glm::vec3 deltaV = sqrt(2 * abs(joules) / mMass) * direction;

    mVelocity += joules > 0 ? deltaV : -deltaV;
}


void Rigidbody::HandleCollision(const Rigidbody* inst, const glm::vec3& norm)
{
    if (mLastCollision >= 0.05f || mLastCollisionID != inst->mInstanceId) 
    {
        mVelocity = glm::reflect(mVelocity, glm::normalize(norm)); 
        mLastCollision = 0.0f; 
    }

    mLastCollisionID = inst->mInstanceId;
}
