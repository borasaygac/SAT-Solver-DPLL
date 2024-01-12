#include <dirent.h>
#include <sys/stat.h>

#include <iostream>
#include <string>

bool isRegularFile(const std::string& path) {
    struct stat fileInfo;
    if (stat(path.c_str(), &fileInfo) != 0) {
        return false;
    }
    return S_ISREG(fileInfo.st_mode);
}

void processFile(std::string& filePath) {
    std::cout << filePath << "\n";
    std::string toRemove = "/test";
    std::string::size_type i = filePath.find(toRemove);

    filePath = filePath.erase(0, 5);
    filePath = filePath.substr(0, filePath.size()-4);

    std::cout << "Running DPLL on file " << filePath << "\n";

    system(("mingw32-make run arg=" + filePath).c_str());
    std::cout << "-------------------Ran--------------" << "\n";
}

void iterateFiles(const std::string& folderPath) {
    DIR* dir = opendir(folderPath.c_str());
    if (dir != nullptr) {
        dirent* entry;
        int count = 0;

        while ((entry = readdir(dir)) != nullptr && count != 2) {
            std::string filePath = folderPath + "/" + entry->d_name;
            if (isRegularFile(filePath)) {
                processFile(filePath);
            }
        }
        count++;
    }
}

int main() {
    const std::string folderPath = "test";
    iterateFiles(folderPath);

    return 0;
}