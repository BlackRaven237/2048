#include "include/RendererUI.h"
UI::UI() {}

UI::~UI() {}

void UI::Init(SDL_Window* window, SDL_Renderer* renderer) {
    // 1. Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    largeFont = io.Fonts->AddFontFromFileTTF("assets/fonts/Roboto-Bold.ttf", 16.0f);

    // 2. Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    // 3. Apply the custom "2048" style
    ApplyCustomTheme();
}

void UI::HandleEvent(const SDL_Event* event) {
    ImGui_ImplSDL3_ProcessEvent(event);
}

void UI::BeginFrame() {
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

bool UI::RenderGameUI(int currentScore, int bestScore) {
    bool resetGame = false;

    // Create a floating window for stats
    // We force a specific position (top-right) and size for consistency
    ImGui::SetNextWindowPos(ImVec2(-1.0f, 1.0f), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(200.0f, 100.0f), ImGuiCond_Always);

    ImGui::Begin("2048", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);

    // Use large text for the score
    ImGui::Text("SCORE");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 0.6f, 0.0f, 1.0f), "%d", currentScore); // Orange text

    ImGui::Text("BEST");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "%d", bestScore); // Grey text

    ImGui::Separator();
    
    // Add some spacing
    ImGui::Dummy(ImVec2(0.0f, 5.0f)); 

    // A nice big button that matches your Gunmetal theme
    if (ImGui::Button("RESET GAME", ImVec2(-1.0f, 25.0f))) { // -1.0f width = fill window
        resetGame = true;
    }

    ImGui::End();

    return resetGame;
}

void UI::Render(SDL_Renderer* renderer) {
    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
}

void UI::Shutdown() {
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}

void UI::ApplyCustomTheme() {
    ImGuiStyle& style = ImGui::GetStyle();
    
    // 1. Rounding - 2048 is all about rounded corners
    style.WindowRounding = 5.0f;
    style.FrameRounding = 5.0f;
    style.GrabRounding = 5.0f;

    // 2. Colors - Matching the "Gunmetal/Eggshell" vibe
    ImVec4* colors = style.Colors;
    
    // Background of the UI window (Gunmetal)
    colors[ImGuiCol_WindowBg] = ImVec4(0.16f, 0.20f, 0.22f, 0.95f); 
    
    // Title bar color (slightly lighter Gunmetal)
    colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.20f, 0.25f, 0.28f, 1.00f);

    // Button colors (The "New Game" button)
    colors[ImGuiCol_Button] = ImVec4(0.55f, 0.47f, 0.40f, 1.00f); // Warm brownish
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.60f, 0.52f, 0.45f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.50f, 0.42f, 0.35f, 1.00f);

    // Text Color (Eggshell White)
    colors[ImGuiCol_Text] = ImVec4(0.97f, 0.96f, 0.95f, 1.00f);
}