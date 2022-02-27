add_executable(projecile projectile.cpp)
target_link_libraries(projecile PRIVATE RayTracer_lib )

add_executable(clock clock.cpp)
target_link_libraries(clock PRIVATE RayTracer_lib )

