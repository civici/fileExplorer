#include "SearchEngine.h"

void SearchEngine::changeDir(int dirIndex)
{
    this->currentPath.erase(this->currentPath.length() - 1);
    this->currentPath.append(this->fileList.at(dirIndex).fileData.cFileName);
    this->currentPath.append("\\*");
}

void SearchEngine::upperDir()
{
    this->currentPath.erase(this->currentPath.length() - 2, 2);
    std::string::size_type pos = this->currentPath.find_last_of("\\");
    this->currentPath = this->currentPath.substr(0, pos + 1) + "*";
}

void SearchEngine::showFiles(HWND list)
{
    SendMessage(list, LB_RESETCONTENT, 0, 0);
    this->fileList.clear();
    File currentFile;
    
}