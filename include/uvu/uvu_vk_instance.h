#pragma once
#include "uvu/uvu_error.h"
#include "vulkan/vulkan.h"
#include <vector>

class UVU_vk_instance
{
private:
    VkInstance _instance;
public:
    UVU_vk_instance(const char* ApplicationName, const std::vector<const char*> &layers, const std::vector<const char*> &extensions)
    {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pNext = nullptr;
        appInfo.pApplicationName = ApplicationName;
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "uvu";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pNext = nullptr;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledLayerCount = static_cast<uint32_t>(layers.size());
        createInfo.ppEnabledLayerNames = layers.data();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        uvu_err_vk(vkCreateInstance(&createInfo, nullptr, &_instance));
    }
    ~UVU_vk_instance()
    {
        vkDestroyInstance(_instance, nullptr);
    }
    operator VkInstance()
    {
        return _instance;
    }
};