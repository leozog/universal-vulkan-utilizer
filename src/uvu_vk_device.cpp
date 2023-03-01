#include "uvu/uvu_vk_device.h"
#include "uvu/uvu_log.h"
#include "uvu/uvu_error.h"
#include "uvu/uvu_vk_queue.h"
#include "vulkan/vulkan.h"
#include <vector>
#include <string>

UVU_vk_device::UVU_vk_device(const VkInstance instance, UVU_vk_queues queues)
{
    uint32_t deviceCount = 0;
    uvu_err_vk(vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr));
    std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
    uvu_err_vk(vkEnumeratePhysicalDevices(instance, &deviceCount, physicalDevices.data()));

    VkPhysicalDevice physicalDevice = choose_physical_device(physicalDevices);

    queues.setup_queues(physicalDevice);

    /*VkDeviceQueueCreateInfo queueCreateInfo={};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.pNext = nullptr;
    queueCreateInfo.flags = 0 ;
    queueCreateInfo.queueFamilyIndex

    VkDeviceCreateInfo createInfo={};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pNext = nullptr;
    createInfo.flags = 0;
    createInfo.queueCreateInfoCount = queues.get_queueCreateInfoCount();
    createInfo.pQueueCreateInfos = queues.get_queueCreateInfos();
    createInfo.enabledExtensionCount = 0;
    createInfo.ppEnabledExtensionNames = {};
    createInfo.pEnabledFeatures = NULL;

    uvu_err_vk(vkCreateDevice(physicalDevices[0], &createInfo, nullptr, &_device));*/
}

UVU_vk_device::~UVU_vk_device()
{
    vkDestroyDevice(_device, nullptr);
}

UVU_vk_device::operator VkDevice()
{
    return _device;
}

VkPhysicalDevice UVU_vk_device::choose_physical_device(std::vector<VkPhysicalDevice> &physicalDevices)
{
    VkPhysicalDeviceProperties properties;
    vkGetPhysicalDeviceProperties(physicalDevices[0], &properties);
    uvu_log(properties.deviceName);
    return physicalDevices[0];
}
