#include "engine/Engine.hh"

int main() {
    auto e = Engine(1920, 1080);
    e.run("github", 200, 1, 60);

    return 0;
}