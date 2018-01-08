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

bool is_number(const std::string& s)
{
	try
	{
		std::stod(s);
	}
	catch (...)
	{
		return false;
	}
	return true;
}
double input(std::string param, std::string eg, std::string str_def, double def)
{
	std::string val;
	std::cout << "Please, enter a " << param << " to use (eg. for " << eg << "). Press enter for default value (" << str_def << "): ";
	std::getline(std::cin, val);
	std::cout << "You selected a " << param << " of: " << val << std::endl;
	if (val == "")
	{
		return def;
	}
	while (!is_number(val))
	{
		std::cout << "Invalid value of " << param << ". Please enter a valid " << param << ": ";
		std::getline(std::cin, val);
		std::cout << "You selected a " << param << " of: " << val << std::endl;
	}
	return std::stod(val);
}

double test_flat_rate()
{
	//let the user choose the rate (default set to 0)
	double tmp = input("rate", "5% enter 0.05", "0%", 0);
	project::rate rate(tmp);
	double rt = rate.get_rate();
	return rt;
}

std::vector<double> test_file_rates()
{
	project::parser file_rates;
	file_rates.readfile();
	project::rate rate(file_rates.get_v2());
	std::vector<double> rt = rate.read_rate();
	return rt;
}


int main(int argc, char* argv[])
{
	//we first setup the data in an underlying object
	project::parser file_stock;
	file_stock.readfile();
	project::underlying UL(file_stock.get_v2(), file_stock.get_v1());

	//initialize the parameters
	project::beVolatilityComputation compute;
	std::vector<double> v_beVol;
	double beVol = 0.0;
	std::size_t count = 0;
	std::vector<double> v_AllStrikes; //Je crée un vector avec tous les strikes pour le plotting
	
	//let the user set the strike parameters
	std::cout << "Initialization of parameters..." << std::endl;
	//set the minimum strike
	double k = input("minimum strike", "50% strike enter 50", "50%", 50);
	//set the max_k
	double max_k = input("maximum strike", "50% strike enter 50", "150%", 150);
	//set the number of steps
	double increment_k = (max_k - k) / input("number of estimations", "10 steps enter 10", "20", 20);;

	//let the user choose if he wants flat rate or not (y for flat rate). warn about the need for a file
	std::string str_flat_rate;
	std::cout << "Do you want to use a flat rate? Type y for yes.";
	std::getline(std::cin, str_flat_rate);

	if (str_flat_rate == "y")
	{
		std::cout << "You selected a flat rate" << std::endl;
		double rt = test_flat_rate();

		//choose robustness or not
		std::string str_robust;
		bool robust = false;
		std::cout << "Do you want to use the robustness method? Type y for yes.";
		std::getline(std::cin, str_robust);

		if (str_robust == "y" || str_robust == "Y")
		{
			std::cout << "You selected the robustness method" << std::endl;
			robust = true;
		}
		else
		{
			std::cout << "You selected the regular method" << std::endl;
		}
		while (k < max_k + 1)
		{
			compute.update_strike(k, UL);
			beVol = compute.midpoint_algo(UL, rt, compute.get_strike(), UL.read_TtoM(), 0.001, 1., 0.0001, 10000,robust);
			v_beVol.push_back(beVol);
			v_AllStrikes.push_back(k);
			std::cout << "Breakeven vol at strike: " << compute.get_strike() << " = " << v_beVol[count] << std::endl;
			count += 1;
			k += increment_k;

		}
	}
	else
	{
		std::cout << "You selected a rate curve" << std::endl;
		std::vector<double> rt = test_file_rates();
		while (k < max_k + 1)
		{
			compute.update_strike(k, UL);
			beVol = compute.midpoint_algo(UL, rt, compute.get_strike(), UL.read_TtoM(), 0.001, 1., 0.0001, 10000);
			v_beVol.push_back(beVol);
			v_AllStrikes.push_back(k);
			std::cout << "Breakeven vol at strike: " << compute.get_strike() << " = " << v_beVol[count] << std::endl;
			count += 1;
			k += increment_k;
		}
	}
		
	return 0;
}
