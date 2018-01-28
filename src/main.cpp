#include "graphics.hpp"

void keyCallbackListener(GLFWwindow* w_window, int32_t w_key, int32_t w_scanCode, int32_t w_action, int32_t w_modKeys)
{

}

GLFWwindow* setupWindow()
{
    if(!glfwInit())
    {
        return nullptr;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Classic tetris", nullptr, nullptr);

    glfwMakeContextCurrent(window);

    return window;
}

int main(void)
{
    GLFWwindow* gameWindow = setupWindow();
    if(!gameWindow)
    {
        return -1;
    }

    glfwSetKeyCallback(gameWindow, keyCallbackListener);

    return 0;
}
