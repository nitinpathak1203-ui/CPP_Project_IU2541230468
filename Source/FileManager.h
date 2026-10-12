#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>

class FileManager {
public:
    // Reads rows from delimited text file
    static std::vector<std::vector<std::string>> readRows(const std::string& path, char delimiter = '|');

    // Writes lines to file, creates file or overwrites
    static void writeRows(const std::string& path, const std::vector<std::string>& rows);
};

#endif // FILEMANAGER_H
