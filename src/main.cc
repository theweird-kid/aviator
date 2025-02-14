#include <iostream>
#include "./headers/app.hpp"

int main(int argc, char *argv[]) {
    std::cout << "Welcome to Aviator!" << std::endl;
    Application app;
    app.run();
    return 0;
}
