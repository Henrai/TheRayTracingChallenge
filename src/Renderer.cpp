#include <Renderer.h>
#include <Canvas.h>
#include <Camera.h>
#include <World.h>
#include <Ray.h>
#include <tbb/parallel_for.h>
#include <tbb/task_arena.h>
#include <chrono>

#include <iostream>

Canvas Renderer::Render(const World& world, const Camera& camera) {
    Canvas canvas(camera.getHorizontalSize(), camera.getVerticalSize());
    tbb::task_arena ta(10);
    auto start = std::chrono::steady_clock::now();
    ta.execute([&] {
        tbb::parallel_for(tbb::blocked_range<size_t>(0, camera.getHorizontalSize()), 
            [&] (tbb::blocked_range<size_t> r) {
                for(size_t i = r.begin(); i < r.end(); i++) {
                    for (int j = 0; j < camera.getVerticalSize(); j++) {
                       //if (i == 125 && j == 125) {
                            Ray r = camera.RayFromPixel(i,j);
                            std::cout << r.Direction() << " " << r.Origin() <<std::endl;
                            Color c = world.ColorAt(r);
                            canvas[i][j] = c;
                        //}
                    }
                }
        }, tbb::simple_partitioner{});
    });
    auto finish = std::chrono::steady_clock::now();
    auto dt = finish - start;
    long long ms = std::chrono::duration_cast<std::chrono::milliseconds>(dt).count();
    std::cout << "time elapsed: " << ms << std::endl;
    return canvas;
}