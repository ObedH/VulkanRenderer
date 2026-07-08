#pragma once

#include <optional>

#include <vulkan/vulkan.hpp>



namespace Device {

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphics_family;
        std::optional<uint32_t> present_family;

        bool is_complete() {
            return graphics_family.has_value() && present_family.has_value();
        }
    };
    
    bool check_device_extension_support(const vk::PhysicalDevice& device, const std::vector<const char*>& requested_extensions, bool debug);
    void log_device_properties(const vk::PhysicalDevice& device);
    bool is_suitable(const vk::PhysicalDevice& device, bool debug);
    vk::PhysicalDevice choose_physical_device(vk::Instance& instance, bool debug);

    QueueFamilyIndices find_queue_families(vk::PhysicalDevice device, bool debug);

    vk::Device create_logical_device(vk::PhysicalDevice physical_device, QueueFamilyIndices indices, bool debug);
    vk::Queue get_queue(vk::PhysicalDevice physical_device, vk::Device logical_device, QueueFamilyIndices indices, bool debug);

}
