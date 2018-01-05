#include <iostream>
#include <cmath>
#include <vector>
#include "classes.hpp"
#include "underlying.hpp"
#include "ComputeBeVol.hpp"

//this is all for the parser
//this code comes from a blog post about boost tokenizer
#include <fstream>      // fstream
#include <string>
#include <algorithm>    // copy
#include <iterator>     // ostream_operator
//only if we use the boost tokenizer
//#include <boost/tokenizer.hpp>

// To compile
//
// Windows users:
// mkdir build
// cd build
// cmake -G "NMake Makefiles" ..
// nmake

//defining the >> operator as reading the next row of the csv file
std::istream& operator>>(std::istream& str, undl::CSVRow& data)
{
	data.readNextRow(str);
	return str;
}

//this function returns an object of type underlying
undl::underlying set_underlying()
{
	
	//set the name of the file to open (this could be done via command line)
	//requires the full path of the file
	std::string filepath;

	std::cout << "Please, enter your full file path: ";
	std::getline(std::cin, filepath);
	std::cout << "Treating file: " << filepath << std::endl;

	//std::ifstream file("C:/Users/pigeo/Desktop/master/S3/C++/project/Book2.csv");
	std::ifstream file(filepath);
	
	undl::CSVRow row;
	//set an empty vector for dates
	std::vector<double> v_date;
	//set an empty vector for stock prices
	std::vector<double> v_price;

	while (file >> row)
	{	
		//setting up vectors of doubles to store the dates and the underlying prices
		v_date.push_back(std::stod(row[0]));
		v_price.push_back(std::stod(row[1]));
	}
	
	//set an underlying object
	undl::underlying UL1(v_price, v_date);
	return UL1;
}

int main(int argc, char* argv[])
{
	//we first setup the data in an underlying object
	set_underlying();
	



	return 0;
}

