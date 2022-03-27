#pragma once

class Camera;
class World;
class Canvas;
//TODO: support path tracing.
class Renderer
{
public:
    Canvas Render(const World& world, const Camera& camera);
};

