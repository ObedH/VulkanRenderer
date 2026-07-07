#pragma once

#include <vulkan/vulkan.hpp>



namespace DebugMessenger {

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        vk::DebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        vk::Flags<vk::DebugUtilsMessageTypeFlagBitsEXT> messageType,
        const vk::DebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData
    );

    vk::DebugUtilsMessengerEXT make_debug_messenger(vk::Instance& instance, vk::detail::DispatchLoaderDynamic& dldi);

}
