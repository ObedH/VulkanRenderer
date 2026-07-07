#pragma once

#include <vulkan/vulkan.hpp>

namespace Device {
    
    bool check_device_extension_support(const vk::PhysicalDevice& device, const std::vector<const char*>& requested_extensions, bool debug);
    void log_device_properties(const vk::PhysicalDevice& device);
    bool is_suitable(const vk::PhysicalDevice& device, bool debug);
    vk::PhysicalDevice choose_physical_device(vk::Instance& instance, bool debug);

}
