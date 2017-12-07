#include "portfowarding.h"
using namespace std;
istream& operator>> (istream& in, Package& pack ){
	int ihl, dscp, total_leng;
	int porta1;
	stringstream buffer;
	string linha;
	string aux;
	char* buffer_dados= new char [2];
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
	for(int cont=0;cont<=1;cont++){
		getline(in,linha,' ');
		aux+=linha;
	}
	buffer<<aux;
	buffer.setf(ios::hex, ios::basefield);
	buffer>>total_leng;
	pack.total_length = total_leng; //
	aux.erase();
	
	in.ignore(35);
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
	int data;

	
	buffer.clear();
	while (tam_data > 0){
		in.read(buffer_dados,2);
		in.ignore();
		buffer<<buffer_dados;
		buffer>>data;
		pack.data+=(char)data;
		buffer.clear();
		tam_data--;
	}	
	return in;
}
void Package::read_cfg(string file_path) {
	string toquen;
	fstream in;
	in.open(file_path, fstream::in);	
		
			while (getline(in,toquen,',')){
				if(in.eof()){
					break;
				}else{
				this->aplication_cfg=stoi(toquen);
				getline(in,toquen,',');
				this->porta_cfg=stoi(toquen);
				getline(in,toquen);
				this->ip_cfg=toquen;
				}
			}
	
}

ostream & operator<< (ostream & out, const Package & pack) {
	out << "ihl: " << pack.ihl;
	out << ", dscp: " << pack.dscp;
	out << ", total_length: " << pack.total_length << endl;

	out << "ip: " << pack.ip;
	out << ", port: " << pack.port << endl;

	out << "data: " << pack.data << endl;
	out << "Aplicação_cfg: " << pack.aplication_cfg;
	out << ",port: " << pack.porta_cfg;
	out << ",ip: " << pack.ip_cfg << endl;

	return out;

}
