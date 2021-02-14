//
// Created by 유승우 on 2021/02/14.
//

#ifndef RAY_TRACING_IN_CPP_MOVING_SPHERE_HPP
#define RAY_TRACING_IN_CPP_MOVING_SPHERE_HPP

#include "rtweekend.hpp"
#include "hittable.hpp"


class moving_sphere : public hittable {
public:
    moving_sphere() {}
    moving_sphere(
            point3 cen0, point3 cen1, double _time0, double _time1, double r, shared_ptr<material> m)
            : center0(cen0), center1(cen1), time0(_time0), time1(_time1), radius(r), mat_ptr(m)
    {};

    virtual bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec) const override;

    point3 center(double time) const;

public:
    point3 center0, center1;
    double time0, time1;
    double radius;
    shared_ptr<material> mat_ptr;
};

bool moving_sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
    vector3 oc = r.origin() - center(r.time());
    auto a = r.direction().length_squared();
    auto half_b = dot_product(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;

    auto discriminant = half_b * half_b - a*c;

    // sphere is hit by the ray if and only if the equation has real solutions
    if (discriminant > 0)
    {
        // Solve for the solution that contains the actual parameter to get the point.
        auto root = sqrt(discriminant);

        // try smaller 't' first
        auto temp = (-half_b - root) / a;
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            // the point of the surface that was hit by the ray
            rec.p = r.at(rec.t);
            // here, we define a normal vector to point outward
            vector3 outward_normal = (rec.p - center(r.time())) / radius;
            // compare the direction of the ray & outward_normal
            // set the normal, opposite to the direction where light came from
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;
            return true;
        }

        // try larger 't' then
        temp = (-half_b + root) / a;

        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.at(rec.t);
            vector3 outward_normal = (rec.p - center(r.time())) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }

    return false;
}

point3 moving_sphere::center(double time) const {
    return center0 + ((time - time0) / (time1 - time0))*(center1 - center0);
}

#endif //RAY_TRACING_IN_CPP_MOVING_SPHERE_HPP
