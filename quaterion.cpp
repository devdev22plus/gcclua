#include <iostream>
#include <cmath>

#pragma warning( disable: 4365 )

const float DEG_TO_RAD = M_PI / 180.0f; // 0.0174532924f

struct Vector3 {
  float x, y, z;


public:
  static Vector3 forward() {
    return {0, 0, 1};
  }

  static Vector3 up() {
    return {0, 1, 0};
  }

  static Vector3 right() {
    return {1, 0, 0};
  }

  Vector3 normalized() {
    float length = sqrt(x * x + y * y + z * z);
    return {x / length, y / length, z / length};
  }

  Vector3 cross(Vector3 other) {
    return {
      y * other.z - z * other.y,
      z * other.x - x * other.z,
      x * other.y - y * other.x
    };
  }

  float angle(Vector3 other) {
    float dot = this->dot(other);
    float lengthProduct = this->magnitude() * other.magnitude();
    float angle = acos(dot / lengthProduct);
    return angle * 180.0f / M_PI;
  }

  float dot(Vector3 other) {
    return x * other.x + y * other.y + z * other.z;
  }

  float magnitude() {
    return sqrt(x * x + y * y + z * z);
  }

  float distance(Vector3 other) {
    float dx = x - other.x;
    float dy = y - other.y;
    float dz = z - other.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
  }

  Vector3 operator+(Vector3 other) {
    return {x + other.x, y + other.y, z + other.z};
  }

  Vector3 operator-(Vector3 other) {
    return {x - other.x, y - other.y, z - other.z};
  }

  Vector3 operator*(float s) {
    return {x * s, y * s, z * s};
  }

  Vector3 operator/(float s) {
    return {x / s, y / s, z / s};
  }

  bool operator==(Vector3 other) {
    return x == other.x && y == other.y && z == other.z;
  }

  bool operator!=(Vector3 other) {
    return !(*this == other);
  }

  Vector3 operator=(Vector3 other) {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
  }

  Vector3 operator+=(Vector3 other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  }

  Vector3 operator-=(Vector3 other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
  }

  Vector3 operator*=(float s) {
    x *= s;
    y *= s;
    z *= s;
    return *this;
  }

  Vector3 operator/=(float s) {
    x /= s;
    y /= s;
    z /= s;
    return *this;
  }

  Vector3 operator*(Quaternion rotation) const {
    float num = rotation.x * 2.0f;
    float num2 = rotation.y * 2.0f;
    float num3 = rotation.z * 2.0f;
    float num4 = rotation.x * num;
    float num5 = rotation.y * num2;
    float num6 = rotation.z * num3;
    float num7 = rotation.x * num2;
    float num8 = rotation.x * num3;
    float num9 = rotation.y * num3;
    float num10 = rotation.w * num;
    float num11 = rotation.w * num2;
    float num12 = rotation.w * num3;
    Vector3 result;
    result.x = (1.0f - (num5 + num6)) * x + (num7 - num12) * y + (num8 + num11) * z;
    result.y = (num7 + num12) * x + (1.0f - (num4 + num6)) * y + (num9 - num10) * z;
    result.z = (num8 - num11) * x + (num9 + num10) * y + (1.0f - (num4 + num5)) * z;
    return result;
  }
};


struct Quaternion {
  float x, y, z, w;

	static Quaternion Internal_Euler(Vector3 euler) {
	  float cx = cos(euler.x * 0.5f);
	  float cy = cos(euler.y * 0.5f);
	  float cz = cos(euler.z * 0.5f);
	  float sx = sin(euler.x * 0.5f);
	  float sy = sin(euler.y * 0.5f);
	  float sz = sin(euler.z * 0.5f);

	  Quaternion q;
	  q.x = sx * cy * cz - cx * sy * sz;
	  q.y = cx * sy * cz + sx * cy * sz;
	  q.z = cx * cy * sz - sx * sy * cz;
	  q.w = cx * cy * cz + sx * sy * sz;
	  return q;
	}

public:
	static Quaternion Euler(Vector3 euler)
	{
		return Internal_Euler(euler * DEG_TO_RAD);
	}

	static Quaternion LookRotation(Vector3 forward, Vector3 up) {
	  Vector3 zaxis = forward;
	  Vector3 xaxis = up.cross(zaxis);
	  Vector3 yaxis = zaxis.cross(xaxis);

	  Quaternion q;
	  q.x = xaxis.x;
	  q.y = xaxis.y;
	  q.z = xaxis.z;
	  q.w = sqrt(1.0f + q.x + q.y + q.z) * 0.5f;
	  float w4_recip = 1.0f / (4.0f * q.w);
	  q.x = (yaxis.z - zaxis.y) * w4_recip;
	  q.y = (zaxis.x - xaxis.z) * w4_recip;
	  q.z = (xaxis.y - yaxis.x) * w4_recip;
	  return q;
	}

	static Quaternion identity() {
		return {0.0f, 0.0f, 0.0f, 1.0f};
	}

	Quaternion operator*(Quaternion other) {
		Quaternion result;
		result.x = w * other.x + x * other.w + y * other.z - z * other.y;
		result.y = w * other.y + y * other.w + z * other.x - x * other.z;
		result.z = w * other.z + z * other.w + x * other.y - y * other.x;
		result.w = w * other.w - x * other.x - y * other.y - z * other.z;
		return result;
	}

	Vector3 operator*(Vector3 point) const {
		float num = x * 2.0f;
		float num2 = y * 2.0f;
		float num3 = z * 2.0f;
		float num4 = x * num;
		float num5 = y * num2;
		float num6 = z * num3;
		float num7 = x * num2;
		float num8 = x * num3;
		float num9 = y * num3;
		float num10 = w * num;
		float num11 = w * num2;
		float num12 = w * num3;
		Vector3 result;
		result.x = (1.0f - (num5 + num6)) * point.x + (num7 - num12) * point.y + (num8 + num11) * point.z;
		result.y = (num7 + num12) * point.x + (1.0f - (num4 + num6)) * point.y + (num9 - num10) * point.z;
		result.z = (num8 - num11) * point.x + (num9 + num10) * point.y + (1.0f - (num4 + num5)) * point.z;
		return result;
	}
};

int main() {
	/* Vector3 euler = {0, 0, 150}; */
	Vector3 euler = {0, 150, 0};
	/* Vector3 euler = {150, 0, 0}; */
	Quaternion q = Quaternion::Euler(euler);
	std::cout << "(" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")" << std::endl;

	Vector3 result = Vector3::up();
	std::cout << "(" << result.x << ", " << result.y << ", " << result.z << ")" << std::endl;

	q = Quaternion::LookRotation(euler, result);
	std::cout << "(" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")" << std::endl;


	Quaternion q1 = {1, 2, 3, 4};
	Quaternion q2 = {5, 6, 7, 8};
	Quaternion q3 = q1 * q2;
	std::cout << "Result: (" << q3.x << ", " << q3.y << ", " << q3.z << ", " << q3.w << ")" << std::endl;


	q3 = q3 * Quaternion::identity();
	std::cout << "Result: (" << q3.x << ", " << q3.y << ", " << q3.z << ", " << q3.w << ")" << std::endl;


	return 0;
}