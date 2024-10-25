#include "mainconfig.h"
#include <QDebug>
MainConfig::MainConfig() : configFile("../../config/global.ini")
{
    INIReader reader(configFile);
    if (reader.ParseError() < 0)
    {
        qDebug() << "Can't load file" << configFile;
        return;
    };

    sound = reader.GetInteger("global_settings", "sound", 0);
    saveCount = reader.GetInteger("global_settings", "saveCount", 0);
    language = reader.Get("global_settings", "language", "en");

    data["global_settings"]["sound"] = std::to_string(sound);
    data["global_settings"]["saveCount"] = std::to_string(saveCount);
    data["global_settings"]["language"] = language;
}

void MainConfig::setSound(int s)
{
    sound = s;
    data["global_settings"]["sound"] = std::to_string(sound);
}

void MainConfig::incrementSaveCount()
{
    saveCount++;
    data["global_settings"]["saveCount"] = std::to_string(saveCount);
}

void MainConfig::setLanguage(std::string s)
{
    language = s;
    data["global_settings"]["language"] = language;
}

int MainConfig::getSound()
{
    return sound;
}


int MainConfig::getSaveCount()
{
    return saveCount;
}
std::string MainConfig::getLanguage()
{
    return language;
}

MainConfig::~MainConfig()
{
    std::ofstream file(configFile);
    if(!file.is_open())
    {
        qDebug() << "Unable to open file :" << configFile;
        return;
    };

    for (const auto &section : data)
    {
        file << "[" << section.first << "]\n";
        for (const auto &setting : section.second)
        {
            file << setting.first << "=" << setting.second << "\n";
        };
        file << "\n";
    };
    file.close();

}
