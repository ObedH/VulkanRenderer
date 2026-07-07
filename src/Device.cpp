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
    }

    return nullptr;

}
