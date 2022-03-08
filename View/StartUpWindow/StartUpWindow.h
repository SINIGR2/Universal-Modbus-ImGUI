#pragma once

#include "common.h"
#include "imgui.h"

class StartUpWindow {
public:
    static void HelperMarker(const char* desc);

    static void ShowStartUpWindow(bool* pOpen);

private:
    static void ShowWidgets();

    static bool m_isShowWidgets;
};