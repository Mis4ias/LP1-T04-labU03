#include <iostream>
#include "portfowarding.h"

int main(int argc, char** argv){
  std::ifstream input;
	input.open("./assets/config.in");

  Package pacote;
  input>>pacote;
  std::cout<<pacote;

}
