#pragma once
#include "vulkan/vulkan.h"
#include <vector>
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
    UVU_vk_queues(std::initializer_list<UVU_vk_queue*> queue_list);
    void setup_queues(VkPhysicalDevice physicalDevice);
    uint32_t get_queueCreateInfoCount() const;
    const VkDeviceQueueCreateInfo *get_queueCreateInfos() const;
    void recive_queues(VkDevice device);
private:
    void find_most_suitable_family(UVU_vk_queue *que, const std::vector<VkQueueFamilyProperties> &queueFamilyProperties, std::vector<uint32_t> &queues_in_family);
    uint32_t queue_flags_score(VkQueueFlags q, VkQueueFlags dv);
};