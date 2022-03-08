#include "StartUpWindow.h"

void
StartUpWindow::HelperMarker(const char* desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

void
StartUpWindow::ShowStartUpWindow(bool* pOpen)
{
    // Exceptionally add an extra assert here for people confused about initial Dear ImGui setup
    // Most ImGui functions would normally just crash if the context is missing.
    IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing dear imgui context. Refer to examples app!");

//    m_isShowWidgets = true;
    ShowWidgets();

}

void
StartUpWindow::ShowWidgets()
{
    if (!ImGui::CollapsingHeader("Widgets"))
        return;

    static int clicked = 0;
    if (ImGui::Button("Button"))
        clicked++;
    if (clicked & 1)
    {
        ImGui::SameLine();
        ImGui::Text("Thanks for clicking me!");
    }
}
