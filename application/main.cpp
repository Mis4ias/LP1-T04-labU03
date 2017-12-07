#include <iostream>
#include <fstream>
#include "Red_portas.h"
using namespace std;

int main(int argc, char const *argv[]){
  ifstream input;
	input.open("./assets/config1.in");
	std::vector<Package> pacotes;
	for (size_t i = 0; i < 6; i++) {
    Package pacote;
		input>>pacote;
    pacotes.push_back(pacote);

	}

  ifstream in;
  in.open("./assets/config1.cfg");
	PortForwarding tabela(in, pacotes);


  //tabela.imprimir_fila();
  cout<<"consulta por porta aplicação resultado :"<<tabela.consultar_porta(48091)<<endl;
  cout<<"consulta por aplicação porta resultado :"<<tabela.consultar_alpicacao(12524)<<endl;

  tabela.registrar_aplicacao("123.321.332", 2321, 6777);



  tabela.remover_aplicacao(9990);

  tabela.remover_porta(48091);

  tabela.alterar_porta(12524, 1111);

	return 0;
}
