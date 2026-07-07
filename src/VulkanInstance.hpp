#pragma once

#include <vulkan/vulkan.hpp>

namespace VulkanInstance {
    bool supported(std::vector<const char*>& extensions, std::vector<const char*>& layers, bool debug);
    vk::Instance make_instance(const char* application_name, bool debug);
}
