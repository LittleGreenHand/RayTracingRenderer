#pragma once
#ifndef  VEC3_H
#define VEC3_H
#endif
#include<cmath>
#include<iostream>
#include<random>
using std::sqrt;

inline double randomdouble() {
	//[0,1)
	return rand() / (RAND_MAX + 1.0);
}

inline double randomdouble(double min, double max) {
	//[min,max)
	//return min + (max - min) * random_double();
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
	static std::mt19937 generator;
	return distribution(generator);
}
class vec3 {
public:
	//构造函数
	vec3() :e{ 0,0,0 } { }
	vec3(double e0, double e1, double e2) :e{ e0, e1, e2 } { }
	//坐标
	double x() const { return e[0]; }
	double y() const { return e[1]; }
	double z() const { return e[2]; }
	//运算符
	vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	double operator[](int i) const { return e[i]; }
	double& operator[](int i) { return e[i]; }
	vec3& operator+=(const vec3& v) {
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}
	vec3& operator*=(const double t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}
	vec3& operator/=(const double t) {
		return *this *= 1 / t;
	}
	//长度相关
	double length() const {
		return sqrt(length_squared());
	}
	double length_squared() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}
	inline static vec3 random() {
		return vec3(randomdouble(), randomdouble(), randomdouble());
	}
	inline static vec3 random(double min, double max) {
		return vec3(randomdouble(min, max), randomdouble(min, max), randomdouble(min, max));
	}
public:
	double e[3];
};

// vec3 Utility Functions
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}
inline vec3 operator+(const vec3& u, const vec3& v) {
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}
inline vec3 operator-(const vec3& u, const vec3& v) {
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}
inline vec3 operator*(const vec3& u, const vec3& v) {
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}
inline vec3 operator*(double t, const vec3& v) {
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}
inline vec3 operator*(const vec3& v, double t) {
	return t * v;
}
inline vec3 operator/(const vec3& v, double t) {
	return (1 / t) * v;
}
//数量积
inline double dot(const vec3& u, const vec3& v) {
	return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}
//叉乘
inline vec3 cross(const vec3& u, const vec3& v) {
	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}
inline vec3 unit_vector(const vec3& v) {
	return v / v.length();
}

using point3 = vec3;	//3D point
using color = vec3;		//RGB color