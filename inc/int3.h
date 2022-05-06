#pragma once

#include <iostream>

class int3 {
    public:
    int x, y, z;

    int3();
    int3(int _x, int _y, int _z);
    int3(const int3& a);
    int3 operator=(const int3& a);

    friend std::ostream& operator<<(std::ostream& flux, const int3& a);

    int3 operator+(const int3& a) const;
    int3 operator-(const int3& a) const;
    int3 operator*(const int3& a) const;
    int3 operator/(const int3& a) const;
    int3 operator+=(const int3& a);
    int3 operator-=(const int3& a);
    int3 operator*=(const int3& a);
    int3 operator/=(const int3& a);

    int3 operator+(const int& a) const;
    int3 operator-(const int& a) const;
    int3 operator*(const int& a) const;
    int3 operator/(const int& a) const;
    int3 operator+=(const int& a);
    int3 operator-=(const int& a);
    int3 operator*=(const int& a);
    int3 operator/=(const int& a);

    bool operator==(const int3& a) const;

    int dot(const int3& a) const;
    float norm() const;
};