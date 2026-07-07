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

    // Create instance
    this->vulkan_instance = VulkanInstance::make_instance("Vulkan Renderer", this->debug_mode);
    std::cout << "[INFO]: Successfully created a Vulkan instance\n";

    // Create dynamic dispatch loader
    this->dldi = vk::detail::DispatchLoaderDynamic(this->vulkan_instance, vkGetInstanceProcAddr);

    // Create debug messenger
    this->makeDebugMessenger();

}

void VulkanRenderer::makeDebugMessenger() {
    this->debug_messenger = DebugMessenger::make_debug_messenger(this->vulkan_instance, this->dldi);
    std::cout << "[INFO]: Successfully created a debug messenger\n";
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

}

void VulkanRenderer::destroyWindow() {

    std::cout << "[INFO]: Closing GLFW window\n";
    glfwDestroyWindow(this->window);

}

void VulkanRenderer::destroyGLFW() {

    std::cout << "[INFO]: Terminating GLFW\n";
    glfwTerminate();

}

/* ==================== ERROR HANDLING ==================== */

void glfw_error_callback(int error, const char* description) {
    std::cerr << "GLFW Error [" << error << "]: " << description << "\n";
}
