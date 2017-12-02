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
	int dscp;
	int total_length;
	std::string ip;
	int port;
	std::string data;
public:
	//friend istream& operator>> (std::istream& in, Package& pack);
	friend std::istream& operator>> (std::istream& in, Package& pack);
	friend std::ostream& operator<< (std::ostream &, const Package &);
};




#endif /*__PORTFOWARDING_H__*/
