#include <iostream>
#include <exception>

#include "VulkanRenderer.hpp"

int main() {

    try {
        VulkanRenderer renderer;

        renderer.run();
    }
    catch(const std::exception& e) {
        std::cerr << "Initialization aborted: " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
