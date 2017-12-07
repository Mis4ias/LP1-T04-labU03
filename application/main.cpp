#include <iostream>
#include "portfowarding.h"

int main(int argc, char** argv){
  std::ifstream input;
	input.open("./assets/config.in");



    Package pacote;
    input>>pacote;
    
    pacote.read_cfg("./data/config1.cfg");


    std::cout<<'\n' << "pacote"<< '\n';
    std::cout<<pacote;

}
