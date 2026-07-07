#include "VulkanRenderer.hpp"

#include <iostream>
#include <stdexcept>

#include "VulkanInstance.hpp"
#include "DebugMessenger.hpp"



/* ==================== SETUP ==================== */

void VulkanRenderer::init() {

    this->initGLFW();
    this->createWindow();
    this->initVulkan();

}

void VulkanRenderer::initGLFW() {
    
    // Set GLFW Error callback
    glfwSetErrorCallback(glfw_error_callback);


    // Initialize GLFW
    if(!glfwInit()) {
        throw std::runtime_error("[ERROR]: GLFW initialization failed");
    }
    std::cout << "[INFO]: GLFW initialization successful\n";

}

void VulkanRenderer::createWindow() {

    // Create GLFW Window
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(this->width, this->height, "Vulkan Renderer", nullptr, nullptr);
    if(window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("[ERROR]: GLFW window creation failed");
    }
    std::cout << "[INFO]: GLFW window creation successful\n";
    this->window = window;

}

void VulkanRenderer::initVulkan() {

    this->makeInstance();
    this->makeDynamicDispatchLoader();
    this->makeDebugMessenger();
    this->makeDevice();

}

void VulkanRenderer::makeInstance() {

    // Create instance
    this->vulkan_instance = VulkanInstance::make_instance("Vulkan Renderer", this->debug_mode);
    std::cout << "[INFO]: Successfully created a Vulkan instance\n";

}

void VulkanRenderer::makeDynamicDispatchLoader() {

    // Create dynamic dispatch loader
    this->dldi = vk::detail::DispatchLoaderDynamic(this->vulkan_instance, vkGetInstanceProcAddr);
    std::cout << "[INFO]: Successfully created a dynamic dispatch loader\n";

}

void VulkanRenderer::makeDebugMessenger() {

    // Create debug messenger
    this->debug_messenger = DebugMessenger::make_debug_messenger(this->vulkan_instance, this->dldi);
    std::cout << "[INFO]: Successfully created a debug messenger\n";

}

void VulkanRenderer::makeDevice() {

}


/* ==================== RUNNING ==================== */

void VulkanRenderer::run() {
    
}


/* ==================== CLEANUP ==================== */

void VulkanRenderer::cleanup() {
    this->cleanupVulkan();
    this->destroyWindow();
    this->destroyGLFW();
}

void VulkanRenderer::cleanupVulkan() {
    this->vulkan_instance.destroyDebugUtilsMessengerEXT(this->debug_messenger, nullptr, dldi);
    std::cout << "[INFO]: Successfully destroyed debug messenger\n";
    this->vulkan_instance.destroy();
    std::cout << "[INFO]: Successfully destroyed Vulkan instance\n";
}

void VulkanRenderer::destroyWindow() {

    glfwDestroyWindow(this->window);
    std::cout << "[INFO]: Successfully closed GLFW window\n";

}

void VulkanRenderer::destroyGLFW() {

    glfwTerminate();
    std::cout << "[INFO]: Successfully terminated GLFW\n";

}

/* ==================== ERROR HANDLING ==================== */

void glfw_error_callback(int error, const char* description) {
    std::cerr << "GLFW Error [" << error << "]: " << description << "\n";
}
