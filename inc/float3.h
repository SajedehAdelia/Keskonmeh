#pragma once

#include <iostream>

class float3 {
    public:
    float x, y, z;

    float3();
    float3(float _x, float _y, float _z);
    float3(const float3& a);
    float3 operator=(const float3& a);

    friend std::ostream& operator<<(std::ostream& flux, const float3& a);

    float3 operator+(const float3& a) const;
    float3 operator-(const float3& a) const;
    float3 operator*(const float3& a) const;
    float3 operator/(const float3& a) const;
    float3 operator+=(const float3& a);
    float3 operator-=(const float3& a);
    float3 operator*=(const float3& a);
    float3 operator/=(const float3& a);

    float3 operator+(const float& a) const;
    float3 operator-(const float& a) const;
    float3 operator*(const float& a) const;
    float3 operator/(const float& a) const;
    float3 operator+=(const float& a);
    float3 operator-=(const float& a);
    float3 operator*=(const float& a);
    float3 operator/=(const float& a);

    bool operator==(const float3& a) const;

    float dot(const float3& a) const;
    float3 cross(const float3& a) const;
    float norm() const;
};