#pragma once
#include "vulkan/vulkan.h"
#include <vector>

class UVU_vk_instance
{
private:
    VkInstance _instance;
public:
    UVU_vk_instance(const char* ApplicationName, const std::vector<const char*> &layers, const std::vector<const char*> &extensions);
    ~UVU_vk_instance();
    operator VkInstance();
};