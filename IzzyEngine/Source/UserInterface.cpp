#include "UserInterface.h"

UserInterface::UserInterface() {
}

UserInterface::~UserInterface() {
}

void 
UserInterface::init(void* window, 
                    ID3D11Device* device, 
                    ID3D11DeviceContext* deviceContext){
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  ImGui::StyleColorsClassic();

  setupStyle();

  ImGuiStyle& style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  ImGui_ImplWin32_Init(window);
  ImGui_ImplDX11_Init(device, deviceContext);
}

void 
UserInterface::update(){
  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();
  ImGui::NewFrame();
}

void 
UserInterface::render(){
  ImGui::Render();
  ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
  ImGuiIO& io = ImGui::GetIO();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
  }
}

void 
UserInterface::destroy(){
  ImGui_ImplDX11_Shutdown();
  ImGui_ImplWin32_Shutdown();
  ImGui::DestroyContext();
}

void 
UserInterface::setupStyle(){

  ImGui::StyleColorsClassic();
  ImGuiStyle& style = ImGui::GetStyle();
  style.WindowRounding = 5.3f;
  style.FrameRounding = 4.0f;
  style.ScrollbarRounding = 5.0f;
  style.GrabRounding = 3.0f;
  style.TabRounding = 3.0f;
  style.WindowPadding = ImVec2(10, 10);
  style.FramePadding = ImVec2(5, 5);
  style.ItemSpacing = ImVec2(8, 8);
  style.ItemInnerSpacing = ImVec2(5, 5);

  ImVec4 neonPink = ImVec4(1.0f, 0.07f, 0.58f, 1.0f);
  ImVec4 neonBlue = ImVec4(0.0f, 0.5f, 1.0f, 1.0f);
  ImVec4 neonGreen = ImVec4(0.0f, 1.0f, 0.5f, 1.0f);
  ImVec4 backgroundColor = ImVec4(0.05f, 0.05f, 0.1f, 1.0f);
  ImVec4 activeGlow = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);

  ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = backgroundColor;
  ImGui::GetStyle().Colors[ImGuiCol_TitleBgActive] = neonPink;
  ImGui::GetStyle().Colors[ImGuiCol_TitleBg] = backgroundColor;
  ImGui::GetStyle().Colors[ImGuiCol_Border] = neonPink;
  ImGui::GetStyle().Colors[ImGuiCol_FrameBg] = ImVec4(0.2f, 0.2f, 0.24f, 1.0f);
  ImGui::GetStyle().Colors[ImGuiCol_FrameBgHovered] = neonBlue;
  ImGui::GetStyle().Colors[ImGuiCol_FrameBgActive] = neonGreen;
  ImGui::GetStyle().Colors[ImGuiCol_Button] = neonPink;
  ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = neonBlue;
  ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] = activeGlow;
  ImGui::GetStyle().Colors[ImGuiCol_Header] = neonGreen;
  ImGui::GetStyle().Colors[ImGuiCol_HeaderHovered] = neonBlue;
  ImGui::GetStyle().Colors[ImGuiCol_HeaderActive] = neonPink;

  ImGui::GetStyle().Colors[ImGuiCol_Text] = neonGreen;

  ImGui::GetStyle().ScaleAllSizes(1.2f);
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

