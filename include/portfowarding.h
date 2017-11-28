
#ifndef __PORTFOWARDING_H__
#define __PORTFOWARDING_H__
#include <iostream>
#include <sstream>
#include <ios>
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
};

/*
class PortFowarding{
 private:
	 std::vector<Port> Roteador;
	 queue < queue< Package > > ip_pacotes;
};*/



#endif /*__PORTFOWARDING_H__*/
