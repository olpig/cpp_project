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
		//the constructor handles the size of the vector
		//m_bevols.resize(size); //Pas sur pour celle_ci
	}

	double bevolatility::get_bevolatility(std::size_t index) const
	{
		return m_bevol[index];
	}
	void bevolatility::set_bevolatility(std::size_t index, double bevol)// const
	{
		m_bevol[index] = bevol;
	}
	bevolatility::~bevolatility()
	{
		/*This is not a pointer but rather a vector
		delete[] m_bevols;
		m_bevols= nullptr;
		*/
	}
	rate::rate(std::vector<double> rates)
		: m_rate(rates)
	{
	}
	double rate::get_rate(std::size_t maturity) const
	{
		return m_rate[maturity]; //Je considère que la maturité est l'indexe, Il suffit juste de dire que 1st date=1 et voila
	}
	double flat_rate::get_rate() const
	{
		return m_rate;
	}
	rate::~rate()
	{
		/*
		delete[] m_rates;
		m_rates= nullptr;
		*/
		//m_rates is a vector not a pointer
	}

	/*
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
		return 0.5*(1 + erf(x*std::sqrt(2)));
	}

	double normal_pdf(double x)
	{
		return std::exp(-x*x / 2) * 1 / std::sqrt(2 * pi);
	}
	double BSPricer(double spot, int time_to_mat, double strike, double rt, double vol)
	{
		double d1;
		double d2;
		d1 = (std::log(spot / strike) + (rt + vol*vol / 2)*time_to_mat) / (vol*std::sqrt(time_to_mat));
		d2 = d1 - vol*std::sqrt(time_to_mat);
		return spot*normal_cdf(d1) - strike*std::exp(-rt*time_to_mat)*normal_cdf(d2);
	}

	double Delta(double spot, int time_to_mat, double strike, double rt ,double vol)
	{
		double d1;
		d1=(std::log(spot/strike)+(rt+vol*vol/2)*time_to_mat)/(vol*std::sqrt(time_to_mat));
		//return 1/(std::sqrt(2*pi))*std::exp(-0.5*d1*d1);
		return normal_cdf(d1);
	}

}