#include "TextRenderer.h"

unsigned int zephyr::cbs::TextRenderer::s_Index = 1;

zephyr::cbs::TextRenderer::TextRenderer(class Object& object, ID_t id, EAlign horizontal, EAlign vertical, float size, const std::string& font_path)
    : Component(object, id)
    , m_Horizontal(horizontal)
    , m_Vertical(vertical)
    , m_Offset(0.0f)
    , m_Color(0.0f, 0.0f, 0.0f, 1.0f) {

    ImGuiIO& io = ImGui::GetIO();

    if (font_path.empty()) {
        // TODO deafult font with resize
        m_Font = io.Fonts->Fonts[0];
    } else {
        m_Font = io.Fonts->AddFontFromFileTTF(font_path.c_str(), size);
        io.Fonts->Build();
    }

    m_Title.append(std::to_string(s_Index));
    s_Index++;
}

void zephyr::cbs::TextRenderer::Initialize() {
    Object().Scene().RegisterGUIWidget(this);
}

void zephyr::cbs::TextRenderer::Destroy() {
    Object().Scene().UnregisterGUIWidget(this);
}

void zephyr::cbs::TextRenderer::Draw() const {
    ImGui::Begin(m_Title.c_str(), nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::PushFont(m_Font);

    const glm::vec2 margin = ImGui::GetWindowContentRegionMin();       // Might not be correct
    const glm::vec2 text_size = ImGui::CalcTextSize(m_Text.c_str());

    glm::vec2 pos(0.0f, 0.0f);
    pos.x = pos.x + m_Offset.x * zephyr::ZephyrEngine::Instance().GetWindow().Width();
    pos.y = pos.y + m_Offset.y * zephyr::ZephyrEngine::Instance().GetWindow().Height();
    IGUIWidget::Align(&pos.x, -margin.x / 2, zephyr::ZephyrEngine::Instance().GetWindow().Width() - margin.x / 2 - text_size.x, m_Horizontal);
    IGUIWidget::Align(&pos.y, -margin.y / 2, zephyr::ZephyrEngine::Instance().GetWindow().Height() - margin.y / 2 - text_size.y, m_Vertical);

    ImGui::SetWindowPos(pos);
    ImGui::TextColored(m_Color, m_Text.c_str());

    ImGui::PopFont();
    ImGui::End();
}

void zephyr::cbs::TextRenderer::Font(const std::string& path, float size) {
    ImGuiIO& io = ImGui::GetIO();
    m_Font = io.Fonts->AddFontFromFileTTF(path.c_str(), size);
    io.Fonts->Build();
}

void zephyr::cbs::TextRenderer::Position(glm::vec2 offset, EAlign horizontal, EAlign vertical) {
    m_Offset = offset;
    m_Vertical = vertical;
    m_Horizontal = horizontal;
}
