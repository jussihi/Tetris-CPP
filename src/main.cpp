#include "graphics.hpp"
#include "TetrisClasses.hpp"
#include <iostream>


static GameState gameState = sPlay;

static const double cFPS = 60;
static const double cDeltaTime = 1 / cFPS;

static const double cTickRate = 1.0 / 120.0;

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
    TetrisGrid tetrisGrid(10, 20);
    TetrisGame* tetrisGame = new TetrisGame(tetrisGrid, cTickRate);

    double lastTick = 0.0;
    double lastRender = 0.0;
    double currTime = glfwGetTime();

    while(!glfwWindowShouldClose(gameWindow))
    {
        // help polling with the while loop.
        glfwPollEvents();

        if(gameState == sPlay)
        {
            currTime = glfwGetTime();
            if(currTime - lastTick >= cTickRate)
            {
                lastTick = currTime;
                tetrisGame->tick();
            }

            // would it be better left this be as it was in the last call?
            currTime = glfwGetTime();
            if(currTime - lastRender >= cDeltaTime)
            {
                lastRender = currTime;
                // render game (update ?)
            }

        }

        if(gameState == sQuit)
        {
            break;
        }
    }

    std::cout << "out" << std::endl;

    return 0;
}
