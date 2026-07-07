#include "Device.hpp"

#include <iostream>



void Device::log_device_properties(const vk::PhysicalDevice& device) {
    
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

bool Device::check_device_extension_support(const vk::PhysicalDevice& device, const std::vector<const char*>& requested_extension, bool debug) {



}

bool Device::is_suitable(const vk::PhysicalDevice& device, bool debug) {

    const std::vector<const char*> requested_extensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    if(debug) {
        std::cout << "[DEBUG]: Requesting the following device extensions:\n";
        for(const char* extension : requested_extensions) {
            std::cout << "\t" << extension << "\n";
        }
    }

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
