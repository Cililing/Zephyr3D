#ifndef IWindow_h
#define IWindow_h

#pragma warning(push, 0)
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#pragma warning(pop)

#include <string>

namespace zephyr {

class IWindow {
public:
    IWindow() = default;
    IWindow(const IWindow&) = delete;
    IWindow& operator=(const IWindow&) = delete;
    IWindow(IWindow&&) = delete;
    IWindow& operator=(IWindow&&) = delete;
    virtual ~IWindow() = default;

    virtual bool ShouldClose() const = 0;
    virtual unsigned int Width() const = 0;
    virtual unsigned int Height() const = 0;
    virtual std::string Title() const = 0;
    virtual void Title(const std::string& title) = 0;

    virtual GLFWwindow* Pointer() const = 0;
    virtual operator GLFWwindow* () const = 0;
};

}

#endif
