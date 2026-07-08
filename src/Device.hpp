#pragma once

#include <optional>
#include <vector>
#include <string>

#include <vulkan/vulkan.hpp>



namespace Device {

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphics_family;
        std::optional<uint32_t> present_family;

        bool is_complete() {
            return graphics_family.has_value() && present_family.has_value();
        }
    };

    struct SwapChainSupportDetails {
        vk::SurfaceCapabilitiesKHR capabilities;
        std::vector<vk::SurfaceFormatKHR> formats;
        std::vector<vk::PresentModeKHR> present_modes;
    };
    
    bool check_device_extension_support(const vk::PhysicalDevice& device, const std::vector<const char*>& requested_extensions, bool debug);
    void log_device_properties(const vk::PhysicalDevice& device);
    std::vector<std::string> log_transform_bits(vk::SurfaceTransformFlagsKHR bits);
    bool is_suitable(const vk::PhysicalDevice& device, bool debug);
    vk::PhysicalDevice choose_physical_device(vk::Instance& instance, bool debug);

    QueueFamilyIndices find_queue_families(vk::PhysicalDevice device, vk::SurfaceKHR, bool debug);

    vk::Device create_logical_device(vk::PhysicalDevice physical_device, QueueFamilyIndices indices, bool debug);
    std::array<vk::Queue,2> get_queue(vk::Device logical_device, QueueFamilyIndices indices, bool debug);

    SwapChainSupportDetails query_swapchain_support(vk::PhysicalDevice device, vk::SurfaceKHR surface, bool debug);

}
