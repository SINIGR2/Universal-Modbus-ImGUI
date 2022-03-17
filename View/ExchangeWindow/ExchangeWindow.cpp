#include "ExchangeWindow.h"

ExchangeWindow* ExchangeWindow::m_instance = 0;

ExchangeWindow::ExchangeWindow()
    : m_windowFlags(0)
{
    m_windowFlags |= ImGuiWindowFlags_MenuBar;
}

ExchangeWindow::~ExchangeWindow()
{
    delete m_instance;
}

void
ExchangeWindow::Show(bool* pOpen)
{
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

    if (!ImGui::Begin(m_title.c_str(), pOpen, m_windowFlags)) {
        ImGui::End();
        return;
    }

//    ImGui::PushItemWidth(ImGui::GetFontSize() * -12);

    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("Настройки")) {
            ImGui::Checkbox("Автопрокрутка", &m_autoscroll);
            ImGui::Separator();
            if (ImGui::MenuItem("Очистить", NULL, false, true))
                Clear();
            if (ImGui::MenuItem("Копировать", NULL, false, true))
                Copy();
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::Separator();
    ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

    ImGui::TextUnformatted(m_exchangeBuffer.begin(), m_exchangeBuffer.end());

    if (m_autoscroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        ImGui::SetScrollHereY(1.0f);

    ImGui::EndChild();
    ImGui::End();
}

void
ExchangeWindow::AddMessage(const char* fmt, ...)
{
    int old_size = m_exchangeBuffer.size();
    va_list args;
    va_start(args, fmt);
    m_exchangeBuffer.appendfv(fmt, args);
    va_end(args);
    for (int new_size = m_exchangeBuffer.size(); old_size < new_size; old_size++)
        if (m_exchangeBuffer[old_size] == '\n')
            m_lines.push_back(old_size + 1);
}

void
ExchangeWindow::Clear()
{
    m_exchangeBuffer.clear();
    m_lines.clear();
    m_lines.push_back(0);
}

void
ExchangeWindow::Copy()
{
}
