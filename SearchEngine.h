#pragma once

#include <string>
#include <vector>
#include <minwinbase.h>
#include <windef.h>
#include <WinUser.h>

class File{
    public:
        WIN32_FIND_DATA fileData;
        int cType;
        File();
};

class SearchEngine{
    public:
        std::string currentPath;
        std::vector<File*> fileList;
        void changeDir(int dirIndex);
        void upperDir();
        void showFiles(HWND list);

};

extern SearchEngine MainEngine;