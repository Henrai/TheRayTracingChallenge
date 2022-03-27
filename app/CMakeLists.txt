add_executable(projecile projectile.cpp)
target_link_libraries(projecile PRIVATE RayTracer_lib )

add_executable(clock clock.cpp)
target_link_libraries(clock PRIVATE RayTracer_lib )


add_executable(silhouette silhouette.cpp)
target_link_libraries(silhouette PRIVATE RayTracer_lib )


add_executable(phong_shading phong_shading.cpp)
target_link_libraries(phong_shading PRIVATE RayTracer_lib )

add_executable(scene Scene.cpp)
target_link_libraries(scene PRIVATE RayTracer_lib )
