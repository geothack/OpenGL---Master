#include "Core/Core.h"
#include "Bounds.h"

BoundingRegion::BoundingRegion(BoundTypes type) : mType(type)
{
}

BoundingRegion::BoundingRegion(const glm::vec3& center, const float radius) : mType(BoundTypes::SPHERE), mCenter(center), mRadius(radius)
{
}

BoundingRegion::BoundingRegion(const glm::vec3& min, const glm::vec3& max) : mType(BoundTypes::AABB), mMin(min), mMax(max)
{
}

glm::vec3 BoundingRegion::CalculateCenter()
{
	return mType == BoundTypes::AABB ? (mMin + mMax) / 2.0f : mCenter;
}

glm::vec3 BoundingRegion::CalculateDimensions()
{
	return mType == BoundTypes::AABB ? (mMax - mMin) : glm::vec3(2.0f * mRadius);
}

bool BoundingRegion::ContainsPoint(const glm::vec3& point)
{
	if (mType == BoundTypes::AABB)
	{
		return (point.x >= mMin.x) && (point.x <= mMax.x) &&
			(point.x >= mMin.y) && (point.x <= mMax.y) &&
			(point.x >= mMin.z) && (point.x <= mMax.z);
	}
	else if(mType == BoundTypes::SPHERE)
	{
		float distanceSquared = 0.0f;

		for (auto i = 0; i < 3; i++)
		{
			distanceSquared += (mCenter[i] - point[i]) * (mCenter[i] - point[i]);
		}

		return distanceSquared <= (mRadius * mRadius);
	}
}

bool BoundingRegion::ContainsRegion(const BoundingRegion& region)
{
	if (region.mType == BoundTypes::AABB)
	{
		return ContainsPoint(region.mMin) && ContainsPoint(region.mMax);
	}
	else if (mType == BoundTypes::SPHERE && region.mType == BoundTypes::SPHERE)
	{
		return glm::length(mCenter - region.mCenter) + region.mRadius < mRadius;
	}
	else
	{
		if (!ContainsPoint(region.mCenter))
		{
			return false;
		}

		for (auto i = 0; i < 3; i++)
		{
			if (glm::abs(mMax[i] - region.mCenter[i]) < region.mRadius ||
				glm::abs(region.mCenter[i] - mMin[i]) < region.mRadius)
			{
				return false;
			}
		}

		return true;
	}

}

bool BoundingRegion::IntersectsWith(BoundingRegion& region)
{
	if (mType == BoundTypes::AABB && region.mType == BoundTypes::AABB)
	{
		glm::vec3 radius = CalculateDimensions() / 2.0f;
		glm::vec3 regionRadius = region.CalculateDimensions() / 2.0f;

		glm::vec3 center = CalculateCenter();
		glm::vec3 regionCenter = region.CalculateCenter();

		glm::vec3 distance = glm::abs(center - regionCenter);

		for (auto i = 0; i < 3; i++)
		{
			if (distance[i] > radius[i] + regionRadius[i])
			{
				return false;
			}
		}

		return true;
	}
	else if (mType == BoundTypes::SPHERE && region.mType == BoundTypes::SPHERE)
	{
		return glm::length(mCenter - region.mCenter) < (mRadius + region.mRadius);
	}
	else if (mType == BoundTypes::SPHERE)
	{
		float distanceSquared = 0.0f;

		for (auto i = 0; i < 3; i++)
		{
			if (mCenter[i] < region.mMin[i])
			{
				distanceSquared += (region.mMin[i] - mCenter[i]) * (region.mMin[i] * mCenter[i]);
			}
			else if (mCenter[i] > region.mMax[i])
			{
				distanceSquared += (mCenter[i] - region.mMax[i]) * (mCenter[i] - region.mMax[i]);
			}
			
		}

		return distanceSquared < (mRadius * mRadius);
	}
	else
	{
		return region.IntersectsWith(*this);
	}
}
