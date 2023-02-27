#pragma once
#include "uvu/uvu_log.h"
#include "uvu/uvu_error.h"
#include "uvu/uvu_vk_instance.h"
#include "uvu/uvu_vk_device.h"
#include "uvu/uvu_vk_queue.h"
#include <vector>


#if defined(__ANDROID__)
#define VK_USE_PLATFORM_ANDROID_KHR
#elif defined(__linux__)
#define VK_USE_PLATFORM_XLIB_KHR
#elif defined(_WIN32)
#define VK_USE_PLATFORM_WIN32_KHR
#endif

//universal_vulkan_utilizer
class UVU
{
protected:
    const char *_name;
    const std::vector<const char*> _layers;
    const std::vector<const char*> _extensions;
    UVU_vk_queues _vk_queues;
    UVU_vk_instance _vk_instance;
    UVU_vk_device _vk_device;
public:
    UVU(std::initializer_list<UVU_vk_queue*> vk_queues) :
        _name{"uvu_test"},
        _layers{"VK_LAYER_KHRONOS_validation"},
        _extensions{},
        _vk_queues(vk_queues),
        _vk_instance(_name, _layers, _extensions),
        _vk_device(_vk_instance, _vk_queues)
    {
        
    }
    ~UVU()
    {
        
    }
};