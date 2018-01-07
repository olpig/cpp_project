// TO COMPILE:
//
// WINDOWS USERS
// mkdir build
// cd build
// cmake -G "NMake Makefiles" ..
// nmake
#include <iostream>
#include <cmath>
#include "classes.hpp"

namespace project
{
	//pi n'est pas explicitement défini sur C++
	double pi = 3.14159265358979323846264338328;

	bevolatility::bevolatility(const std::size_t size)
		:m_bevol(size)
	{
	}

	double bevolatility::get_bevolatility(std::size_t index) const
	{
		return m_bevol[index];
	}
	void bevolatility::set_bevolatility(std::size_t index, double bevol)
	{
		m_bevol[index] = bevol;
	}
	bevolatility::~bevolatility()
	{
	}
	rate::rate(std::vector<double> rate)
		: m_v_rate(rate)
	{
	}

	rate::rate(double rate)
		: m_rate(rate)
	{
	}
	double rate::get_rate(std::size_t index) const
	{
		return m_v_rate[index];
	}
	double rate::get_rate() const
	{
		return m_rate;
	}
	rate::~rate()
	{
	}

	/*
	// Dans son exemple sur le polymorphism le prof utilise un constructeur pour implied vol
	flat_rate::flat_rate(double rate)
		:m_rate(rate)
	{
	}
	flat_rate::get_rate()
	{
		return m_rate;
	}
	flat_rate::~flat_rate()
	{
	}
	*/
	double normal_cdf(double x)
	{
		//we define the normal cdf using the error function (calculations are straightforward)
		return 0.5*(1 + erf(x*std::sqrt(0.5)));
	}

	double BSPricer(double spot, double time_to_mat, double strike, double rt, double vol)
	{
		double d1 = (std::log(spot / strike) + (rt + vol*vol / 2)*time_to_mat) / (vol*std::sqrt(time_to_mat));
		double d2 = d1 - vol*std::sqrt(time_to_mat);
		//std::cout << "spot = " << spot << ", time_to_mat = " << time_to_mat << ", strike = " << strike << ", rate = " << rt << ", vol = " << vol << ", d1 = " << d1 << ", d2 = " << d2 << std::endl;
		double price = spot*normal_cdf(d1) - strike*std::exp(-rt*time_to_mat)*normal_cdf(d2);
		//std::cout << "N(d1) = " << normal_cdf(d1) << ", N(d2) = " << normal_cdf(d2) << std::endl;
		return price;
	}

	double Delta(double spot, double time_to_mat, double strike, double rt ,double vol)
	{
		double d1 = (std::log(spot / strike) + (rt + vol*vol / 2)*time_to_mat) / (vol*std::sqrt(time_to_mat));
		//std::cout << "d1 = " << d1 << ", T = " << time_to_mat << std::endl;
		return normal_cdf(d1);
	}

}