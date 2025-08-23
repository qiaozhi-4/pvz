/**
 * @author XGeorge
 * @date 2025/8/21 21:34:35
*/
#include "Menu.h"
#include "imgui.h"
#include "Logger.h"
#include "Config.h"

namespace Menu
{
    void init()
    {
        Config::init("cfg.json");
    }

    void RenderMain()
    {
        // 获取显示区域大小（整个屏幕/视口大小）
        ImVec2 displaySize = ImGui::GetIO().DisplaySize;
        // 计算 80% 的宽高
        ImVec2 windowSize(displaySize.x * 0.3f, displaySize.y * 0.5f);
        // 设置下一次窗口大小，只在第一次生效
        ImGui::SetNextWindowSize(windowSize, ImGuiCond_Once);

        if (ImGui::Begin("主菜单"))
        {
            if (ImGui::Button("打印窗口大小"))
            {
                LOG_DEBUG("%f,%f", displaySize.x, displaySize.y);
            }
            if (ImGui::Button("保存配置"))
            {
                Config::save();
            }

            ChildWindow();

            ImGui::Checkbox("带菜单栏的窗口", &Config::showMenuBar);
            MenuBar(&Config::showMenuBar);
            ImGui::Checkbox("顶部全局菜单栏", &Config::showMainMenuBar);
            MainMenuBar(Config::showMainMenuBar);
            Popup();
            ModalPopup();
            Tooltip();
            ComboBox();
            TabBar();
            Table();
            TreeNode();
        }
        ImGui::End();

    }

    void ChildWindow()
    {
        // 子窗口：高度 100px，带边框
        if (ImGui::BeginChild("ChildRegion", ImVec2(0, 100), ImGuiChildFlags_Borders))
        {
            ImGui::Text("这是子窗口里的内容!!");
            ImGui::Button("按钮1");
            ImGui::Button("按钮2");
        }
        ImGui::EndChild();
    }

    void MenuBar(bool *p_open)
    {
        if (!*p_open)return;
        // 窗口菜单栏
        if (ImGui::Begin("带菜单栏的窗口", p_open, ImGuiWindowFlags_MenuBar))
        {
            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("文件"))
                {
                    if (ImGui::MenuItem("打开"))
                    { LOG_DEBUG("激活: 文件-打开"); }
                    if (ImGui::MenuItem("保存"))
                    { LOG_DEBUG("激活: 文件-保存"); }
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("编辑"))
                {
                    if (ImGui::MenuItem("复制"))
                    { LOG_DEBUG("激活: 编辑-复制"); }
                    if (ImGui::MenuItem("粘贴"))
                    { LOG_DEBUG("激活: 编辑-粘贴"); }
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }
            ImGui::Text("窗口正文内容,*p_open: %d", *p_open);
        }
        ImGui::End();

    }

    void MainMenuBar(bool show)
    {
        if (!show)return;
        // 顶部全局菜单栏
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("文件"))
            {
                if (ImGui::MenuItem("退出"))
                {}
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

    }

    void Popup()
    {
        if (ImGui::Button("Popup 弹窗(右键点我)"))
            ImGui::OpenPopup("popup1");

        if (ImGui::BeginPopup("popup1"))
        {
            if (ImGui::MenuItem("选项A"))
            { LOG_DEBUG("激活: 选项A"); }
            if (ImGui::MenuItem("选项B"))
            { LOG_DEBUG("激活: 选项B"); }
            ImGui::EndPopup();
        }
    }

    void ModalPopup()
    {
        // 点击按钮打开模态对话框
        if (ImGui::Button("打开模态窗口"))
            ImGui::OpenPopup("模态窗口");

        if (ImGui::BeginPopupModal("模态窗口", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text("这是一个模态弹窗");
            if (ImGui::Button("关闭"))
                ImGui::CloseCurrentPopup();
            ImGui::EndPopup();
        }
    }

    void Tooltip()
    {
        // 鼠标悬停提示
        ImGui::Text("悬停这里");
        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::Text("这是提示信息");
            ImGui::EndTooltip();
        }

    }

    void ComboBox()
    {
        // 下拉选择框
        const char *items[] = {"苹果", "香蕉", "樱桃"};
        static int current = 0;

        if (ImGui::BeginCombo("水果选择", items[current])) // 打开下拉
        {
            for (int i = 0; i < IM_ARRAYSIZE(items); i++)
            {
                bool is_selected = (current == i);
                if (ImGui::Selectable(items[i], is_selected))
                    current = i;
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
    }

    void TabBar()
    {
        // 标签页
        if (ImGui::BeginTabBar("标签栏"))
        {
            if (ImGui::BeginTabItem("第一页"))
            {
                ImGui::Text("内容 A");
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("第二页"))
            {
                ImGui::Text("内容 B");
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }

    }

    void Table()
    {
        // 三列表格
        if (ImGui::BeginTable("示例表格", 3))
        {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("行1 列1");
            ImGui::TableSetColumnIndex(1);
            ImGui::Text("行1 列2");
            ImGui::TableSetColumnIndex(2);
            ImGui::Text("行1 列3");

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("行2 列1");
            ImGui::TableSetColumnIndex(1);
            ImGui::Text("行2 列2");
            ImGui::TableSetColumnIndex(2);
            ImGui::Text("行2 列3");

            ImGui::EndTable();
        }

    }

    void TreeNode()
    {
        // 树结构
        if (ImGui::TreeNode("节点1"))
        {
            ImGui::Text("子内容 A");
            if (ImGui::TreeNode("子节点 1.1"))
            {
                ImGui::Text("更深层的内容");
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }

    }
} // Menu