#pragma once
#include "uvu/uvu_log.h"
#include "vulkan/vk_enum_string_helper.h"
#include <iostream>

void uvu_err_exit(std::string str)
{
    uvu_log(str);
    exit(-1);
}

void uvu_err_vk(VkResult result)
{
    if(result != VK_SUCCESS)
        uvu_err_exit(string_VkResult(result));
}