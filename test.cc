#include <iostream>
#include <YargsCpp/Yargs.h>


int main(int argc, char* argv[]) { 
  argc::Yargs arguments(argc, argv);
  std::cout << "ships: " << arguments("ships", int()) << std::endl;
  std::cout << "distance: " << arguments("distance", double()) << std::endl;
}

