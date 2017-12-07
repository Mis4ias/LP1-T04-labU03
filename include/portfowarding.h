#ifndef __PORTFOWARDING_H__
#define __PORTFOWARDING_H__
#include <iostream>
#include <sstream>
#include <ios>
#include <fstream>
#include <string>
#include <vector>
//using namespace std;
class Package{
private:
	unsigned int ihl;
	long int porta_cfg,aplication_cfg;
	std::string  ip_cfg;
	int dscp;
	int total_length;
	std::string ip;
	int port;
	std::string data;

public:
	friend std::istream& operator>> (std::istream& in, Package& pack);
	friend std::ostream& operator<< (std::ostream &, const Package &);
	void read_cfg(std::string file_path);

};




#endif /*__PORTFOWARDING_H__*/
