#include "Device.hpp"

#include <iostream>
#include <set>
#include <vector>



void Device::log_device_properties(const vk::PhysicalDevice& device) {
    
    // Print device name and type
    vk::PhysicalDeviceProperties properties = device.getProperties();

    std::cout << "\tDevice name: " << properties.deviceName << "\n";
    std::cout << "\tDevice type: ";
    switch(properties.deviceType) {
        case(vk::PhysicalDeviceType::eCpu):
            std::cout << "CPU\n";
            break;
        case(vk::PhysicalDeviceType::eDiscreteGpu):
            std::cout << "Discrete GPU\n";
            break;
        case(vk::PhysicalDeviceType::eIntegratedGpu):
            std::cout << "Integrated GPU\n";
            break;
        case(vk::PhysicalDeviceType::eVirtualGpu):
            std::cout << "Virtual GPU\n";
            break;
        default:
            std::cout << "Other\n";
    }

}

bool Device::check_device_extension_support(const vk::PhysicalDevice& device, const std::vector<const char*>& requested_extensions, bool debug) {

    // Check each required extension to see if it is supported
    std::set<std::string> required_extensions(requested_extensions.begin(), requested_extensions.end());

    if(debug) {
        std::cout << "[DEBUG]: Device can support the following extensions:\n";
    }
    for(vk::ExtensionProperties& extension : device.enumerateDeviceExtensionProperties()) {
        if(debug) {
            std::cout << "\t" << extension.extensionName << "\n";
        }

        required_extensions.erase(extension.extensionName);
    }

    return required_extensions.empty();

}

bool Device::is_suitable(const vk::PhysicalDevice& device, bool debug) {

    // Declare required extensions
    const std::vector<const char*> requested_extensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    if(debug) {
        std::cout << "[DEBUG]: Requesting the following device extensions:\n";
        for(const char* extension : requested_extensions) {
            std::cout << "\t" << extension << "\n";
        }
    }

    // Check compatibility with this extension
    if(bool extensions_supported = check_device_extension_support(device, requested_extensions, debug)) {
        if(debug) {
            std::cout << "[DEBUG]: Device can support the requested extensions\n";
        }
    }
    else {
        if(debug) {
            std::cout << "[DEBUG]: Device cannot support the requested extensions\n";
        }
        return false;
    }

    return true;

}

vk::PhysicalDevice Device::choose_physical_device(vk::Instance& instance, bool debug) {


    std::vector<vk::PhysicalDevice> available_devices = instance.enumeratePhysicalDevices();


    // Check if a suitable device can be found
    if(debug) {
        std::cout << "[DEBUG]: There are " << available_devices.size() << " physical devices available on the system\n";
    }

    for(vk::PhysicalDevice device : available_devices) {
        if(debug) {
            log_device_properties(device);
        }
        if(is_suitable(device, debug)) {
            return device;
        }
    }

    return nullptr;

}

Device::QueueFamilyIndices Device::find_queue_families(vk::PhysicalDevice device, bool debug) {

    // Query the device's supported queue families
    QueueFamilyIndices indices;
    std::vector<vk::QueueFamilyProperties> queue_families = device.getQueueFamilyProperties();

    // Log number of supported queue families
    if(debug) {
        std::cout << "[DEBUG]: Device can support " << queue_families.size() << " queue families.\n";
    }

    // Find which of the queue families supports graphics and presenting
    int i = 0;
    for(vk::QueueFamilyProperties queue_family : queue_families) {
        if(queue_family.queueFlags & vk::QueueFlagBits::eGraphics) {
            indices.graphics_family = i;
            // TODO: Reconsider this assumption
            indices.present_family = i;

            if(debug) {
                std::cout << "\tQueue family " << i << " is suitable for graphics and presenting.\n";
            }
        }

        if(indices.is_complete()) {
            break;
        }

        i ++;
    }

    return indices;

}
