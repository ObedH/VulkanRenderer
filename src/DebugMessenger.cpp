#include "DebugMessenger.hpp"

#include <iostream>



static VKAPI_ATTR VkBool32 VKAPI_CALL DebugMessenger::debugCallback(
    vk::DebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    vk::Flags<vk::DebugUtilsMessageTypeFlagBitsEXT> messageType,
    const vk::DebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData
) {
    std::cerr << "[VALIDATION LAYER]: " << pCallbackData->pMessage << std::endl;
    return VK_FALSE;
}

vk::DebugUtilsMessengerEXT DebugMessenger::make_debug_messenger(vk::Instance& instance, vk::detail::DispatchLoaderDynamic& dldi) {
    
    vk::DebugUtilsMessengerCreateInfoEXT create_info(
        {},
        vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
        vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
        vk::DebugUtilsMessageSeverityFlagBitsEXT::eError,
        vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
        vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation |
        vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance,
        debugCallback,
        nullptr
    );

    return instance.createDebugUtilsMessengerEXT(create_info, nullptr, dldi);
}


