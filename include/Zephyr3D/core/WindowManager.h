#ifndef WindowManager_h
#define WindowManager_h

#include "IWindow.h"

namespace zephyr {

class WindowManager : public IWindow {
    friend void framebuffer_size_callback(GLFWwindow* window, int width, int height);

public:
    void Initialize(unsigned int width, unsigned int heigth, const std::string& title);

    bool ShouldClose() const override;

    unsigned int Width() const override { return m_Width; }
    unsigned int Height() const override {return m_Height; }
    std::string Title() const override { return m_Title; }
    void Title(const std::string& title) override;

    GLFWwindow* Handle() const override { return m_GLFWHandler; }

private:
    GLFWwindow* m_GLFWHandler{ nullptr };
    unsigned int m_Width{ 0 };
    unsigned int m_Height{ 0 };
    std::string m_Title{};
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

}

#endif
