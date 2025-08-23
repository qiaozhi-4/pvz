/**
 * @author XGeorge
 * @date 2025/8/22 20:54:36
*/
#ifndef PVZ_CONFIG_H
#define PVZ_CONFIG_H

#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>

using json = nlohmann::json;

class Config
{
public:
    inline static bool showMenuBar = false;          // 显示窗口菜单栏
    inline static bool showMainMenuBar = false;          // 显示窗口菜单栏

    // 初始化配置文件路径
    static void init(const std::string &filename);

    // 获取配置值
    template<typename T>
    static T get(const std::string &key);

    // 设置配置值
    template<typename T>
    static void set(const std::string &key, const T &value);

    // 保存配置到文件
    static bool save();

private:
    inline static std::string filename_; // 配置文件路径
    inline static json config_;          // JSON配置数据

    // 加载配置文件
    static void load();

    // 创建默认配置文件
    static void createDefaultConfig();
};


#endif //PVZ_CONFIG_H
