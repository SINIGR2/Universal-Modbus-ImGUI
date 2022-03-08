#include "BackgroundWindow.h"
#include "common.h"

BackgroundWindow* BackgroundWindow::m_instance = 0;

BackgroundWindow::BackgroundWindow()
    : m_dockspaceId(ImGui::GetID("MyDockSpace"))
{
    m_windowFlags = ImGuiWindowFlags_MenuBar;
    m_windowFlags |= ImGuiWindowFlags_NoDocking;
}

BackgroundWindow::~BackgroundWindow()
{
    if (m_instance)
        delete m_instance;
}

BackgroundWindow*
BackgroundWindow::instance()
{
    if (!m_instance)
        m_instance = new BackgroundWindow();
    return m_instance;
}

void
BackgroundWindow::Show(bool* pOpen)
{
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    m_dockspaceFlags = ImGuiDockNodeFlags_None;

    m_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(m_viewport->WorkPos);
    ImGui::SetNextWindowSize(m_viewport->WorkSize);
    ImGui::SetNextWindowViewport(m_viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    setWindowFlags();

    if (m_dockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode) {
        m_windowFlags |= ImGuiWindowFlags_NoBackground;
    }

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace", pOpen, m_windowFlags);
    ImGui::PopStyleVar();
    ImGui::PopStyleVar(2);

    ImGui::DockSpace(m_dockspaceId, ImVec2(0.0f, 0.0f), m_dockspaceFlags);

    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("Menu")) {
            ImGui::Separator();

            if (ImGui::MenuItem("Exit", NULL, false, pOpen != NULL))
                *pOpen = false;
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
    ImGui::End();
}

void
BackgroundWindow::setWindowFlags()
{
    m_windowFlags |= ImGuiWindowFlags_NoTitleBar;
    m_windowFlags |= ImGuiWindowFlags_NoCollapse;
    m_windowFlags |= ImGuiWindowFlags_NoResize;
    m_windowFlags |= ImGuiWindowFlags_NoMove;
    m_windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    m_windowFlags |= ImGuiWindowFlags_NoNavFocus;
}
