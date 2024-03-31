#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

class FileManager {
public:
    void createFolder(const std::string& folderName) {
        std::string path = "/home/hania/Desktop/groups/" + folderName;
        if (fs::exists(path)) {
            fs::remove_all(path);
        }
        fs::create_directories(path);
        std::cout << "Carpeta creada exitosamente en: " << path << std::endl;
    }

    void writeFile(const std::string& subfolderName, const std::string& fileName, const std::string& content) {
        std::string folderPath = "/home/hania/Desktop/groups/" + subfolderName;
        std::string filePath = folderPath + "/" + fileName;
        if (fs::exists(folderPath)) {
            std::ofstream file(filePath);
            if (file.is_open()) {
                file << content;
                file.close();
                std::cout << "Archivo creado exitosamente en: " << filePath << std::endl;
            } else {
                std::cerr << "No se pudo abrir el archivo: " << filePath << std::endl;
            }
        }
    }
};