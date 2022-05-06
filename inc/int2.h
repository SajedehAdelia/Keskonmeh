#pragma once

#include <iostream>

class int2 {
    public:
    int x, y;

    int2();
    int2(int _x, int _y);
    int2(const int2& a);
    int2 operator=(const int2& a);

    friend std::ostream& operator<<(std::ostream& flux, const int2& a);

    int2 operator+(const int2& a) const;
    int2 operator-(const int2& a) const;
    int2 operator*(const int2& a) const;
    int2 operator/(const int2& a) const;
    int2 operator+=(const int2& a);
    int2 operator-=(const int2& a);
    int2 operator*=(const int2& a);
    int2 operator/=(const int2& a);

    int2 operator+(const int& a) const;
    int2 operator-(const int& a) const;
    int2 operator*(const int& a) const;
    int2 operator/(const int& a) const;
    int2 operator+=(const int& a);
    int2 operator-=(const int& a);
    int2 operator*=(const int& a);
    int2 operator/=(const int& a);

    bool operator==(const int2& a) const;

    int dot(const int2& a) const;
    float norm() const;
};