#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
public:
    // Stationary Sphere
    sphere(const point3& center, double radius, shared_ptr<material> mat)
        : m_center(center, vec3(0, 0, 0)), m_radius(std::fmax(0, radius)), m_mat(mat)
    {
        auto rvec = vec3(radius, radius, radius);
        m_bbox = aabb(center - rvec, center + rvec);
    }

    // Moving Sphere
    sphere(const point3& center1, const point3& center2, double radius,
        shared_ptr<material> mat)
        : m_center(center1, center2 - center1), m_radius(std::fmax(0, radius)), m_mat(mat) 
    {
        auto rvec = vec3(radius, radius, radius);
        aabb box1(m_center.at(0) - rvec, m_center.at(0) + rvec);
        aabb box2(m_center.at(1) - rvec, m_center.at(1) + rvec);
        m_bbox = aabb(box1, box2);
    }

    aabb bounding_box() const override { return m_bbox; }
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        point3 current_center = m_center.at(r.time());
        vec3 oc = current_center - r.origin();
        auto a = r.direction().length_squared();
        auto h = dot(r.direction(), oc);
        auto c = oc.length_squared() - m_radius * m_radius;

        auto discriminant = h * h - a * c;
        if (discriminant < 0)
            return false;

        auto sqrtd = std::sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (h - sqrtd) / a;
        if (!ray_t.surrounds(root)) {
            root = (h + sqrtd) / a;
            if (!ray_t.surrounds(root))
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - current_center) / m_radius;
        rec.set_face_normal(r, outward_normal);
        get_sphere_uv(outward_normal, rec.u, rec.v);
        rec.mat = m_mat;

        return true;
    }

private:
    ray m_center;
    double m_radius;
    shared_ptr<material> m_mat;
    aabb m_bbox;

    static void get_sphere_uv(const point3& p, double& u, double& v) {
        // p: a given point on the sphere of radius one, centered at the origin.
        // u: returned value [0,1] of angle around the Y axis from X=-1.
        // v: returned value [0,1] of angle from Y=-1 to Y=+1.
        //     <1 0 0> yields <0.50 0.50>       <-1  0  0> yields <0.00 0.50>
        //     <0 1 0> yields <0.50 1.00>       < 0 -1  0> yields <0.50 0.00>
        //     <0 0 1> yields <0.25 0.50>       < 0  0 -1> yields <0.75 0.50>

        auto theta = std::acos(-p.y());
        auto phi = std::atan2(-p.z(), p.x()) + pi;

        u = phi / (2 * pi);
        v = theta / pi;
    }
};

#endif