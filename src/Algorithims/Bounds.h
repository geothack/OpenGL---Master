#pragma once


enum class BoundTypes : unsigned char // Making the enum size 2 byte
{
	AABB = 0x00, // Axis aligned bounding box
	SPHERE = 0x01 
};

class BoundingRegion
{
public:
	BoundingRegion() = default;
	BoundingRegion(BoundTypes type);
	BoundingRegion(const glm::vec3& center, const float radius);
	BoundingRegion(const glm::vec3& min, const glm::vec3& max);


	glm::vec3 CalculateCenter();

	glm::vec3 CalculateDimensions();

	bool ContainsPoint(const glm::vec3& point);

	bool ContainsRegion(const BoundingRegion& region);

	bool IntersectsWith(BoundingRegion& region);

	glm::vec3& GetMax() { return mMax; }
	glm::vec3& SetMax(const glm::vec3& value) { return mMax = value; }
	glm::vec3& GetMin() { return mMin; }
	glm::vec3& SetMin(const glm::vec3& value) { return mMin = value; }
	glm::vec3& GetCenter() { return mCenter; }

	void SetRadius(const float value) { mRadius = value; }

private:
	BoundTypes mType;

	// Sphere
	glm::vec3 mCenter;
	float mRadius;

	// AABB
	glm::vec3 mMin;
	glm::vec3 mMax;
};