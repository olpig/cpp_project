#ifndef CLASSES_HPP
#define CLASSES_HPP

#include <iostream>
#include <cmath>
#include <vector>

namespace project
{
	class bevolatility
	{
	public:
		bevolatility(std::size_t size);
		double get_bevolatility(std::size_t index) const; //read method
		void set_bevolatility(std::size_t index, double bevol); 
		~bevolatility();

	private:
		std::vector<double> m_bevol;
	};


	class rate
	{
	public:
		explicit rate(std::vector<double> rate);
		explicit rate(double rate);
		double get_rate(std::size_t index) const;
		std::vector<double> read_rate() const;
		double rate::get_rate() const;
		~rate();
	protected:

	private:
		std::vector<double> m_v_rate;
		double m_rate;
	};
	
	double BSPricer(double spot, double time_to_mat, double strike, double rt ,double vol);
	
	double Delta(double spot, double time_to_mat, double strike, double rt ,double vol);	
	double gamma(double spot, double time_to_mat, double strike, double rt, double vol);
	double normal_cdf(double x);
	double normal_pdf(double x);
}
#endif