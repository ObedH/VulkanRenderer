#include "Device.hpp"

#include <iostream>
#include <set>



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

std::vector<std::string> Device::log_transform_bits(vk::SurfaceTransformFlagsKHR bits) {
    std::vector<std::string> result;

    if(bits & vk::SurfaceTransformFlagBitsKHR::eIdentity) {
        result.push_back("identity");
    }
    if(bits & vk::SurfaceTransformFlagBitsKHR::eRotate90) {
        result.push_back("90 degree rotation");
    }
    if(bits & vk::SurfaceTransformFlagBitsKHR::eRotate180) {
        result.push_back("180 degree rotation");
    }
    if(bits & vk::SurfaceTransformFlagBitsKHR::eRotate270) {
        result.push_back("270 degree rotation");
    }
    if(bits & vk::SurfaceTransformFlagBitsKHR::eHorizontalMirror) {
        result.push_back("horizontal mirror");
    }
    if(bits & vk::SurfaceTransformFlagBitsKHR::eHorizontalMirrorRotate90) {
        result.push_back("horizontal mirror, then 90 degree rotation");
    }
    if(bits & vk::SurfaceTransformFlagBitsKHR::eHorizontalMirrorRotate180) {
        result.push_back("horizontal mirror, then 180 degree rotation");
    }
    if(bits & vk::SurfaceTransformFlagBitsKHR::eHorizontalMirrorRotate270) {
        result.push_back("horizontal mirror, then 270 degree rotation");
    }
    if(bits & vk::SurfaceTransformFlagBitsKHR::eInherit) {
        result.push_back("inherit");
    }

    return result;
    
}

std::vector<std::string> Device::log_alpha_composite_bits(vk::CompositeAlphaFlagsKHR bits) {

    std::vector<std::string> result;

    if(bits & vk::CompositeAlphaFlagBitsKHR::eOpaque) {
        result.push_back("opaque (alpha ignored)");
    }
    if(bits & vk::CompositeAlphaFlagBitsKHR::ePreMultiplied) {
        result.push_back("pre multiplied (alpha expected to already be multiplied in image)");
    }
    if(bits & vk::CompositeAlphaFlagBitsKHR::ePostMultiplied) {
        result.push_back("post multiplied (alpha will be applied during composition)");
    }
    if(bits & vk::CompositeAlphaFlagBitsKHR::eInherit) {
        result.push_back("inherited");
    }

    return result;

}

std::vector<std::string> Device::log_image_usage_bits(vk::ImageUsageFlags bits) {
    
    std::vector<std::string> result;

    if(bits & vk::ImageUsageFlagBits::eTransferSrc) {
        result.push_back("transfer src: image can be used as the source of a transfer command.");
    }
    if(bits & vk::ImageUsageFlagBits::eTransferDst) {
        result.push_back("transfer dst: image can be used as the destination of a transfer command.");
    }
    if(bits & vk::ImageUsageFlagBits::eSampled) {
        result.push_back("sampled: image can be used to create a VkImageView suitable for occupying a VkDescriptorSet slot either of type VK_DESCRIPTOR_TYPE_SAMPLED_IAMGE or VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, and be sampled by a shader.");
    }
    if(bits & vk::ImageUsageFlagBits::eStorage) {
        result.push_back("storage: image can be used to create a VkImageView suitable for occupying a VkDescriptorSet slot of type VK_DESCRIPTOR_TYPE_STORAGE_IMAGE.");
    }
    if(bits & vk::ImageUsageFlagBits::eColorAttachment) {
        result.push_back("color attachment: image can be used to create a VkImageView suitable for use as a color or resolve attachment in a VkFrameBuffer.");
    }
    if(bits & vk::ImageUsageFlagBits::eDepthStencilAttachment) {
        result.push_back("depth/stencil attachment: image can be used to create a VkImageView suitable for use as a depth/stencil or depth/stencil resolve attachment in a VkFramebuffer.");
    }
    if(bits & vk::ImageUsageFlagBits::eTransientAttachment) {
        result.push_back("transient attachment: implementations may support using memory allocations with the VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT to back an image with this usage. This bit can be set for any image that can be used to create a VkImageView suitable for use as a color, resolve, depth/stencil, or input attachment.");
    }
    if(bits & vk::ImageUsageFlagBits::eInputAttachment) {
        result.push_back("input attachment: image can be used to create a VkImageView suitable for occupying VkDescriptorSet slot of type VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT; be read from a shader as an input attachment; and be used as an input attachment in a framebuffer.");
    }
    if(bits & vk::ImageUsageFlagBits::eFragmentDensityMapEXT) {
        result.push_back("fragment density map: image can be used to create a VkImageView suitable for use as a fragment density map image.");
    }
    if(bits & vk::ImageUsageFlagBits::eFragmentShadingRateAttachmentKHR) {
        result.push_back("fragment shading rate attachment: image can be used to create a VkImageView suitable for use as a fragment shading rate attachment or shading rate image.");
    }

    return result;

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

Device::QueueFamilyIndices Device::find_queue_families(vk::PhysicalDevice device, vk::SurfaceKHR surface, bool debug) {

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
            if(debug) {
                std::cout << "\tQueue family " << i << " is suitable for graphics\n";
            }
        }

        if(device.getSurfaceSupportKHR(i, surface)) {
            indices.present_family = i;
            if(debug) {
                std::cout << "\tQueue family " << i << " is suitable for presenting\n";
            }
        }

        if(indices.is_complete()) {
            break;
        }

        i ++;
    }

    return indices;

}

vk::Device Device::create_logical_device(vk::PhysicalDevice physical_device, Device::QueueFamilyIndices indices, bool debug) {
    

    // Build queue creation info
    std::vector<uint32_t> unique_indices;
    unique_indices.push_back(indices.graphics_family.value());
    if(indices.graphics_family.value() != indices.present_family.value()) {
        unique_indices.push_back(indices.present_family.value());
    }
    float queue_priority = 1.0f;

    std::vector<vk::DeviceQueueCreateInfo> queue_create_info;
    for(uint32_t queue_family_index : unique_indices) {
        queue_create_info.push_back(
            vk::DeviceQueueCreateInfo(
                vk::DeviceQueueCreateFlags(),
                indices.graphics_family.value(),
                1, &queue_priority
            )
        );
    }


    // Request device extensions
    std::vector<const char*> device_extensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };


    vk::PhysicalDeviceFeatures device_features = vk::PhysicalDeviceFeatures();


    // Declare enabled layers
    std::vector<const char*> enabled_layers;
    if(debug) {
        enabled_layers.push_back("VK_LAYER_KHRONOS_validation");
    }


    // Build device creation info
    vk::DeviceCreateInfo device_create_info = vk::DeviceCreateInfo(
        vk::DeviceCreateFlags(),
        queue_create_info.size(), queue_create_info.data(),
        enabled_layers.size(), enabled_layers.data(),
        device_extensions.size(), device_extensions.data(),
        &device_features
    );

    try {
        vk::Device device = physical_device.createDevice(device_create_info);
        return device;
    }
    catch(vk::SystemError err) {
        return nullptr;
    }

}

std::array<vk::Queue,2> Device::get_queue(vk::Device logical_device, QueueFamilyIndices indices, bool debug) {

    return {
        {
            logical_device.getQueue(indices.graphics_family.value(), 0),
            logical_device.getQueue(indices.present_family.value(), 0)
        }
    };
}
Device::SwapChainSupportDetails Device::query_swapchain_support(vk::PhysicalDevice device, vk::SurfaceKHR surface, bool debug) {

    SwapChainSupportDetails support;

    support.capabilities = device.getSurfaceCapabilitiesKHR(surface);

    if(debug) {
        // TODO: These values look REALLY suspicious!
        std::cout << "[DEBUG]: Swapchain can support the following surface capabilities:\n";
        std::cout << "\tMinimum image count: " << support.capabilities.minImageCount << "\n";
        std::cout << "\tMaximum image count: " << support.capabilities.maxImageCount << "\n";

        std::cout << "\tCurrent extent:\n";
        std::cout << "\t\tWidth: " << support.capabilities.currentExtent.width << '\n';
        std::cout << "\t\tHeight: " << support.capabilities.currentExtent.height << '\n';

        std::cout << "\tMinimum supported extent: \n";
        std::cout << "\t\tWidth: " << support.capabilities.minImageExtent.width << '\n';
        std::cout << "\t\tHeight: " << support.capabilities.minImageExtent.height << '\n';

        std::cout << "\tMaximum supported extent: \n";
        std::cout << "\t\tWidth: " << support.capabilities.maxImageExtent.width << '\n';
        std::cout << "\t\tHeight: " << support.capabilities.maxImageExtent.height << '\n';

        std::cout << "\tMaximum image array layers: " << support.capabilities.maxImageArrayLayers << '\n';
        
        std::cout << "\tSupported transforms:\n";
        std::vector<std::string> string_list = log_transform_bits(support.capabilities.supportedTransforms);
        for(std::string line : string_list) {
            std::cout << "\t\t" << line << '\n';
        }

        std::cout << "\tCurrent transforms:\n";
        string_list = log_transform_bits(support.capabilities.currentTransform);
        for(std::string line : string_list) {
            std::cout << "\t\t" << line << '\n';
        }

        std::cout << "\tSupported alpha operations:\n";
        string_list = log_alpha_composite_bits(support.capabilities.supportedCompositeAlpha);
        for(std::string line : string_list) {
            std::cout << "\t\t" << line << '\n';
        }

        std::cout << "\tSupported image usage:\n";
        string_list = log_image_usage_bits(support.capabilities.supportedUsageFlags);
        for(std::string line : string_list) {
            std::cout << "\t\t" << line << '\n';
        }
    }

    support.formats = device.getSurfaceFormatsKHR(surface);
    if(debug) {
        for(vk::SurfaceFormatKHR supported_format : support.formats) {
            std::cout << "\tSupported pixel format: " << vk::to_string(supported_format.format) << '\n';
            std::cout << "\tSupported color space: " << vk::to_string(supported_format.colorSpace) << '\n';
        }
    }

    return support;

}
