/**
 * @author XGeorge
 * @date 2025/8/21 21:34:35
*/
#ifndef PVZ_MENU_H
#define PVZ_MENU_H

namespace Menu
{
    void RenderMain();

    // 子窗口
    void ChildWindow();

    // 菜单栏
    void MenuBar(bool *p_open = nullptr);

    // 主菜单栏
    void MainMenuBar(bool show = false);

    // 弹出菜单
    void Popup();

    // 模态弹窗
    void ModalPopup();

    // 工具提示
    void Tooltip();

    // 组合框
    void ComboBox();

    // 标签栏 (Tab Bar + Tab Item)
    void TabBar();

    // 表格 (Table)
    void Table();;

    // 树形节点 (TreeNode)
    void TreeNode();
} // Menu

#endif //PVZ_MENU_H
