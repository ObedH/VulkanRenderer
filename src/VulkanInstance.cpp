#include "VulkanInstance.hpp"

#include <iostream>
#include <vector>

#include <GLFW/glfw3.h>


bool VulkanInstance::supported(std::vector<const char*>& extensions, std::vector<const char*>& layers, bool debug) {
    
    // Get supported extension properties
    std::vector<vk::ExtensionProperties> supported_extensions = vk::enumerateInstanceExtensionProperties();
    
    // Print extension info
    if(debug) {
        std::cout << "[DEBUG]: Device can support the following extensions:\n";
        for(vk::ExtensionProperties supported_extension : supported_extensions) {
            std::cout << "\t" << supported_extension.extensionName << "\n";
        }
    }

    // Check extension support
    bool found;
    for(const char* extension : extensions) {
        found = false;
        for(vk::ExtensionProperties supported_extension : supported_extensions) {
            if(strcmp(extension, supported_extension.extensionName) == 0) {
                found = true;
                if(debug) {
                    std::cout << "[DEBUG]: Extension \"" << extension << "\" is supported\n";
                }
            }
        }
        if(!found) {
            if(debug) {
                std::cout << "[DEBUG]: Extension \"" << extension << "\" is not supported\n";
            }
            return false;
        }
    }

    // Check layer support
    std::vector<vk::LayerProperties> supported_layers = vk::enumerateInstanceLayerProperties();
    if(debug) {
        std::cout << "[DEBUG]: Device can support the following layers:\n";
        for(vk::LayerProperties supported_layer : supported_layers) {
            std::cout << "\t" << supported_layer.layerName << "\n";
        }
    }

    for(const char* layer : layers) {
        found = false;
        for(vk::LayerProperties supported_layer : supported_layers) {
            if(strcmp(layer, supported_layer.layerName) == 0) {
                found = true;
                if(debug) {
                    std::cout << "[DEBUG]: Layer \"" << layer << "\" is supported\n";
                }
            }
        }
        if(!found) {
            if(debug) {
                std::cout << "[DEBUG]: Layer \"" << layer << "\" is not supported\n";
            }
            return false;
        }
    }


    return true;

}

vk::Instance VulkanInstance::make_instance(const char* application_name, bool debug) {

    // Get Vulkan instance version
    uint32_t version{ 0 };
    vkEnumerateInstanceVersion(&version);
    if(debug) {
        std::cout << "[DEBUG]: System can support Vulkan variant: "
            << VK_API_VERSION_VARIANT(version)
            << ", Version: " << VK_API_VERSION_MAJOR(version)
            << "." << VK_API_VERSION_MINOR(version)
            << "." << VK_API_VERSION_PATCH(version)
            << "\n";
    }

    version &= ~(0xFFFU);


    // Setup application info
    vk::ApplicationInfo app_info = vk::ApplicationInfo(
        "Simple Vulkan Renderer",
        version,
        "Simple Vulkan Engine",
        version,
        version
    );


    // Find extensions required by GLFW
    uint32_t glfw_extension_count = 0;
    const char** glfw_extensions;
    glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);
    std::vector<const char*> extensions(glfw_extensions, glfw_extensions + glfw_extension_count);
    if(debug) {
        extensions.push_back("VK_EXT_debug_utils");
    }
    if(debug) {
        std::cout << "[DEBUG]: Extensions to be requested:\n";
        for(const char* extension_name : extensions) {
            std::cout << "\t" << extension_name << "\n";
        }
    }


    // Declare enabled layers
    std::vector<const char*> layers;
    if(debug) {
        layers.push_back("VK_LAYER_KHRONOS_validation");
    }
    if(!supported(extensions, layers, debug)) {
        return nullptr;
    }


    // Setup instance create info
    vk::InstanceCreateInfo create_info = vk::InstanceCreateInfo(
        vk::InstanceCreateFlags(),
        &app_info,
        static_cast<uint32_t>(layers.size()), layers.data(),
        static_cast<uint32_t>(extensions.size()), extensions.data()
    );


    // Create the Vulkan instance
    try {
        return vk::createInstance(create_info, nullptr);
    }
    catch(vk::SystemError err) {
        return nullptr;
    }
}
