#pragma once

#include <vulkan/vulkan.hpp>

namespace Device {
    vk::PhysicalDevice choose_physical_device(vk::Instance& instance, bool debug);
}
