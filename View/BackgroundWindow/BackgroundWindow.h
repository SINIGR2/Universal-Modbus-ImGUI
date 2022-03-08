#pragma once

#include "imgui.h"

class BackgroundWindow {
public:
    ~BackgroundWindow();

    BackgroundWindow(const BackgroundWindow&) = delete;
    BackgroundWindow(BackgroundWindow&&) = delete;
    BackgroundWindow& operator=(const BackgroundWindow&) = delete;
    BackgroundWindow& operator=(BackgroundWindow&&) = delete;

    static BackgroundWindow* instance();
    void Show(bool* pOpen = (bool*)true);

private:
    BackgroundWindow();

    void setWindowFlags();

    ImGuiWindowFlags m_windowFlags;
    ImGuiDockNodeFlags m_dockspaceFlags;
    ImGuiID m_dockspaceId;
    const ImGuiViewport* m_viewport;
    static BackgroundWindow* m_instance;
};
