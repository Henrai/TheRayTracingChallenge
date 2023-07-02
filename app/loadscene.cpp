#include <World.h>

int main(int argc, char** argv) {
    World world;
    world.LoadSecne(argv[1]);
    world.render();
}