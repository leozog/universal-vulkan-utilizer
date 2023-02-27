#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>

#include "uvu/uvu.h"
#include "uvu/uvu_vk_queue.h"

class UVU_compute : private UVU
{
private:
    UVU_vk_queue queue1;
    UVU_vk_queue queue2;
public:
    UVU_compute() :
        queue1(0, 1),
        queue2(0, 0.5),
        UVU({&queue1, &queue2})
    {

    }
};

int main() {
    {
        UVU_compute uvu;
    }
    return 0;
}