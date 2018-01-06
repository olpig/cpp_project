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
	double k = 50.0;
	double increment_k = 5.0;
	double max_k = 150.0;
	std::vector<double> v_beVol;
	double beVol = 0.0;
	std::size_t count = 0;
	while (k < max_k + 1)
	{
		k += increment_k;
		tmp.update_strike(k);
		beVol = tmp.midpoint_algo(0.001, 100, 0.0001, 10000);
		v_beVol.push_back(beVol);
		std::cout << v_beVol[count] << std::endl;
		count += 1;
	}

	return 0;
}

