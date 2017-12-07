#ifndef Red_portas_h
#define Red_portas_h

#include <string>
#include <vector>
#include <queue>
using namespace std;

class Dados{
public:
  int priority;
  string data;
public:

	Dados(int dscp, string dados){
	priority= dscp;
	data=dados;
}

	  friend ostream & operator<<(ostream& ous,  Dados const & );
	bool operator<(const Dados & compare){
			return priority < compare.priority;
	}
};


struct CompareDscp{
	bool operator()(const Dados& dados1,Dados& dados2  ){
	return dados1.priority < dados2.priority;
	}
};

class Package{
public:
	unsigned int ihl;
	long int porta_cfg,aplication_cfg;
	std::string  ip_cfg;
	int dscp;
	int total_length;
	std::string ip;
	int port;
	std::string data;
public:
  int getPort(){return port;}
  string getIP(){return ip;}
  Dados getData(){
    Dados _dados(this->dscp,this->data);

    return _dados;
  }
	friend std::istream& operator>> (std::istream& in, Package& pack);
	friend std::ostream& operator<< (std::ostream &, const Package &);
};


class Aplication {
	public:
		int cod_processo;
		int porta;
		string end_ip;
		priority_queue<Dados, std::vector<Dados>, CompareDscp> fila;
  public:
		//inserir_dado(Dados data){

		//}
};

class PortForwarding {
	private:
		Aplication aplic;
		vector <Aplication> tab_associacoes;

	public:
/*	O construtor terá a função de inicializar a tabela de
associação apartir de um arquivo exeterno de configuração.
*/
		PortForwarding(istream & in, std::vector<Package> pacotes);//Usa o arquivo indicado.
		int consultar_alpicacao(int c_process);
		int consultar_porta(int c_door);
		void registrar_aplicacao(string interface_ip, int c_process, int c_door = 1000);
		void remover_aplicacao(int c_process);
		void remover_porta(int c_door);
		void alterar_porta(int c_process, int c_door);
		void imprimir_fila();
};

#endif
