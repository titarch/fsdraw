#include "engine/Engine.hh"

int main() {
    auto e = Engine(2560, 1440);
    e.run("github", 200, 1);

    return 0;
}