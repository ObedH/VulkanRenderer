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

    // Create GLFW window
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
    this->connectWindowSurface();
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

void VulkanRenderer::connectWindowSurface() {
    
    // Make GLFW window surface
    VkSurfaceKHR surface;
    if(glfwCreateWindowSurface(this->vulkan_instance, this->window, nullptr, &surface) != VK_SUCCESS) {
        throw std::runtime_error("[ERROR]: Failed to create GLFW window surface for vulkan!");
    }
    this->surface = surface;
    std::cout << "[INFO]: Successfully created a GLFW window surface\n";

}

void VulkanRenderer::makeDevice() {

    // Choose physical device
    vk::PhysicalDevice physical_device = Device::choose_physical_device(this->vulkan_instance, this->debug_mode);
    if(physical_device == nullptr) {
        throw std::runtime_error("[ERROR]: Failed to choose physical device!");
    }
    this->physical_device = physical_device;
    std::cout << "[INFO]: Successfully chose a physical device\n";

    this->queue_family_indices = Device::find_queue_families(this->physical_device, this->surface, this->debug_mode);

    // Create logical device
    vk::Device logical_device = Device::create_logical_device(this->physical_device, this->queue_family_indices, this->debug_mode);
    if(logical_device == nullptr) {
        throw std::runtime_error("[ERROR]: Failed to create logical device!");
    }
    this->logical_device = logical_device;
    std::cout << "[INFO]: Successfully created a logical device\n";

    // Create queues
    std::array<vk::Queue,2> queues = Device::get_queue(this->logical_device, this->queue_family_indices, this->debug_mode);

    vk::Queue graphics_queue = queues[0];
    if(!graphics_queue) {
        throw std::runtime_error("[ERROR]: Failed to get graphics queue!");
    }
    this->graphics_queue = graphics_queue;
    std::cout << "[INFO]: Successfully got graphics queue\n";

    vk::Queue present_queue = queues[1];
    if(!present_queue) {
        throw std::runtime_error("[ERROR]: Failed to get present queue!");
    }
    this->graphics_queue = present_queue;

    // Query swapchain support
    Device::query_swapchain_support(this->physical_device, this->surface, this->debug_mode);

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

    this->logical_device.destroy();
    std::cout << "[INFO]: Successfully destroyed logical device\n";

    this->vulkan_instance.destroySurfaceKHR(this->surface);
    std::cout << "[INFO]: Successfully destroyed window surface\n";

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
