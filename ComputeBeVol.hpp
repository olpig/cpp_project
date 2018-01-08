#ifndef COMPUTEBEVOL_HPP
#define COMPUTEBEVOL_HPP

#include <iostream>
#include <cmath>
#include <vector>
#include <iostream>
#include <cmath>
#include "underlying.hpp"
#include "classes.hpp"

namespace project
{
	class beVolatilityComputation
	{
	public:
		//initialize with nothing since the strike will be set latter on and all other members are actually from another class
		beVolatilityComputation();
		//read method
		double get_strike() const;
		//write method
		void update_strike(const double strike, underlying undl);

		//other methods		
		double PnlComputation(underlying& undl, double rt, double strike, double vol, std::vector<double> time_to_mat, std::size_t start);
		double PnlComputation(underlying& undl, std::vector<double> rt, double strike, double vol, std::vector<double> time_to_mat, std::size_t start);// avec une courbe des taux		
		double beVolatilityComputation::PnlComputation(underlying& undl, double rt, double strike, double vol, std::vector<double> time_to_mat, std::size_t start, bool robust);
		double midpoint_algo(underlying& undl, double rt, double strike, std::vector<double> time_to_mat, double min_vol, double max_vol, double tol, std::size_t max_iter, bool robust);
		double midpoint_algo(underlying& undl, std::vector<double> rt, double strike, std::vector<double> time_to_mat, double min_vol, double max_vol, double tol, std::size_t max_iter);
		~beVolatilityComputation();

	private:
		double m_strike;
	};
}
#endif