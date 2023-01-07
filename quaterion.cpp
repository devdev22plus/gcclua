#include <iostream>
#include <cmath>

#define PI 3.14159265

struct Vector3 {
  float x, y, z;
};

struct Quaternion {
  float x, y, z, w;
};

Quaternion operator*(const Quaternion& a, const Quaternion& b) {
  Quaternion result;
  result.x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y;
  result.y = a.w * b.y + a.y * b.w + a.z * b.x - a.x * b.z;
  result.z = a.w * b.z + a.z * b.w + a.x * b.y - a.y * b.x;
  result.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;
  return result;
}

Vector3 normalize(Vector3 v) {
  float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
  v.x /= length;
  v.y /= length;
  v.z /= length;
  return v;
}

Vector3 cross(Vector3 a, Vector3 b) {
  Vector3 result;
  result.x = a.y * b.z - a.z * b.y;
  result.y = a.z * b.x - a.x * b.z;
  result.z = a.x * b.y - a.y * b.x;
  return result;
}

Vector3 Euler(const Quaternion& q) {
  Vector3 euler;
  float sqw = q.w*q.w;
  float sqx = q.x*q.x;
  float sqy = q.y*q.y;
  float sqz = q.z*q.z;
  euler.x = atan2f(2.0f * (q.y*q.z + q.x*q.w), (-sqx - sqy + sqz + sqw));
  euler.y = asinf(-2.0f * (q.x*q.z - q.y*q.w));
  euler.z = atan2f(2.0f * (q.x*q.y + q.z*q.w), (sqx - sqy - sqz + sqw));
  return euler;
}

Vector3 ToEulerAngles(const Quaternion& q) {
  Vector3 euler;
  float sqw = q.w*q.w;
  float sqx = q.x*q.x;
  float sqy = q.y*q.y;
  float sqz = q.z*q.z;
  euler.x = atan2f(2.0f * (q.y*q.z + q.x*q.w), (-sqx - sqy + sqz + sqw));
  euler.y = asinf(-2.0f * (q.x*q.z - q.y*q.w));
  euler.z = atan2f(2.0f * (q.x*q.y + q.z*q.w), (sqx - sqy - sqz + sqw));
  return euler;
}

Quaternion EulerToQuaternion(const Vector3& euler) {
  Quaternion q;
  float c1 = cosf(euler.x / 2.0f);
  float c2 = cosf(euler.y / 2.0f);
  float c3 = cosf(euler.z / 2.0f);
  float s1 = sinf(euler.x / 2.0f);
  float s2 = sinf(euler.y / 2.0f);
  float s3 = sinf(euler.z / 2.0f);
  q.w = c1 * c2 * c3 - s1 * s2 * s3;
  q.x = s1 * s2 * c3 + c1 * c2 * s3;
  q.y = s1 * c2 * c3 + c1 * s2 * s3;
  q.z = c1 * s2 * c3 - s1 * c2 * s3;
  return q;
}

Quaternion LookRotation(Vector3 forward, Vector3 up) {
  forward = normalize(forward);

  Vector3 right = cross(up, forward);
  right = normalize(right);

  up = cross(forward, right);

  Quaternion q;
  q.w = sqrt(1.0 + right.x + up.y + forward.z) / 2.0;
  float w4_recip = 1.0 / (4.0 * q.w);
  q.x = (forward.y - up.z) * w4_recip;
  q.y = (right.z - forward.x) * w4_recip;
  q.z = (up.x - right.y) * w4_recip;

  return q;
}


int main() {
  Vector3 forward = {0, 0, 1};
  Vector3 up = {0, 1, 0};
  Vector3 right = {1, 0, 0};

  Vector3 eulerAngles = {0, 150, 0};
  std::cout << "Euler angles: " << eulerAngles.x << ", " << eulerAngles.y << ", " << eulerAngles.z << std::endl;

  Quaternion c = EulerToQuaternion(eulerAngles);
  std::cout << "Quaternion: " << c.x << ", " << c.y << ", " << c.z << ", " << c.w << std::endl;

  return 0;
}



