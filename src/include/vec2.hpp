#ifndef TV2_H
#define TV2_H
#include <math.h>
#include <raylib.h>


class vec2 {
    public:
    long double e[2];
    vec2() {};
    vec2(long double e0, long double e1) {e[0]=e0; e[1]=e1;};//convert initializer arguments into vec
    vec2(long double e0) {e[0]=e0; e[1]=e0;};//convert initializer arguments into vec

    inline long double x() const {return e[0]; }
    inline long double y() const {return e[1]; }

    inline const vec2& operator+() const {return * this; }
    inline vec2 operator-() const {return vec2(-e[0], -e[1]); }
    inline long double operator[] (int i) const {return e[i];}
    inline long double& operator[](int i) {return e[i];};

    inline vec2& operator+=(const vec2 &v2);
    inline vec2& operator-=(const vec2 &v2);
    inline vec2& operator*=(const vec2 &v2);
    inline vec2& operator/=(const vec2 &v2);
    inline vec2& operator*=(const long double t);
    inline vec2& operator/=(const long double t);

    inline double length() const { return sqrt(e[0]*e[0] + e[1]*e[1]); }
    inline double squared_length() const { return e[0]*e[0] + e[1]*e[1]; }

    
    Vector2 toRayVec() {
        return (Vector2){
            (float)e[0],
            (float)e[1],
        };
    }

};

inline vec2 operator+(const vec2 &v1, const vec2 &v2) {//Vector+Vector
    return vec2(v1.e[0]+v2.e[0], v1.e[1]+v2.e[1]);
}

inline vec2 operator-(const vec2 &v1, const vec2 &v2) {//Vector-Vector
    return vec2(v1.e[0]-v2.e[0], v1.e[1]-v2.e[1]);
}

inline vec2 operator*(const vec2 &v1, const vec2 &v2) {//Vector * Vector
    return vec2(v1.e[0]*v2.e[0], v1.e[1]*v2.e[1]);
}

inline vec2 operator/(const vec2 &v1, const vec2 &v2) {//Vector * Vector
    return vec2(v1.e[0]/v2.e[0], v1.e[1]/v2.e[1]);
}

inline vec2 operator*(float t, const vec2 &v1) {//float * Vector
    return vec2(v1.e[0]*t, v1.e[1]*t);
}

inline vec2 operator/(const vec2 &v1, long double t) {
    return vec2(v1.e[0]/t, v1.e[1]/t);
}

inline vec2& vec2::operator+=(const vec2 &v) {
    e[0]+=v[0];
    e[1]+=v[1];
    return *this;
}

inline vec2& vec2::operator-=(const vec2 &v) {
    e[0]-=v[0];
    e[1]-=v[1];
    return *this;
}

inline vec2& vec2::operator*=(const vec2 &v) {
    e[0]*=v[0];
    e[1]*=v[1];
    return *this;
}

inline vec2& vec2::operator/=(const vec2 &v) {
    e[0]/=v[0];
    e[1]/=v[1];
    return *this;
}

inline vec2& vec2::operator/=(const long double f) {
    e[0]/=f;
    e[1]/=f;
    return *this;
}

inline vec2& vec2::operator*=(const long double t) {
    e[0]*=t;
    e[1]*=t;
    return *this;
}




#endif