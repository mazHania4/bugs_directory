#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

class FileManager {
public:
    void createFolder(const std::string& folderName) {
        std::string path = "/home/hania/Desktop/directory/" + folderName;
        if (fs::exists(path)) {
            fs::remove_all(path);
        }
        fs::create_directories(path);
        std::cout << "Carpeta creada exitosamente en: " << path << std::endl;
    }

    void writeFile(const std::string& subfolderName, const std::string& fileName, const std::string& content) {
        std::string folderPath = "/home/hania/Desktop/directory/" + subfolderName;
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

    void generateGraph(std::string dotContent){
        std::ofstream file("/home/hania/Desktop/directory/graphs/graph.dot");
        if (!file.is_open()) {
            std::cerr << "Error al abrir el archivo." << std::endl;
        }
        file << dotContent << std::endl;
        file.close();
        system("dot -Tpng /home/hania/Desktop/directory/graphs/graph.dot -o /home/hania/Desktop/directory/graphs/graph.png");
        std::cout << "\nGráfico generado correctamente en /home/hania/Desktop/directory/graphs/graph.dot" << std::endl;
    }
};