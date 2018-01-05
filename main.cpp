#include <iostream>
#include <cmath>
#include <vector>
#include "classes.hpp"
#include "underlying.hpp"

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

void test_parser()
{
	//std::string FileName = "C:/Users/pigeo/Desktop/master/S3/C++/Book1.csv";
	//getNextLineAndSplitIntoTokens(FileName);
	
	//set the name of the file to open (this could be done via command line)
	//requires the full path of the file
	std::ifstream file("C:/Users/pigeo/Desktop/master/S3/C++/project/Book2.csv");
	std::cout << file.is_open() << std::endl;
	
	undl::CSVRow row;
	while (file >> row)
	{	

		//printing the stock price and date
		std::cout << "Date: " << std::stod(row[0]) << " Stock price(" << std::stod(row[1]) << ")\n";
	}
	
	
}

int main(int argc, char* argv[])
{
	//code here
	test_parser();
	return 0;
}

