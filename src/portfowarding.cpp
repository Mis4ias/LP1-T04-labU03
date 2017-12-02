#include "portfowarding.h"
using namespace std;

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


ostream & operator<< (ostream & out, const Package & pack) {
	out << "ihl: " << pack.ihl;
	out << ", dscp: " << pack.dscp;
	out << ", total_length: " << pack.total_length << endl;

	out << "ip: " << pack.ip;
	out << ", port: " << pack.port << endl;

	out << "data: " << pack.data << endl;
	return out;
}
