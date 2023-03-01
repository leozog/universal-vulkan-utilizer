#include "uvu/uvu_vk_queue.h"
#include "uvu/uvu_log.h"
#include "uvu/uvu_error.h"
#include "vulkan/vulkan.h"
#include <vector>
#include <initializer_list>


UVU_vk_queues::UVU_vk_queues(std::initializer_list<UVU_vk_queue*> queue_list) : _queue_list(queue_list) {}

void UVU_vk_queues::setup_queues(VkPhysicalDevice physicalDevice)
{
    uint32_t queueFamilyPropertyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyPropertyCount, nullptr);
    std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyPropertyCount);
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

uint32_t UVU_vk_queues::get_queueCreateInfoCount() const {return _queueCreateInfos.size();}

const VkDeviceQueueCreateInfo *UVU_vk_queues::get_queueCreateInfos() const {return _queueCreateInfos.data();}

void UVU_vk_queues::recive_queues(VkDevice device)
{
    for(auto que : _queue_list)
        vkGetDeviceQueue(device, que->queueFamilyIndex, que->queueIndex, &que->_queue);
}

void UVU_vk_queues::find_most_suitable_family(UVU_vk_queue *que, std::vector<VkQueueFamilyProperties> &queueFamilyProperties, std::vector<uint32_t> queues_in_family)
{
    uint32_t max_score = 0;
    uint32_t max_pos = 0;
    for(uint32_t i = 0; i < queueFamilyProperties.size(); i++)
    {
        if(queues_in_family[i] == queueFamilyProperties[i].queueCount)
            continue;
        uint32_t a = compare_flags(que->_flags, queueFamilyProperties[i].queueFlags);
        if(a > max_score)
        {
            max_score = a;
            max_pos = i;
        }
    }
    if(max_score == 0)
        uvu_err_exit("VK_CANT_LOCATE_QUEUE_FLAGS");

    
}

uint32_t UVU_vk_queues::compare_flags(VkQueueFlags a, VkQueueFlags b)
{
    if(a == b) return UINT32_MAX;
    
}