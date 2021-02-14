# renderer using cpu only
add_executable(rt-cpu main.cpp camera.hpp color.hpp
        hittable.hpp hittable_list.hpp aabb.hpp material.hpp lambertian.hpp
        metal.hpp dielectric.hpp ray.hpp rtweekend.hpp
        sphere.hpp moving_sphere.hpp vector3.hpp)