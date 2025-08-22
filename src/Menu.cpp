/**
 * @author XGeorge
 * @date 2025/8/21 21:34:35
*/
#include "Menu.h"
#include "imgui.h"
#include "Logger.h"

namespace Menu {
    void RenderMain() {
        ImGui::Begin("主菜单");

        ImGui::Text("上方内容");

        // 子窗口：高度 100px，带边框
        if (ImGui::BeginChild("ChildRegion", ImVec2(0, 100), ImGuiChildFlags_Borders)) {
            ImGui::Text("这是子窗口里的内容");
            ImGui::Button("按钮1");
            ImGui::Button("按钮2");
        }
        ImGui::EndChild();

        ImGui::Text("下方内容");
        ImGui::End();
    }
} // Menu