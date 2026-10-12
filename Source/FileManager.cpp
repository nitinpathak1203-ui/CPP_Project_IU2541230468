#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace {
std::string trim(const std::string& s) {
    size_t start = 0;
    while (start < s.size() && (s[start] == ' ' || s[start] == '\t' || s[start] == '\r' || s[start] == '\n')) {
        start++;
    }
    size_t end = s.size();
    while (end > start && (s[end - 1] == ' ' || s[end - 1] == '\t' || s[end - 1] == '\r' || s[end - 1] == '\n')) {
        end--;
    }
    return s.substr(start, end - start);
}
}

std::vector<std::vector<std::string>> FileManager::readRows(const std::string& path, char delimiter) {
    std::ifstream in(path);
    std::vector<std::vector<std::string>> all;
    if (!in.is_open()) {
        return all;
    }

    std::string line;
    while (std::getline(in, line)) {
        line = trim(line);
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string part;
        std::vector<std::string> row;
        while (std::getline(ss, part, delimiter)) {
            row.push_back(trim(part));
        }
        if (!row.empty()) {
            all.push_back(row);
        }
    }
    return all;
}

void FileManager::writeRows(const std::string& path, const std::vector<std::string>& rows) {
    std::ofstream out(path);
    if (!out.is_open()) {
        throw std::runtime_error("Could not write file: " + path);
    }
    for (const auto& r : rows) {
        out << r << "\n";
    }
}
