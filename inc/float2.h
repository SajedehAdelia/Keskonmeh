#pragma once

#include <iostream>
#include "int2.h"

class float2 {
    public:
    float x, y, z;

    float2();
    float2(float _x, float _y);
    float2(const float2& a);
    float2(const int2& a);
    float2 operator=(const float2& a);

    friend std::ostream& operator<<(std::ostream& flux, const float2& a);

    float2 operator+(const float2& a) const;
    float2 operator-(const float2& a) const;
    float2 operator*(const float2& a) const;
    float2 operator/(const float2& a) const;
    float2 operator+=(const float2& a);
    float2 operator-=(const float2& a);
    float2 operator*=(const float2& a);
    float2 operator/=(const float2& a);

    float2 operator+(const float& a) const;
    float2 operator-(const float& a) const;
    float2 operator*(const float& a) const;
    float2 operator/(const float& a) const;
    float2 operator+=(const float& a);
    float2 operator-=(const float& a);
    float2 operator*=(const float& a);
    float2 operator/=(const float& a);

    float2 operator+(const int2& a) const;
    float2 operator-(const int2& a) const;
    float2 operator*(const int2& a) const;
    float2 operator/(const int2& a) const;
    float2 operator+=(const int2& a);
    float2 operator-=(const int2& a);
    float2 operator*=(const int2& a);
    float2 operator/=(const int2& a);

    bool operator==(const float2& a) const;

    float dot(const float2& a) const;
    float norm() const;
};