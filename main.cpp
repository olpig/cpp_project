#include <iostream>
#include <cmath>
#include <vector>
#include "classes.hpp"
#include "underlying.hpp"
#include "ComputeBeVol.hpp"

// To compile
//
// Windows users:
// mkdir build
// cd build
// cmake -G "NMake Makefiles" ..
// nmake


int main(int argc, char* argv[])
{
	//we first setup the data in an underlying object
	//set_underlying();
	undl::parser file_stock;
	file_stock.readfile();
	undl::underlying UL(file_stock.get_data(), file_stock.get_dates());
	std::cout << "Date: " << UL.get_date(10) << " Stock Price: " << UL.get_underlying(10) << std::endl;
	std::cout << UL.get_size() << std::endl;
	project::beVolatilityComputation tmp(UL, 0.0, 100.0, 0.1);
	

	return 0;
}

