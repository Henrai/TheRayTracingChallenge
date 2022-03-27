#include <Renderer.h>
#include <Canvas.h>
#include <Camera.h>
#include <World.h>
#include <Ray.h>

Canvas Renderer::Render(const World& world, const Camera& camera) {
    Canvas canvas(camera.getHorizontalSize(), camera.getVerticalSize());
    for (int i = 0; i < camera.getHorizontalSize(); i++) {
        for (int j = 0; j < camera.getVerticalSize(); j++) {
            Ray r = camera.RayFromPixel(i,j);
            Color c = world.ColorAt(r);
            canvas[i][j] = c;
        }
    }
    return canvas;
}