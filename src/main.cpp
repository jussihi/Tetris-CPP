#include "graphics.hpp"
#include "TetrisClasses.hpp"
#include <iostream>


static GameState gameState = sStop;

void keyCallbackListener(GLFWwindow* w_window, int32_t w_key, int32_t w_scanCode, int32_t w_action, int32_t w_modKeys)
{
    if(w_key == GLFW_KEY_ESCAPE && w_action == GLFW_PRESS)
    {
        gameState = sQuit;
    }
}

void errorCallbackListener(int w_error, const char* w_description)
{
    puts(w_description);
}

GLFWwindow* setupWindow()
{
        glfwSetErrorCallback(errorCallbackListener);

    if(!glfwInit())
    {
        return nullptr;
    }

    glfwWindowHint(GLFW_RESIZABLE, (int32_t)false);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, (int32_t)true);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Classic tetris", nullptr, nullptr);

    glfwMakeContextCurrent(window);

    if(!window)
    {
        glfwTerminate();
        return nullptr;
    }

    return window;
}

int main(void)
{
    GLFWwindow* gameWindow = setupWindow();

    glfwSetErrorCallback(errorCallbackListener);

    if(!gameWindow)
    {
        std::cout << "Failed to initialize window. Exiting." << std::endl;
        return -1;
    }

    glfwSetKeyCallback(gameWindow, keyCallbackListener);

    // initialize game params here
    TetrisGame* tetrisGame = new TetrisGame();


    while(!glfwWindowShouldClose(gameWindow))
    {
        if(gameState == sQuit)
        {
            break;
        }

        std::cout << "In game loop" << std::endl;
    }

    std::cout << "out" << std::endl;

    return 0;
}
