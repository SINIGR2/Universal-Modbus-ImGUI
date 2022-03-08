#pragma once

#include "CommunicationManager/CommunicationManager.h"
#include "View/BackgroundWindow/BackgroundWindow.h"
#include "View/ExchangeWindow/ExchangeWindow.h"
#include "View/StartUpWindow/StartUpWindow.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include <iostream>

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

class GuiBuilder {
public:
    GuiBuilder();
    ~GuiBuilder();

    void loop();

private:
    int setupWindow();
    void setGlVersion();
    int createWindow();
    void setupContext();
    void setupStyle();
    void setupPlatform();
    void loadFonts();

    static void glfwErrorCallback(int error, const char* description);

    GLFWwindow* m_window;
    ImGuiIO m_io;
    ImGuiStyle m_style;
    ImVec4 m_clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    const char* m_glslVersion;
};
