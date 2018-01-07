// TO COMPILE:
//
// WINDOWS USERS
// mkdir build
// cd build
// cmake -G "NMake Makefiles" ..
// nmake
#include <iostream>
#include <cmath>
#include <algorithm>
#include "ComputeBeVol.hpp"

namespace project
{
	beVolatilityComputation::beVolatilityComputation()
	{
	}

	double beVolatilityComputation::PnlComputation(underlying& undl, double rt, double strike, double vol, std::vector<double> time_to_mat, std::size_t start)
	{
		double BSPrice0; //Call price at the beginning
		double BSPriceT; //Call price at the end
		double dlt;
		double UndlNew;
		//get the first value of underlying at time 0
		double UndlOld = undl.get_underlying(start);
		//std::cout << "intial strike: " << strike << std::endl;
		//std::cout << "intial undlold: " << UndlOld<< std::endl;
		BSPrice0=BSPricer(UndlOld, time_to_mat[start]/365, strike, rt, vol);
		//std::cout << "initial price of option is: " << BSPrice0 << std::endl;
		//change this to payoff (last value of the call is its payoff)
		BSPriceT = std::max(undl.get_underlying(0) - strike, 0.0);
		//std::cout << "Final payoff = " << BSPriceT << std::endl;
		//intitialize the PnL
		double PnL=BSPriceT-BSPrice0;
		//std::cout << "PnL from option = " << PnL << std::endl;
		//std::cout << "Time to maturity at 0: " << time_to_mat[start] / 365 << std::endl;
		double sum = 0;
		std::size_t count = 0;
		for(int i = (undl.get_size() - 2); i >= 0; i--)
        {
			UndlNew=undl.get_underlying(i);
			dlt=Delta(UndlOld, time_to_mat[i+1]/365, strike, rt, vol);//On Calcul delta en t-1
			PnL-=dlt*(UndlNew-UndlOld);
			sum -= dlt*(UndlNew - UndlOld);
			UndlOld=UndlNew;
			count += 1;
			//std::cout << "New value of Underlying: " << UndlNew << ", Delta = " << dlt << ", T = " << time_to_mat[i+1] << ", hedging PnL = " << sum << std::endl;
        }
		//std::cout << "Nb days of delta hedging: " << count << std::endl;
		//std::cout << "Sum of delta hedging = " << sum << std::endl;
		//std::cout << "Total PnL = " << PnL << std::endl;
		return PnL;

	}
	
		double beVolatilityComputation::PnlComputation(underlying& undl, std::vector<double> rt,double strike, double vol, std::vector<double> time_to_mat, std::size_t start)
	{
		double BSPrice0; //Call price at the beginning
		double BSPriceT; //Call price at the end
		double dlt;
		double UndlNew;
		//get the first value of underlying at time 0
		double UndlOld = undl.get_underlying(start);
		//std::cout << "intial strike: " << strike << std::endl;
		//std::cout << "intial undlold: " << UndlOld<< std::endl;
		BSPrice0 = BSPricer(UndlOld, time_to_mat[start] / 365, strike, rt[start], vol);
		//std::cout << "initial price of option is: " << BSPrice0 << std::endl;
		//change this to payoff (last value of the call is its payoff)
		BSPriceT = std::max(undl.get_underlying(0) - strike, 0.0);
		//std::cout << "Final payoff = " << BSPriceT << std::endl;
		//intitialize the PnL
		double PnL=BSPriceT-BSPrice0;
		//std::cout << "PnL from option = " << PnL << std::endl;
		//std::cout << "Time to maturity at 0: " << time_to_mat[start] / 365 << std::endl;
		double sum = 0;
		std::size_t count = 0;
		for(int i = (undl.get_size() - 2); i >= 0; i--)
        {
			UndlNew=undl.get_underlying(i);
			dlt=Delta(UndlOld, time_to_mat[i+1]/365, strike, rt[i+1], vol);//On Calcul delta en t-1
			PnL-=dlt*(UndlNew-UndlOld);
			sum -= dlt*(UndlNew - UndlOld);
			UndlOld=UndlNew;
			count += 1;
			//std::cout << "New value of Underlying: " << UndlNew << ", Delta = " << dlt << ", T = " << time_to_mat[i+1] << ", hedging PnL = " << sum << std::endl;
        }
		//std::cout << "Nb days of delta hedging: " << count << std::endl;
		//std::cout << "Sum of delta hedging = " << sum << std::endl;
		//std::cout << "Total PnL = " << PnL << std::endl;
		return PnL;

	}
	
	double beVolatilityComputation::midpoint_algo(underlying& undl, double rt, double strike, std::vector<double> time_to_mat, double min_vol, double max_vol, double tol, std::size_t max_iter)
	{
		//test to see if the real value of bevol is inclulded in the boundaries
		double h_PnL = PnlComputation(undl, rt, strike, max_vol, time_to_mat, undl.get_size() - 1);
		double l_PnL = PnlComputation(undl, rt, strike, min_vol, time_to_mat, undl.get_size() - 1);
		//std::cout << "h_PnL = " << h_PnL << ", l_PnL = " << l_PnL << std::endl;
		if (((h_PnL < 0) && (l_PnL < 0)) || ((h_PnL > 0) && (l_PnL > 0)))
		{
			std::cout << "The boundaries for the volatility do not contain a value where the PnL would reach 0. Strike " << m_strike << " cannot be solved." << std::endl;
			return 0;
		}
		//set initial value of beVol
		double beVol = (min_vol + max_vol)/2;
		//initialize the first value of the PnL with the midpoint between min_vol and max_vol
		double newPnL = PnlComputation(undl, rt, strike, beVol, time_to_mat, undl.get_size()-1);
		//initilize the number of iteration
		std::size_t nb_iter = 1;
		//loop while until we reach the given tolerance
		//std::cout << "Initial value of PnL: " << newPnL << std::endl;
		while (std::fabs(newPnL)>tol)
		{
			//std::cout << "Current beVol = " << beVol << std::endl;
			if (newPnL < 0)
			{
				//std::cout << "PnL > 0" << std::endl;
				max_vol = beVol;
				//std::cout << "New max_vol = " << max_vol << std::endl;
			}
			else
			{
				//std::cout << "PnL < 0" << std::endl;
				min_vol = beVol;
				//std::cout << "New min_vol = " << min_vol << std::endl;
			}
			//std::cout << "iteration: " << nb_iter << " PnL is now: " << newPnL << std::endl;
			//check if the number of iteration was reach. If so, we take the last value of volatility as the beVol and return an error message
			nb_iter += 1;
			if (nb_iter > max_iter)
			{
				std::cout << "The maximum number of iteration has been reached the current value of PnL is: " << newPnL << ". The process will be stopped." << std::endl;
				return beVol;
			}
			beVol = (min_vol + max_vol) / 2;
			//std::cout << "min_vol = " << min_vol << ", max_vol = " << max_vol << ", beVol = " << beVol << std::endl;
			newPnL = PnlComputation(undl, rt, strike, beVol, time_to_mat, undl.get_size() - 1);
			//std::cout << "new bevol = " << beVol << ", new PnL = " << newPnL << std::endl;
		}
		//std::cout << "Last value of PnL is: " << newPnL << ", Nb_iter = " << nb_iter << std::endl;
		return beVol;
	}
	//overload for rate as vector
	double beVolatilityComputation::midpoint_algo(underlying& undl, std::vector<double> rt, double strike, std::vector<double> time_to_mat, double min_vol, double max_vol, double tol, std::size_t max_iter)
	{
		//test to see if the real value of bevol is inclulded in the boundaries
		double h_PnL = PnlComputation(undl, rt, strike, max_vol, time_to_mat, undl.get_size() - 1);
		double l_PnL = PnlComputation(undl, rt, strike, min_vol, time_to_mat, undl.get_size() - 1);
		//std::cout << "h_PnL = " << h_PnL << ", l_PnL = " << l_PnL << std::endl;
		if (((h_PnL < 0) && (l_PnL < 0)) || ((h_PnL > 0) && (l_PnL > 0)))
		{
			std::cout << "The boundaries of 0% and 100% for the volatility do not contain a value where the PnL would reach 0. Strike " << m_strike << " cannot be solved." << std::endl;
			return 0;
		}
		//set initial value of beVol
		double beVol = (min_vol + max_vol) / 2;
		//initialize the first value of the PnL with the midpoint between min_vol and max_vol
		double newPnL = PnlComputation(undl, rt, strike, beVol, time_to_mat, undl.get_size() - 1);
		//initilize the number of iteration
		std::size_t nb_iter = 1;
		//loop while until we reach the given tolerance
		//std::cout << "Initial value of PnL: " << newPnL << std::endl;
		while (std::fabs(newPnL)>tol)
		{
			//std::cout << "Current beVol = " << beVol << std::endl;
			if (newPnL < 0)
			{
				//std::cout << "PnL > 0" << std::endl;
				max_vol = beVol;
				//std::cout << "New max_vol = " << max_vol << std::endl;
			}
			else
			{
				//std::cout << "PnL < 0" << std::endl;
				min_vol = beVol;
				//std::cout << "New min_vol = " << min_vol << std::endl;
			}
			//std::cout << "iteration: " << nb_iter << " PnL is now: " << newPnL << std::endl;
			//check if the number of iteration was reach. If so, we take the last value of volatility as the beVol and return an error message
			nb_iter += 1;
			if (nb_iter > max_iter)
			{
				std::cout << "The maximum number of iteration has been reached the current value of PnL is: " << newPnL << ". The process will be stopped." << std::endl;
				return beVol;
			}
			beVol = (min_vol + max_vol) / 2;
			//std::cout << "min_vol = " << min_vol << ", max_vol = " << max_vol << ", beVol = " << beVol << std::endl;
			newPnL = PnlComputation(undl, rt, strike, beVol, time_to_mat, undl.get_size() - 1);
			//std::cout << "new bevol = " << beVol << ", new PnL = " << newPnL << std::endl;
		}
		//std::cout << "Last value of PnL is: " << newPnL << ", Nb_iter = " << nb_iter << std::endl;
		return beVol;
	}

	double beVolatilityComputation::get_BeVol() const
	{
		return m_bevol;
	}

	void beVolatilityComputation::update_strike(const double strike, underlying undl)
	{
		m_strike = (strike / 100) * undl.get_underlying(undl.get_size() - 1);
	}
	
	beVolatilityComputation::~beVolatilityComputation()
	{
	}

	double beVolatilityComputation::get_strike() const
	{
		return m_strike;
	}
}