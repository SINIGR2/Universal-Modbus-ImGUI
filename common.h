#pragma once

#include "imgui.h"
#include "iso646.h"

typedef signed long ssize_t;
typedef unsigned char byte;
typedef signed char sbyte;

const byte ModbusAsciiHeader = ':';

enum ModbusCommandMode {
    NONE = -1,
    ASCII,
    RTU
};

static void
HelpMarker(const char* desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered()) {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}