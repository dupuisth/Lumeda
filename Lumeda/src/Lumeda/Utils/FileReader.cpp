#include <Lumeda/Utils/FileReader.h>

#include <fstream>
#include <sstream>

using namespace Lumeda;

std::string FileReader::ReadFile(const std::string& path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        LUMEDA_CORE_ERROR("Could not open file: {0}", path);
        throw std::runtime_error("Could not open file: " + path);
    }

    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}