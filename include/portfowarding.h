
#ifndef __PORTFOWARDING_H__
#define __PORTFOWARDING_H__
#include <iostream>
#include <sstream>
#include <ios>
<<<<<<< HEAD
#include <fstream>
#include <string>
//using namespace std;
class Package{
private:
	unsigned int ihl;
	int dscp;
	int total_length;
	std::string ip;
	int port;
	int data;
public:
	//friend istream& operator>> (std::istream& in, Package& pack);
	friend std::istream& operator>> (std::istream& in, Package& pack);
	friend std::ostream& operator<< (std::ostream &, const Package &);
=======
using namespace std;
class Package{
private:
	int ihl,port,data,dscp,total_lenght;
	float ip;
	
public:
	friend istream& operator>> (istream& in, Package& pack ){
		string field;
		string buffer;
		while(in>>buffer){
			stringstream input(buffer);
			while (getline(input, field, ' ')) {
				int cont=0;
				if(cont==0){
					int n;
					stringstream aux(field);
					aux >> hex >> n;
					pack.ihl = n%10;
				}else if (cont==1) {
					/* code */
				}else if (cont==2) {
					/* code */
				}else if (cont==3) {
					/* code */
				}else if (cont==4) {
					/* code */
				}
				cont++;
			}
		}
		return in;
	}

>>>>>>> e0b262d675ad1d13c81590ed8b408c8a2695d247
};

/*
class PortFowarding{
 private:
	 std::vector<Port> Roteador;
	 queue < queue< Package > > ip_pacotes;
};*/



#endif /*__PORTFOWARDING_H__*/
