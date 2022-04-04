
set(LIBRARY ${CMAKE_PROJECT_NAME}_lib)

file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/include/*.h")

find_package(TBB REQUIRED)

add_library(${LIBRARY} 
    Tuple.cpp 
    Color.cpp
    Canvas.cpp
    Transformation.cpp
    Ray.cpp
    Shapes/Shape.cpp
    Shapes/Sphere.cpp
    Shapes/Plane.cpp
    Intersection.cpp
    World.cpp
    Camera.cpp
    Renderer.cpp
    ${HEADER_LIST})
target_link_libraries(${LIBRARY} PRIVATE TBB::tbb)
target_include_directories(${LIBRARY} PUBLIC ../include)
