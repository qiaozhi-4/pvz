/**
 * @author XGeorge
 * @date 2025/8/22 20:54:36
*/
#include "Config.h"
#include <fstream>

void Config::init(const std::string &filename)
{
    filename_ = filename;
    std::ifstream file(filename_);
    if (!file.is_open())
    {
        createDefaultConfig();
        save();
    }
    load();
}

void Config::load()
{
    std::ifstream file(filename_);
    if (!file.is_open())
    {
        throw std::runtime_error("无法打开配置文件: " + filename_);
    }

    try
    {
        file >> config_;
        // 更新静态成员变量
        if (config_.contains("showMenuBar")) {
            showMenuBar = config_["showMenuBar"].get<bool>();
        }
        if (config_.contains("showMainMenuBar")) {
            showMainMenuBar = config_["showMainMenuBar"].get<bool>();
        }
    } catch (const json::exception &e)
    {
        file.close();
        throw std::runtime_error("解析JSON配置文件失败: " + std::string(e.what()));
    }

    file.close();
}

void Config::createDefaultConfig()
{
    // 设置默认配置，包含静态成员的默认值
    config_["showMenuBar"] = showMenuBar;
    config_["showMainMenuBar"] = showMainMenuBar;
}

bool Config::save()
{
    std::ofstream file(filename_);
    if (!file.is_open())
    {
        return false;
    }

    // 更新JSON对象中的值
    config_["showMenuBar"] = showMenuBar;
    config_["showMainMenuBar"] = showMainMenuBar;

    // 格式化输出JSON
    try
    {
        file << std::setw(4) << config_ << std::endl;
    } catch (const json::exception &e)
    {
        file.close();
        return false;
    }

    file.close();
    return true;
}

template<typename T>
T Config::get(const std::string &key)
{
    if (!config_.contains(key))
    {
        throw std::runtime_error("未找到配置键: " + key);
    }

    try
    {
        return config_[key].get<T>();
    } catch (const json::exception &e)
    {
        throw std::runtime_error("无法转换键值: " + key + "，错误: " + e.what());
    }
}

template<typename T>
void Config::set(const std::string &key, const T &value)
{
    config_[key] = value;
}

// 显式模板实例化
//template int Config::get<int>(const std::string &key) ;
//
//template std::string Config::get<std::string>(const std::string &key) ;
//
//template bool Config::get<bool>(const std::string &key) ;
//
//template double Config::get<double>(const std::string &key) ;
//
//template void Config::set<int>(const std::string &key, const int &value);
//
//template void Config::set<std::string>(const std::string &key, const std::string &value);
//
//template void Config::set<bool>(const std::string &key, const bool &value);
//
//template void Config::set<double>(const std::string &key, const double &value);
