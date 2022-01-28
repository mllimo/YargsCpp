#include <iostream>
#include <YargsCpp/Yargs.h>


int main(int argc, char* argv[]) { 
  argc::Yargs arguments(argc, argv);
  arguments.Parse();
  std::cout << "ships: " << arguments("ships", Int) << std::endl;
  std::cout << "distance: " << arguments("distance", Double) << std::endl;
}

