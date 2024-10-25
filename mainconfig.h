#ifndef MAINCONFIG_H
#define MAINCONFIG_H

#include <fstream>
#include <string>
#include <unordered_map>
#include "INIReader.h"

inline std::string ENGLISH = "en";
inline std::string FRENCH = "fr";

class MainConfig
{
    public:
        MainConfig();
        ~MainConfig();
        void setSound(int);
        void incrementSaveCount();
        void setLanguage(std::string);
        int getSound();
        int getSaveCount();
        std::string getLanguage();
    private:
        int sound;
        std::string language;
        int saveCount;
        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> data;
        std::string configFile;
};

#endif // MAINCONFIG_H
