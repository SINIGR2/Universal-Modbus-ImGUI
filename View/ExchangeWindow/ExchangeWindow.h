#pragma once
#include <xstring>
#include "common.h"
#include "imgui.h"


class ExchangeWindow {
public:
    ~ExchangeWindow();

    ExchangeWindow(const ExchangeWindow&) = delete;
    ExchangeWindow(ExchangeWindow&&) = delete;
    ExchangeWindow& operator=(const ExchangeWindow&) = delete;
    ExchangeWindow& operator=(ExchangeWindow&&) = delete;

    static ExchangeWindow*
    instance()
    {
        if(!m_instance)
            m_instance = new ExchangeWindow();
        return m_instance;
    }

    void Show(bool* pOpen);
    void AddMessage(const char* fmt, ...) IM_FMTARGS(2);

private:
    ExchangeWindow();
    void Clear();
    void Copy();

    ImGuiTextBuffer m_exchangeBuffer;
    ImGuiWindowFlags m_windowFlags;
    ImGuiDockNodeFlags m_dockSpaceFlags;
    ImVector<int> m_lines;
    bool m_autoscroll;
    static ExchangeWindow* m_instance;

    bool m_clear = false;
    bool m_copy = false;

    std::string m_title = "Exchange";
};
