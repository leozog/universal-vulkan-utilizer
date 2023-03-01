#pragma once
#include "uvu/uvu_vk_queue.h"
#include "vulkan/vulkan.h"
#include <vector>

class UVU_vk_device
{
private:
    VkDevice _device;
public:
    UVU_vk_device(const VkInstance instance, UVU_vk_queues queues);
    ~UVU_vk_device();
    operator VkDevice();
private:
    VkPhysicalDevice choose_physical_device(std::vector<VkPhysicalDevice> &physicalDevices);
};