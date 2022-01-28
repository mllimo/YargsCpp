#include <iostream>
#include <YargsCpp/Yargs.h>

std::ostream& operator<<(std::ostream& os,
                         const std::vector<std::string>& vector) {
  for (auto& s : vector) {
    os << s << " ";
  }
  return os;
}

int main(int argc, char* argv[]) { 
  argc::Yargs arguments(argc, argv);
  arguments.Array("names").Parse();
  std::cout << "ships: " << arguments("ships", Int) << std::endl;
  std::cout << "distance: " << arguments("distance", Double) << std::endl;
  std::cout << "names: " << arguments("names", ArrayString) << std::endl;
}

