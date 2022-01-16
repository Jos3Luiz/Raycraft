#pragma once 
#include "raylib.h"

Vector3 operator+(const Vector3& lhs,const Vector3& rhs){
    return Vector3{lhs.x+rhs.x,lhs.y+rhs.y,lhs.z+rhs.z};
}

Vector3 operator/(const Vector3& lhs,const float& rhs){
    return Vector3{lhs.x/rhs,lhs.y/rhs,lhs.z/rhs};
}

Vector3 operator-(const Vector3& lhs,const Vector3& rhs){
    return Vector3{lhs.x-rhs.x,lhs.y-rhs.y,lhs.z-rhs.z};
}

Vector3 operator*(const Vector3& lhs,const float rhs){
    return Vector3{lhs.x*rhs,lhs.y*rhs,lhs.z*rhs};
}


Vector2 operator+(const Vector2& lhs,const Vector2& rhs){
    return Vector2{lhs.x+rhs.x,lhs.y+rhs.y};
}


inline float abs(float a,float b){
    return (a > b) ? a : b;
}

inline float min(float a,float b){
    if(a < b) return a;
    return b;
}