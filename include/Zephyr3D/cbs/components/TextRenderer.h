#ifndef TextRenderer_h
#define TextRenderer_h

#include "Component.h"
#include "../../rendering/DrawManager.h"
#include "../../rendering/IGUIWidget.h"
#include "../connections/MessageIn.h"

#include <string>

namespace zephyr::cbs {

constexpr char* TITLE_PREFIX = "__dummy";

class TextRenderer : public Component, public rendering::IGUIWidget {
public:
    TextRenderer(class Object& object, ID_t id, EAlign horizontal, EAlign vertical, float size, const std::string& font_path = "");

    void Initialize() override;
    void Destroy() override;

    void Draw() const override;

    void Font(const std::string& path, float size);
    void LocalPosition(glm::vec2 offset, EAlign horizontal, EAlign vertical);

    const std::string Text() const { return m_Text; }
    void Text(std::string text) { m_Text = text; }

    const glm::vec4 Color() const { return m_Color; }
    void Color(glm::vec4 color) { m_Color = color; }

public:
    MessageIn<std::string, TextRenderer, &TextRenderer::Text> TextIn{ this };
    MessageIn<glm::vec4, TextRenderer, &TextRenderer::Color> ColorIn{ this };

private:
    static unsigned int s_Index;

    std::string m_Title { TITLE_PREFIX };
    std::string m_Text;

    EAlign m_Horizontal;
    EAlign m_Vertical;
    glm::vec2 m_Offset{ 0.0f };
    glm::vec4 m_Color{ 1.0f };
    ImFont* m_Font;
};

}

#endif