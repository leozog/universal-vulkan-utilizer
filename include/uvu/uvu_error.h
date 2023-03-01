#pragma once
#include "uvu/uvu_log.h"
#include "vulkan/vk_enum_string_helper.h"
#include <string>

void uvu_err_exit(std::string str);
void uvu_err_vk(VkResult result);