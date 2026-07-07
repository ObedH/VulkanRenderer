#pragma once

#include <vulkan/vulkan.hpp>

namespace Device {
    
    void log_device_properties(const vk::PhysicalDevice& device);
    vk::PhysicalDevice choose_physical_device(vk::Instance& instance, bool debug);

}
