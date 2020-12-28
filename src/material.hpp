//
// Created by 유승우 on 2020/05/21.
//

#ifndef FIRSTRAYTRACER_MATERIAL_HPP
#define FIRSTRAYTRACER_MATERIAL_HPP


#include "ray.hpp"
#include "hittable.hpp"

/*
 * Generalized, abstract class for different materials
 * The common roles of various material classes are:
 * 1. If the object didn't fully absorbed incident ray, produce a scattered ray
 * 2. (If 1), determine how much the scattered ray is attenuated compared to incident ray
 *
 * In short, the material of the surface tells the ray tracer how rays interact with the surface.
 */
class material
{
public:
    virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
            ) const = 0;
};

/*
 * Metal material class
 */
class metal : public material
{
public:
    // Constructor
    metal(const color& a, double f) : albedo(a), fuzz(f < 1 ? f: 1) {}

public:
    color albedo;
    double fuzz;

    virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
            ) const
    {
        vector3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);

        // since we passed a reference of variable, the scattered ray is determined here.
        // the fuzziness determines the clarity of metal surface. if it's value gets large
        // the metal gets closer to diffuse material
        scattered = ray(rec.p, reflected + fuzz*random_in_unit_sphere());
        attenuation = albedo;
        return (dot_product(scattered.direction(), rec.normal) > 0);
    }
};

/*
 * Lambertian(diffuse) material class
 */
class lambertian : public material
{
public:
    color albedo;

public:
    lambertian(const color& a) : albedo(a) {}

    virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
            ) const
    {
        vector3 scatter_direction = rec.normal + random_in_unit_sphere();

        // since we passed a reference of variable, the scattered ray is determined here.
        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }
};

#endif //FIRSTRAYTRACER_MATERIAL_HPP
