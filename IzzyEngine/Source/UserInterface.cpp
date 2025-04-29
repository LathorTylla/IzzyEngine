#include "UserInterface.h"
#include "Prerequisites.h"

UserInterface::UserInterface() {
}

UserInterface::~UserInterface() {
}

void 
UserInterface::init(void* window, 
                    ID3D11Device* device, 
                    ID3D11DeviceContext* deviceContext){
  IMGUI_CHECKVERSION(); // Check ImGui version
  ImGui::CreateContext(); // Create ImGui context
  ImGuiIO& io = ImGui::GetIO(); // Get ImGui IO
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable keyboard navigation
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable docking

  ImGui::StyleColorsClassic();  // Set default style

  setupStyle(); // Setup custom style

  ImGuiStyle& style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    style.WindowRounding = 0.0f; 
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  ImGui_ImplWin32_Init(window); // Initialize Win32
  ImGui_ImplDX11_Init(device, deviceContext); // Initialize DX11
}

void 
UserInterface::update(){
  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();
  ImGui::NewFrame();
}

void 
UserInterface::render(){
  ImGui::Render();  // Render ImGui
  ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());  // Render draw data
  ImGuiIO& io = ImGui::GetIO(); // Get ImGui IO
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    ImGui::UpdatePlatformWindows(); // Update platform windows
    ImGui::RenderPlatformWindowsDefault();  // Render platform windows
  }
}

void 
UserInterface::destroy(){
  ImGui_ImplDX11_Shutdown();  // Shutdown DX11
  ImGui_ImplWin32_Shutdown();  // Shutdown Win32
  ImGui::DestroyContext();  // Destroy ImGui context
}

void 
UserInterface::setupStyle(){

  ImGui::StyleColorsClassic();  // Set default style
  ImGuiStyle& style = ImGui::GetStyle();  // Get ImGui style
  style.WindowRounding = 5.3f;  // Set window rounding
  style.FrameRounding = 4.0f; // Set frame rounding
  style.ScrollbarRounding = 5.0f; // Set scrollbar rounding
  style.GrabRounding = 3.0f;  // Set grab rounding
  style.TabRounding = 3.0f; // Set tab rounding
  style.WindowPadding = ImVec2(10, 10); // Set window padding
  style.FramePadding = ImVec2(5, 5); // Set frame padding
  style.ItemSpacing = ImVec2(8, 8); // Set item spacing
  style.ItemInnerSpacing = ImVec2(5, 5); // Set item inner spacing

  ImVec4 neonPink = ImVec4(1.0f, 0.07f, 0.58f, 1.0f); // Neon pink color
  ImVec4 neonBlue = ImVec4(0.0f, 0.5f, 1.0f, 1.0f); // Neon blue color
  ImVec4 neonGreen = ImVec4(0.0f, 1.0f, 0.5f, 1.0f); // Neon green color
  ImVec4 backgroundColor = ImVec4(0.05f, 0.05f, 0.1f, 1.0f); // Background color
  ImVec4 activeGlow = ImVec4(1.0f, 1.0f, 0.0f, 1.0f); // Active glow color

  ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = backgroundColor;  // Set window background color
  ImGui::GetStyle().Colors[ImGuiCol_TitleBgActive] = neonPink;  // Set title background active color
  ImGui::GetStyle().Colors[ImGuiCol_TitleBg] = backgroundColor; // Set title background color
  ImGui::GetStyle().Colors[ImGuiCol_Border] = neonPink; // Set border color
  ImGui::GetStyle().Colors[ImGuiCol_FrameBg] = ImVec4(0.2f, 0.2f, 0.24f, 1.0f); // Set frame background color
  ImGui::GetStyle().Colors[ImGuiCol_FrameBgHovered] = neonBlue; // Set frame background hovered color
  ImGui::GetStyle().Colors[ImGuiCol_FrameBgActive] = neonGreen; // Set frame background active color
  ImGui::GetStyle().Colors[ImGuiCol_Button] = neonPink; // Set button color
  ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = neonBlue; // Set button hovered color
  ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] = activeGlow; // Set button active color
  ImGui::GetStyle().Colors[ImGuiCol_Header] = neonGreen; // Set header color
  ImGui::GetStyle().Colors[ImGuiCol_HeaderHovered] = neonBlue; // Set header hovered color
  ImGui::GetStyle().Colors[ImGuiCol_HeaderActive] = neonPink; // Set header active color

  ImGui::GetStyle().Colors[ImGuiCol_Text] = neonGreen; // Set text color

  ImGui::GetStyle().ScaleAllSizes(1.2f); // Scale all sizes
}

void 
UserInterface::actorsWindow(std::vector<EngineUtilities::TSharedPointer<Actor>>& actors, 
                            int& selectedIndex){
  ImGui::Begin("Actors");
  for (int i = 0; i < (int)actors.size(); ++i) {
    auto& actor = actors[i];
    if (!actor) continue;
    // "##i" assures that the label is unique
    std::string label = actor->getName() + "##" + std::to_string(i);
    bool isSelected = (selectedIndex == i);
    if (ImGui::Selectable(label.c_str(), isSelected)) {
      selectedIndex = i;
    }
  }
  ImGui::End();
}

void 
UserInterface::transformWindow(EngineUtilities::TSharedPointer<Actor>& actor){
  ImGui::Begin("Transform", nullptr, ImGuiWindowFlags_NoCollapse);
  if (actor) {
    auto tr = actor->getComponent<Transform>();
    vec3Control("Position", const_cast<float*>(tr->getPosition().data()));  // Get position
    vec3Control("Rotation", const_cast<float*>(tr->getRotation().data()));  // Get rotation
    vec3Control("Scale", const_cast<float*>(tr->getScale().data()));  // Get scale
  }
  ImGui::End();
}

void 
UserInterface::drawTestDock(){
  ImGui::Begin("Test Docking", nullptr, ImGuiWindowFlags_NoCollapse); 
  ImGui::Text("Don't forget to smile <:");
  ImGui::End();
}

void 
UserInterface::vec3Control(std::string label, 
                           float* values, 
                           float resetValue, 
                           float columnWidth){

  // Colores
  ImVec4 neonPurple = ImVec4(0.6f, 0.2f, 1.0f, 1.0f);  
  ImVec4 neonYellow = ImVec4(1.0f, 0.9f, 0.2f, 1.0f);  
  ImVec4 darkGrayPurple = ImVec4(0.15f, 0.10f, 0.25f, 1.0f); 

  ImGui::PushID(label.c_str());

  ImGui::Columns(2);
  ImGui::SetColumnWidth(0, columnWidth);
  ImGui::Text(label.c_str());
  ImGui::NextColumn();

  ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
  ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

  float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
  ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

  // X
  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.07f, 0.07f, 1.0f));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, neonPurple);
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, neonYellow);
  if (ImGui::Button("X", buttonSize)) values[0] = resetValue;
  ImGui::PopStyleColor(3);

  ImGui::SameLine();
  ImGui::PushStyleColor(ImGuiCol_FrameBg, darkGrayPurple);
  ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, neonPurple);
  ImGui::PushStyleColor(ImGuiCol_FrameBgActive, neonYellow);
  ImGui::DragFloat("##X", &values[0], 0.1f, -100.0f, 100.0f, "%.2f");
  ImGui::PopStyleColor(3);
  ImGui::PopItemWidth();
  ImGui::SameLine();

  // Y
  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 1.0f, 0.5f, 1.0f));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, neonPurple);
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, neonYellow);
  if (ImGui::Button("Y", buttonSize)) values[1] = resetValue;
  ImGui::PopStyleColor(3);

  ImGui::SameLine();
  ImGui::PushStyleColor(ImGuiCol_FrameBg, darkGrayPurple);
  ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, neonPurple);
  ImGui::PushStyleColor(ImGuiCol_FrameBgActive, neonYellow);
  ImGui::DragFloat("##Y", &values[1], 0.1f, -100.0f, 100.0f, "%.2f");
  ImGui::PopStyleColor(3);
  ImGui::PopItemWidth();
  ImGui::SameLine();

  // Z
  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.5f, 1.0f, 1.0f));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, neonPurple);
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, neonYellow);
  if (ImGui::Button("Z", buttonSize)) values[2] = resetValue;
  ImGui::PopStyleColor(3);

  ImGui::SameLine();
  ImGui::PushStyleColor(ImGuiCol_FrameBg, darkGrayPurple);
  ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, neonPurple);
  ImGui::PushStyleColor(ImGuiCol_FrameBgActive, neonYellow);
  ImGui::DragFloat("##Z", &values[2], 0.1f, -100.0f, 100.0f, "%.2f");
  ImGui::PopStyleColor(3);
  ImGui::PopItemWidth();

  ImGui::PopStyleVar();
  ImGui::Columns(1);
  ImGui::PopID();

}

