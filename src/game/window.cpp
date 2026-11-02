// Glad needs to be included first
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class mcWindow
{
private:
    GLFWwindow *window{nullptr};

    mcWindow(int w, int h, char *title, GLFWmonitor *monitor, GLFWwindow *share)
    {
        window = glfwCreateWindow(w, h, title, monitor, share);
    }

    ~mcWindow()
    {
        delete window;
    }

public:
    GLFWwindow *getWindow()
    {
        return window;
    }
};