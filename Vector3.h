#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3
{
public:
	Vector3();
	Vector3(float x, float y, float z);
	virtual ~Vector3();
	float getX() const;
	float getY() const;
	float getZ() const;
	void setX(float data);
	void setY(float data);
	void setZ(float data);
	bool operator==(const Vector3& other) const;
	bool operator!=(const Vector3& other) const;
private:
	static bool equal(const Vector3& c1, const Vector3& c2);
	float x, y, z;
};

#endif // VECTOR3_H
