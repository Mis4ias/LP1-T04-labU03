#include "portfowarding.h"

std::istream& operator>> (std::istream& in, Package& pack ){
	int ihl, dscp, null, total_length2;
	// VERIFICA SER O ARQUIVO TA FUNCIONANDO
	if (!in){
		std::cout << "Arquivo não Abriu!" << '\n';
		return in;
	}
	//COMEÇAR A LER
	std::string linha;
	std::getline(in, linha);
	std::stringstream buffer(linha);// le só a primeira linha para dentro do buffer
	buffer.setf(std::ios::hex, std::ios::basefield);// manipulação pra converter e fazer a escovação dos bits
	// PEGA O BUFFER E SEPARA OS TOKENS (DUPLA DE HEXA) PARA CADA VARIAVEL NA ORDEM

	buffer >> ihl >> dscp >> null >>total_length2; // null e só pra pular 8 bytes coloca cada token na sua variavel

	pack.ihl = ihl & 0x0f;
	pack.dscp = dscp >> 2;
	pack.total_length = total_length2; //

	// PULAR 1 LINHA PARA IR DIRETO PARA A LINHA DO IP
	std::getline(in, linha);


	//LER IP
	std::getline(in, linha);
	std::stringstream buffer2(linha);// le a linha para dentro do buffer
	buffer2.setf(std::ios::hex, std::ios::basefield);//manipula

	int ip1,ip2,ip3,ip4;
	buffer2>> ip1 >> ip2 >> ip3 >> ip4;

	pack.ip = std::to_string(ip1) + "." + std::to_string(ip2) + "." + std::to_string(ip3) + "." + std::to_string(ip4);



	//PEGANDO PORTA
	// to tentando desenvolver ainda//
	if (pack.ihl > 5) {
		for (unsigned i = 5; i < pack.ihl; i++) std::getline(in, linha);
		buffer.str(linha);
		buffer.clear();
		if (pack.ihl % 2) in.ignore(12);
	}

	buffer.ignore(6);
	int porta1, porta2;
	buffer>> porta1 >> porta2;
	pack.port = (porta1<<8) + porta2;

	//PEGANDO DATA
	int tam_data = pack.total_length - pack.ihl * 4;
	int data;
	do{
		std::getline(in, linha); // pega a linha 5 onde começa os dados
		buffer.str(linha); 
		buffer >> data; 	// buffer é um stringstream que recebe a linha do arquivo e passa o token para data
		pack.data+=(char)data; // pack.data é uma string que recebe data que é um hex que foi convertido
		pack.data+="/";// só pra separar na saida (auxiliar)
		--tam_data;//tamanho data é o rage que ele tem que ler
	
	}while (tam_data>0);
		


	return in;
}


std::ostream & operator<< (std::ostream & out, const Package & pack) {
	out << "ihl: " << pack.ihl;
	out << ", dscp: " << pack.dscp;
	out << ", total_length: " << pack.total_length << std::endl;

	out << "ip: " << pack.ip;
	out << ", port: " << pack.port << std::endl;

	out << "data: " << pack.data << std::endl;
	return out;
}
