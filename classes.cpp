#include <iostream>
#include <cmath>

namespace project
{
	underlying::underlying(std::vector<double> UndlData)
		: m_UndlData(UndlData)
	{
	}
	underlying::get_underlying(std::size_t UndlPos)
	{
		return m_UndlData[UndlPos];
	}
	underlying::~underlying()
	{
		delete[] m_UndlData;
		m_UndlData= nullptr;
	}

	bevolatilities::bevolatilities(const std::size_t size)
	{
		m_bevols.resize(size); //Pas sur pour celle_ci
	}
	
	bevolatilities::get_bevolatilities(std::size_t index) const
	{
		return m_bevols[index];
	}
	bevolatilities::set_bevolatilities(std::size_t index, double bevol) const
	{
		m_bevols[index]=bevol;
	}
	bevolatilities::~bevolatilities()
	{
		delete[] m_bevols;
		m_bevols= nullptr;
	}
	rates::rates(std::vector<double> rates)
		: m_rates(rates)
	{
	}
	rates::get_rate(double maturity)
	{
		return m_rates[maturity]; //Je considère que la maturité est l'indexe, Il suffit juste de dire que 1st date=1 et voila
	}
	rates::~rates()
	{
		delete[] m_rates;
		m_rates= nullptr;
	}
	double BSPricer(double undl, int time_to_mat, double strike,double rt ,double vol,normal_distribution norm_dist);
	{
		double d1;
		double d2;
		d1=(std::log(undl/strike)+(rt-vol*vol/2)*std::sqrt(time_to_mat))/(vol*std::sqrt(time_to_mat));
		d2=d1-vol*std::sqrt(time_to_mat);
		return undl*norm_dist(d1)-strike*std::exp(-rt*time_to_maturity)*norm_dist(d2);
	}
	double Delta(underlying undl, int time_to_mat, double strike,rate rt ,double vol,std::normal_distribution ndist);
	{
		double pi; //pi n'est pas explicitement défini sur C++
		pi=3.14159265358979323846264338328;
		double d1;
		d1=(std::log(undl/strike)+(rt-vol*vol/2)*std::sqrt(time_to_mat))/(vol*std::sqrt(time_to_mat));
		return 1/(std::sqrt(2*time_to_mat))*std::exp(-0.5*d1*d1);
	}
}