
set(LIBRARY ${CMAKE_PROJECT_NAME}_lib)

file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/include/*.h")

add_library(${LIBRARY} 
    Tuple.cpp 
    Color.cpp
    Canvas.cpp
    Transformation.cpp
    Ray.cpp
    Shape.cpp
    Sphere.cpp
    Intersection.cpp
    World.cpp
    Camera.cpp
    Renderer.cpp
    ${HEADER_LIST})

target_include_directories(${LIBRARY} PUBLIC ../include)
