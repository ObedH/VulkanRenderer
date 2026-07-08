#pragma once

#include <iostream>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vulkan/vulkan.hpp>

#include "Device.hpp"



class VulkanRenderer {
    public:
/* ==================== PUBLIC API ==================== */
        VulkanRenderer() {
            std::cout << "[INFO]: Starting new Vulkan Renderer instance\n";
            this->init();
        }
        ~VulkanRenderer() {
            std::cout << "[INFO]: Ending Vulkan Renderer instance\n";
            this->cleanup();
        }
        void run();

    private:
/* ==================== INTERNAL VARIABLES ==================== */
        
        bool debug_mode{ true };

        int width{ 800 };
        int height{ 600 };
        GLFWwindow* window{ nullptr };

        vk::Instance vulkan_instance{ nullptr };
        vk::detail::DispatchLoaderDynamic dldi;
        vk::DebugUtilsMessengerEXT debug_messenger{ nullptr };
        vk::SurfaceKHR surface{ nullptr };

        vk::PhysicalDevice physical_device{ nullptr };
        vk::Device logical_device{ nullptr };
        vk::Queue graphics_queue{ nullptr };
        vk::Queue present_queue{ nullptr };

        Device::QueueFamilyIndices queue_family_indices;


    private:
/* ==================== SETUP ==================== */
        void init();
        void initGLFW();
        void createWindow();
        void initVulkan();
        void makeInstance();
        void makeDynamicDispatchLoader();
        void makeDebugMessenger();
        void connectWindowSurface();
        void makeDevice();

/* ==================== CLEANUP ==================== */
        void cleanup();
        void cleanupVulkan();
        void destroyWindow();
        void destroyGLFW();
};

void glfw_error_callback(int error_code, const char* description);
