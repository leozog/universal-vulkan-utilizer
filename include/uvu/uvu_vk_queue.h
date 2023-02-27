#pragma once
#include "uvu/uvu_log.h"
#include "uvu/uvu_error.h"
#include "vulkan/vulkan.h"
#include <initializer_list>

class UVU_vk_queue
{
    friend class UVU_vk_queues;
private:
    VkQueue _queue;
    VkQueueFlags _flags;
    float _priority;

    uint32_t queueFamilyIndex;
    uint32_t queueIndex;
public:
    UVU_vk_queue(VkQueueFlags flags, float priority) : _flags(flags), _priority(priority) {}
    operator VkQueue() {return _queue;}
    void submit();
};

class UVU_vk_queues
{
private:
    std::vector<UVU_vk_queue*> _queue_list;
    std::vector<VkDeviceQueueCreateInfo> _queueCreateInfos;
public:
    UVU_vk_queues(std::initializer_list<UVU_vk_queue*> queue_list) : _queue_list(queue_list) {}
    void setup_queues(VkPhysicalDevice physicalDevice)
    {
        uint32_t queueFamilyPropertyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyPropertyCount, nullptr);
        std::vector<VkQueueFamilyProperties> queueFamilyProperties.resize(queueFamilyPropertyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyPropertyCount, queueFamilyProperties.data());
        
        uvu_log(std::to_string((int)queueFamilyPropertyCount));
        for(auto que : queueFamilyProperties)
        {
            uvu_log((que.queueFlags & VK_QUEUE_GRAPHICS_BIT) ? "VK_QUEUE_GRAPHICS_BIT " : "", 0);
            uvu_log((que.queueFlags & VK_QUEUE_COMPUTE_BIT) ? "VK_QUEUE_COMPUTE_BIT " : "", 0);
            uvu_log((que.queueFlags & VK_QUEUE_TRANSFER_BIT) ? "VK_QUEUE_TRANSFER_BIT " : "", 0);
            uvu_log((que.queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) ? "VK_QUEUE_SPARSE_BINDING_BIT " : "", 0);
            uvu_log((que.queueFlags & VK_QUEUE_PROTECTED_BIT) ? "VK_QUEUE_PROTECTED_BIT " : "");
            uvu_log(std::to_string((int)que.queueCount));
        }

        std::vector<uint32_t> queues_in_family(queueFamilyPropertyCount);
        for(uint32_t &i : queues_in_family)
            i = 0;
        for(auto que : _queue_list)
        {
            find_most_suitable_family(que, queueFamilyProperties, queues_in_family);
        }
    }
    uint32_t get_queueCreateInfoCount() const {return _queueCreateInfos.size();}
    const VkDeviceQueueCreateInfo *get_queueCreateInfos() const {return _queueCreateInfos.data();}
    void recive_queues(VkDevice device)
    {
        for(auto que : _queue_list)
            vkGetDeviceQueue(device, que->queueFamilyIndex, que->queueIndex, &que->_queue);
    }
private:
    void find_most_suitable_family(UVU_vk_queue que, std::vector<VkQueueFamilyProperties> &queueFamilyProperties, std::vector<uint32_t> queues_in_family)
    {
        uint32_t max_score = 0;
        uint32_t max_pos = 0;
        for(uint32_t i = 0; i < queueFamilyProperties.size(); i++)
        {
            if(queues_in_family[i] == queueFamilyProperties[i].queueCount)
                continue;
            uint32_t a = compare_flags(que._flags, queueFamilyProperties[i].queueFlags);
            if(a > max_score)
            {
                max_score = a;
                max_pos = i;
            }
        }
        if(max_score == 0)
            uvu_err_exit("VK_CANT_LOCATE_QUEUE_FLAGS");

        
    }
    uint32_t compare_flags(VkQueueFlags a, VkQueueFlags b)
    {
        if(a == b) return UINT32_MAX;
        
    }
};