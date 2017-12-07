#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include "Red_portas.h"

using namespace std;
/**
*OPERADOR DE ENTRADA DOS PACOTES
*/
istream& operator>> (istream& in, Package& pack ){
	int ihl, dscp, total_leng;
int porta1;
stringstream buffer;
string linha;
string aux;
// VERIFICA SER O ARQUIVO TA FUNCIONANDO
if (!in){
	cout << "Arquivo não Abriu!" << '\n';
	return in;
}

//COMEÇAR A IHL

in.ignore();
getline(in, linha,' ');
buffer<<linha;
buffer.setf(ios::hex, ios::basefield);
buffer >> ihl ;
pack.ihl = ihl;
buffer.clear();
//dscp
getline(in, linha,' ');
buffer<<linha;
buffer.setf(ios::hex, ios::basefield);// manipulação pra converter e fazer a escovação dos bit
buffer >>dscp;
pack.dscp = dscp>>2;
buffer.clear();
// >>total_leng; // null e só pra pular 8 bytes coloca cada token na sua variavel
for(int cont=0;cont<=1;cont++){
	getline(in,linha,' ');
	aux+=linha;
}
buffer<<aux;
buffer.setf(ios::hex, ios::basefield);
buffer>>total_leng;
pack.total_length = total_leng; //
aux.erase();
// PULAR 1 LINHA PARA IR DIRETO PARA A LINHA DO IP
in.ignore(35);
//getline(in, linha);
//LER IP
int ip_var;
vector<int> ip;
for (int i = 0; i < 4; i++) {
	getline(in, linha, ' ');
	stringstream buffer2(linha);
	buffer2.setf(ios::hex, ios::basefield);//manipula
	buffer2>>ip_var;
	ip.push_back(ip_var);
}
pack.ip = to_string(ip[0]) + "." + to_string(ip[1]) + "." + to_string(ip[2]) + "." + to_string(ip[3]);
//PEGANDO PORTA
// to tentando desenvolver ainda//
in.ignore();
if (pack.ihl > 5) {
	for (unsigned i = 5; i < pack.ihl; i++)
		in.ignore(12);
}
buffer.clear();
in.ignore(5);
getline(in,linha,' ');
aux+=linha;
getline(in,linha,' ');
aux+=linha;
buffer<<aux;
buffer.setf(ios::hex, ios::basefield);
buffer>>porta1;
aux.erase();

pack.port =porta1;

//PEGANDO DATA
in.ignore(12);//DEFININDO POSIÇÃO DO DATA
int tam_data = (pack.total_length) - (pack.ihl * 4);//tamanho data
int tam_linhas = tam_data/8;//tamanho linha
int data;

buffer.clear();
while (tam_linhas >= 0){
	getline(in, linha);//pega as linhas onde o data estar
	buffer<<linha;
	while(buffer >> data){
		pack.data+=(char)data; // pack.data é uma string que recebe data que é um hex que foi convertido/
	}
	buffer.clear();
	tam_linhas--;
}
return in;
}
/**
* SOBRECARGA OPERADORES SAIDA
*/
ostream & operator<< (ostream & out, const Package & pack) {
	out << "ihl: " << pack.ihl;
	out << ", dscp: " << pack.dscp;
	out << ", total_length: " << pack.total_length << endl;
	out << "ip: " << pack.ip;
	out << ", port: " << pack.port << endl;
	out << "data: " << pack.data << endl;
	return out;
}




/**
*SOBRECARGA OPERADOR DE SAIDA DA CLASSE APLICATION
*/
ostream& operator<<(ostream &Saida, Aplication &A){
	cout << A.cod_processo << " ";
	cout << A.porta << " ";
	cout << A.end_ip << "\n";
	//cout<< A.fila.top();
	//cout<<A.fila.size()<<endl;
	//cout<< A.fila.top();
	// if(!A.fila.empty()){
	// 	while(!A.fila.empty()) {
	// 		cout << A.fila.top();
	// 		A.fila.pop();
	// 	}
	// }
    return Saida;
}

/**
* SOBRECARCA OPERADOR DE SAIDA DA CLASSE DADOS
*/

ostream & operator<<(ostream& ous,  Dados const &compare ){

		cout<<"["<<compare.priority<<"]";
				cout<< compare.data<<endl;

		return ous;
	}

	/**
	* CONSTRUTOR DO PORTFORWARD
	*/
PortForwarding::PortForwarding(istream& in,std::vector<Package> pacotes ){
	string line;

	if(in.good()){
 		while(!in.eof()){
 			getline(in,line, ',');
 			stringstream(line) >>  aplic.cod_processo;
			cout<<aplic.cod_processo<<' ';
 			getline(in,line, ',');
 			stringstream(line) >>  aplic.porta;
			cout<<aplic.porta<<' ';
 			getline(in,line);
 			stringstream(line) >>  aplic.end_ip;
			cout<<aplic.end_ip<<endl;
			for (size_t i = 0; i < 5; i++) {
				if(pacotes[i].getPort() == aplic.porta){
					if(pacotes[i].getIP()==aplic.end_ip){
						Dados tmp(pacotes[i].dscp,pacotes[i].data);
						aplic.fila.push(tmp);
						// while(aplic.fila.empty()){
						// 	cout<<aplic.fila.top();
						// 	aplic.fila.pop();
						// }
						cout<<aplic.fila.top();
						//cout<<aplic.fila.size()<<endl;
					}
				}

			}

 			tab_associacoes.push_back(aplic);

    	}

 	}else cout << "Falha na leitura do arquivo!" << endl;
}
/**
* CONSULTAR APLICAÇÃO
*/
int PortForwarding::consultar_alpicacao(int c_process){
	for(unsigned int i = 0; i < tab_associacoes.size(); i++){
		if(tab_associacoes[i].cod_processo == c_process){
			return tab_associacoes[i].porta;
		}else return 0;
	}
	return 0;
}
/**
* CONSULTAR PORTA
*/
int PortForwarding::consultar_porta(int c_door){
	for(unsigned int i = 0; i < tab_associacoes.size(); i++){
		if(tab_associacoes[i].porta == c_door){
			return tab_associacoes[i].cod_processo;
		}else return 0;
	}
	return 0;
}
/**
* REGISTRAR APLICACAO NOVA
*/
void PortForwarding::registrar_aplicacao(string interface_ip, int c_process, int c_door){
	while(consultar_porta(c_door) != 0){
		c_door++;
	}
	aplic.cod_processo = c_process;
	aplic.porta = c_door;
	aplic.end_ip = interface_ip;
	tab_associacoes.push_back(aplic);
	cout << "A aplicação " << c_process << " foi registrada com sucesso à porta: " << c_door << endl;
}
/**
* REMOVER APLICACAO
*/
void PortForwarding::remover_aplicacao(int c_process){
	for(unsigned int i = 0; i < tab_associacoes.size(); i++){
		if(tab_associacoes[i].cod_processo == c_process){
			tab_associacoes[i].cod_processo = 0;
			cout<< "Removida aplicação da porta:"<<tab_associacoes[i].porta<<endl;
		}
	}
}
/**
*REMOVER PORTA
*/
void PortForwarding::remover_porta(int c_door){
	for(unsigned int i = 0; i < tab_associacoes.size(); i++){
		if(tab_associacoes[i].porta == c_door){
			tab_associacoes[i].porta = 0;
			cout<< "Removida porta da aplicação:"<<tab_associacoes[i].cod_processo<<endl;
		}
	}
}
/**
*ALTERAR PORTA
*/
void PortForwarding::alterar_porta(int c_process, int c_door){
	if(consultar_porta(c_door) == 0){
		//unsigned int i = 0;
		for(unsigned int i = 0; i < tab_associacoes.size(); i++){
			if(tab_associacoes[i].cod_processo == c_process){
				if(tab_associacoes[i].fila.empty())tab_associacoes[i].porta = c_door;
				cout<<"aplicação alterada"<<endl;
		}
	}
	}else cout << "A porta não pôde ser alterada pois a nova já esta em uso!" << endl;
}
/**
* IMPRIMIR FILA - DIFICULDADES EM MOSTRAR A AS FILAS QUE EXISTEM por aqui
*/
void PortForwarding::imprimir_fila(){
	cout << "Conteudo da fila: " << endl;
	for(unsigned int i = 0; i < tab_associacoes.size(); i++){
		cout<<tab_associacoes[i];

	}
}
