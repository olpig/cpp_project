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
		BSPrice0=BSPricer(UndlOld, time_to_mat[start]/365, strike, rt, vol);
		BSPriceT = std::max(undl.get_underlying(0) - strike, 0.0);
		//intitialize the PnL
		double PnL = BSPriceT-BSPrice0;
		double cash = -BSPrice0 + Delta(UndlOld, time_to_mat[start] / 365, strike, rt, vol)*UndlOld;
		double dt;
		for(int i = (undl.get_size() - 2); i >= 0; i--)
        {
			UndlNew=undl.get_underlying(i);
			dt = (time_to_mat[i + 1] - time_to_mat[i]) / 365;
			dlt=Delta(UndlOld, time_to_mat[i+1]/365, strike, rt, vol);//On Calcul delta en t-1
			PnL -= dlt*(UndlNew - UndlOld)-rt*dt*cash;
			//update the cash position
			cash = cash * (1 + rt*dt) + UndlNew*(Delta(UndlNew, time_to_mat[i] / 365, strike, rt, vol) - dlt);
			UndlOld=UndlNew;
        }
		return PnL;

	}
	//robustness formula
	double beVolatilityComputation::PnlComputation(underlying& undl, double rt, double strike, double vol, std::vector<double> time_to_mat, std::size_t start, bool robust)
	{
		double UndlNew;
		//get the first value of underlying at time 0
		double UndlOld = undl.get_underlying(start);
		//intitialize the PnL
		double PnL = 0;
		for (int i = (undl.get_size() - 2); i >= 0; i--)
		{
			UndlNew = undl.get_underlying(i);
			PnL += 0.5*gamma(UndlNew, time_to_mat[i + 1], strike, rt, vol)*std::pow(UndlNew, 2)*(std::pow((UndlNew - UndlOld) / UndlOld, 2) - std::pow(vol, 2)*(time_to_mat[i + 1] - time_to_mat[i]));
			UndlOld = UndlNew;
		}
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
		BSPrice0 = BSPricer(UndlOld, time_to_mat[start] / 365, strike, rt[start], vol);
		BSPriceT = std::max(undl.get_underlying(0) - strike, 0.0);
		//intitialize the PnL
		//double PnL=BSPriceT-BSPrice0;
		double PnL = BSPriceT- BSPrice0;
		double cash = -BSPrice0 + Delta(UndlOld, time_to_mat[start] / 365, strike, rt[start], vol)*UndlOld;;
		double dt;
		for(int i = (undl.get_size() - 2); i >= 0; i--)
        {
			dt = (time_to_mat[i + 1] - time_to_mat[i]) / 365;
			UndlNew=undl.get_underlying(i);
			dlt=Delta(UndlOld, time_to_mat[i+1]/365, strike, rt[i+1], vol);//On Calcul delta en t-1
			//PnL-=dlt*(UndlNew-UndlOld);
			PnL = PnL - dlt*(UndlNew - UndlOld)+rt[i+1]*dt*cash;
			//sum -= dlt*(UndlNew - UndlOld);
			cash = cash * (1 + rt[i+1]*dt) + UndlNew*(Delta(UndlNew, time_to_mat[i] / 365, strike, rt[i], vol) - dlt);
			UndlOld=UndlNew;
        }
		return PnL;
	}
	
	double beVolatilityComputation::midpoint_algo(underlying& undl, double rt, double strike, std::vector<double> time_to_mat, double min_vol, double max_vol, double tol, std::size_t max_iter, bool robust)
	{
		//test to see if the real value of bevol is inclulded in the boundaries
		double h_PnL;
		double l_PnL;
		if (robust)
		{
			h_PnL = PnlComputation(undl, rt, strike, max_vol, time_to_mat, undl.get_size() - 1, robust);
			l_PnL = PnlComputation(undl, rt, strike, min_vol, time_to_mat, undl.get_size() - 1, robust);
		}
		else
		{
			h_PnL = PnlComputation(undl, rt, strike, max_vol, time_to_mat, undl.get_size() - 1);
			l_PnL = PnlComputation(undl, rt, strike, min_vol, time_to_mat, undl.get_size() - 1);
		}

		if (((h_PnL < 0) && (l_PnL < 0)) || ((h_PnL > 0) && (l_PnL > 0)))
		{
			std::cout << "The boundaries for the volatility do not contain a value where the PnL would reach 0. Strike " << m_strike << " cannot be solved." << std::endl;
			//uncomment to show the value of PnL at the boundaries
			//std::cout << "l_pnl = " << l_PnL << ", h_pnl = " << h_PnL << std::endl;
			return 0;
		}
		//set initial value of beVol
		double beVol = (min_vol + max_vol)/2;
		//initialize the first value of the PnL with the midpoint between min_vol and max_vol
		double newPnL;
		if (robust)
		{
			newPnL = PnlComputation(undl, rt, strike, beVol, time_to_mat, undl.get_size() - 1, robust);
		}
		else
		{
			newPnL = PnlComputation(undl, rt, strike, beVol, time_to_mat, undl.get_size() - 1);
		}

		//initilize the number of iteration
		std::size_t nb_iter = 1;
		//loop while until we reach the given tolerance
		while (std::fabs(newPnL)>tol)
		{
			if (newPnL < 0)
			{
				max_vol = beVol;
			}
			else
			{
				min_vol = beVol;
			}
			//check if the number of iteration was reach. If so, we take the last value of volatility as the beVol and return an error message
			nb_iter += 1;
			if (nb_iter > max_iter)
			{
				std::cout << "The maximum number of iteration has been reached the current value of PnL is: " << newPnL << ". The process will be stopped." << std::endl;
				return beVol;
			}
			beVol = (min_vol + max_vol) / 2;
			if (robust)
			{
				newPnL = PnlComputation(undl, rt, strike, beVol, time_to_mat, undl.get_size() - 1, robust);
			}
			else
			{
				newPnL = PnlComputation(undl, rt, strike, beVol, time_to_mat, undl.get_size() - 1);
			}
		}
		return beVol;
	}
	//overload for rate as vector
	double beVolatilityComputation::midpoint_algo(underlying& undl, std::vector<double> rt, double strike, std::vector<double> time_to_mat, double min_vol, double max_vol, double tol, std::size_t max_iter)
	{
		//test to see if the real value of bevol is inclulded in the boundaries
		double h_PnL = PnlComputation(undl, rt, strike, max_vol, time_to_mat, undl.get_size() - 1);
		double l_PnL = PnlComputation(undl, rt, strike, min_vol, time_to_mat, undl.get_size() - 1);
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
		while (std::fabs(newPnL)>tol)
		{
			if (newPnL < 0)
			{
				max_vol = beVol;
			}
			else
			{
				min_vol = beVol;
			}
			//check if the number of iteration was reach. If so, we take the last value of volatility as the beVol and return an error message
			nb_iter += 1;
			if (nb_iter > max_iter)
			{
				std::cout << "The maximum number of iteration has been reached the current value of PnL is: " << newPnL << ". The process will be stopped." << std::endl;
				return beVol;
			}
			beVol = (min_vol + max_vol) / 2;
			newPnL = PnlComputation(undl, rt, strike, beVol, time_to_mat, undl.get_size() - 1);
		}
		return beVol;
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