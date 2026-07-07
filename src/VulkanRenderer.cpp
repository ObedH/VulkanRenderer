#include "VulkanRenderer.hpp"

#include <iostream>
#include <stdexcept>

#include "VulkanInstance.hpp"
#include "DebugMessenger.hpp"
#include "Device.hpp"



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
        throw std::runtime_error("[ERROR]: GLFW window creation failed!");
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
    vk::Instance vulkan_instance = VulkanInstance::make_instance("Vulkan Renderer", this->debug_mode);
    if(vulkan_instance == nullptr) {
        throw std::runtime_error("[ERROR]: Failed to create Vulkan instance!");
    }
    this->vulkan_instance = vulkan_instance;
    std::cout << "[INFO]: Successfully created a Vulkan instance\n";

}

void VulkanRenderer::makeDynamicDispatchLoader() {

    // Create dynamic dispatch loader
    vk::detail::DispatchLoaderDynamic dldi = vk::detail::DispatchLoaderDynamic(this->vulkan_instance, vkGetInstanceProcAddr);
    if(!dldi.vkCreateDevice || !dldi.vkDestroyDevice) {
        throw std::runtime_error("[ERROR]: Failed to create dynamic dispatch loader!");
    }
    this->dldi = dldi;
    std::cout << "[INFO]: Successfully created a dynamic dispatch loader\n";

}

void VulkanRenderer::makeDebugMessenger() {

    // Create debug messenger
    vk::DebugUtilsMessengerEXT debug_messenger = DebugMessenger::make_debug_messenger(this->vulkan_instance, this->dldi);
    if(debug_messenger == nullptr) {
        throw std::runtime_error("[ERROR]: Failed to create debug messenger!");
    }
    this->debug_messenger = debug_messenger;
    std::cout << "[INFO]: Successfully created a debug messenger\n";

}

void VulkanRenderer::makeDevice() {

    // Choose physical device
    vk::PhysicalDevice physical_device = Device::choose_physical_device(this->vulkan_instance, this->debug_mode);
    if(physical_device == nullptr) {
        throw std::runtime_error("[ERROR]: Failed to choose physical device!");
    }
    this->physical_device = physical_device;
    std::cout << "[INFO]: Successfully chose a physical device\n";
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
