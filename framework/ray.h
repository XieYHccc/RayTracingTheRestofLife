#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray
{
public:
    ray(const point3& origin, const vec3& direction, double time)
        : m_origin(origin), m_direction(direction), m_tm(time) {}
    ray(const point3& origin, const vec3& direction)
        : ray(origin, direction, 0) {}
    ray() : m_origin(point3(0, 0, 0)), m_direction(vec3(0, 0, 0)), m_tm(0) {}

    const point3& origin() const { return m_origin; }
    const vec3& direction() const { return m_direction; }

    double time() const { return m_tm; }
    point3 at(double t) const
    {
        return m_origin + t * m_direction;
    }

private:
    point3 m_origin;
    vec3 m_direction;
    double m_tm;
};
#endif