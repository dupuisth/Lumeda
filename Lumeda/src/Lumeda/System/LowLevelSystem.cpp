#include <filesystem>
#include <fstream>
#include <sstream>
#include <Lumeda/System/LowLevelSystem.h>

using namespace Lumeda;

tString iLowLevelSystem::ReadFileAsString(const twString& path)
{
  std::ifstream file{std::filesystem::path(path)};

  if (!file.is_open())
  {
    LUMEDA_CORE_ERROR("Could not open file: {}", std::filesystem::path(path).string());
    return "";
  }

  std::stringstream stringstream;
  stringstream << file.rdbuf();
  return stringstream.str();
}