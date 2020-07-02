# ImGUI Shade Bindings
Shade bindings for the widely used Dear ImGui.

## Installation
Simply copy the `src` and `include` directories into an existing Shade project.

## Usage
To use, you should call the following methods in your application:
```
void YourApplication::init()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsClassic();

    ImGui_ImplShade_Init(this);
}

void YourApplication::destroy()
{
    // Cleanup Dear ImGui
    ImGui_ImplShade_Shutdown();
    ImGui::DestroyContext();
}

void YourApplication::render()
{
    // Start the Dear ImGui frame
    ImGui_ImplShade_NewFrame();
    ImGui::NewFrame();

    // Show demo window
    ImGui::ShowDemoWindow();

    // Render
    ImGui::Render();
    ImGui_ImplShade_RenderDrawData(ImGui::GetDrawData());
}
```