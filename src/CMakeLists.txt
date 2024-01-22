add_library (src 
aabb.cpp
bvh_node.cpp
camera.cpp
color.cpp
common.cpp
dielectric.cpp
hit_record.cpp
hittable.cpp
hittable_list.cpp
interval.cpp
# lambertian.cpp
material.cpp
# metal.cpp
ray.cpp
sphere.cpp
vec3.cpp
)

target_include_directories(src PUBLIC "${PROJECT_SOURCE_DIR}/include")