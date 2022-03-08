#include "GuiBuilder.h"

GuiBuilder::GuiBuilder()
{
    setupWindow();
    setGlVersion();
    createWindow();
    m_io = setupContext();
    setupStyle();
    setupPlatform();
    loadFonts(m_io);
}

GuiBuilder::~GuiBuilder()
{
}

int
GuiBuilder::setupWindow()
{
    // Setup window
    glfwSetErrorCallback(glfwErrorCallback);
    if (!glfwInit())
        return -1;
}

void
GuiBuilder::setGlVersion()
{
    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on Mac
#else
    // GL 3.0 + GLSL 130
    m_glslVersion = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif
}

int
GuiBuilder::createWindow()
{
    // Create window with graphics context
    m_window = glfwCreateWindow(1280, 720, "Universal modbus configure", NULL, NULL);
    if (m_window == NULL)
        return -1;

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1); // Enable vsync
}

ImGuiIO&
GuiBuilder::setupContext()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)m_io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows
    // io.ConfigViewportsNoAutoMerge = true;
    // io.ConfigViewportsNoTaskBarIcon = true;

    return io;
}

void
GuiBuilder::setupStyle()
{
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsClassic();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    m_style = ImGui::GetStyle();
    if (m_io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        m_style.WindowRounding = 0.0f;
        m_style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
}

void
GuiBuilder::setupPlatform()
{
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(m_glslVersion);
}

void
GuiBuilder::loadFonts(ImGuiIO& io)
{
    // Load Fonts
    io.Fonts->AddFontDefault();
    io.Fonts->AddFontFromFileTTF("C:\\_Projects\\C++\\Universal-Modbus-ImGUI\\Support\\Fonts\\LiberationMono-Regular.ttf", 18.0f);
}

void
GuiBuilder::glfwErrorCallback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int
GuiBuilder::build()
{
    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    bool enableBackground = true;
    bool showExchange = true;

    m_clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    while (!glfwWindowShouldClose(m_window)) {

        // Main loop
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        BackgroundWindow::instance()->Show(&enableBackground);

        ExchangeWindow::instance()->Show(&showExchange);
        std::time_t result = std::time(nullptr);
        std::string msg = std::asctime(std::localtime(&result));
        ExchangeWindow::instance()->AddMessage("[%05d] Hello, current time is %.1f'\n", ImGui::GetFrameCount(), ImGui::GetTime());

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(m_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(m_clearColor.x * m_clearColor.w, m_clearColor.y * m_clearColor.w, m_clearColor.z * m_clearColor.w, m_clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (m_io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            m_backupCurrentContext = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(m_backupCurrentContext);
        }
        glfwSwapBuffers(m_window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_window);
    glfwTerminate();

    return 0;
}