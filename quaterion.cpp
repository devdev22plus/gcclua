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


	return 0;
}