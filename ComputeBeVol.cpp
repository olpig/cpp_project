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

	beVolatilityComputation::beVolatilityComputation(undl::underlying undl, double rt, double strike, double volstart)
		:m_undl(undl), m_rt(rt), m_strike(strike), m_vol(volstart)
	{
		std::vector<double> res(undl.get_size());
		std::vector<double> date = undl.read_date();
		std::transform(date.begin(), date.end(), res.begin(), [&](double arg) {return undl.get_date(0) - arg; });
		m_time_to_mat = res;
	}
	
	double beVolatilityComputation::PnlComputation(undl::underlying undl, double rt,double strike, double vol, std::vector<double> time_to_mat, std::size_t start)
	{	
		
		double BSPrice0; //Call price at the beginning
		double BSPriceT; //Call price at the end
		double dlt;
		double UndlNew;
		//get the first value of underlying at time 0
		double UndlOld = undl.get_underlying(start);
		BSPrice0=BSPricer(UndlOld, time_to_mat[start], strike, rt, vol);
		//change this to payoff (last value of the call is its payoff)
		BSPriceT = std::max(undl.get_underlying(0) - strike, 0.0);
		//intitialize the PnL
		double PnL=BSPriceT-BSPrice0;
		
		for(int i = 1; i < undl.get_size(); i++)
        {
			UndlNew=undl.get_underlying(i);
			dlt=Delta(UndlOld, time_to_mat[i-1], strike, rt, vol);//On Calcul delta en t-1
			PnL-=dlt*(UndlNew-UndlOld);
			UndlOld=UndlNew;
        }
		return PnL;

	}
	
	double beVolatilityComputation::midpoint_algo(double min_vol = 0., double max_vol = 1., double tol = 0.0001, std::size_t max_iter = 10000)
	{
		
		//set initial value of beVol
		double beVol = (min_vol + max_vol)/2;
		//double oldPnL = PnlComputation(m_undl, m_rt, m_strike, beVol, m_time_to_mat);
		//rest of code here
		return 0.0;
	}

	double beVolatilityComputation::ComputeBeVolatility(undl::underlying undl, double rt,double strike, double vol, std::vector<int> time_to_mat)
	{
		/*
		//this method will loop over time to maturity to get an average of beVol to put in the volatility skew vector
		//it will change the value of the data member m_bevol
		//code to be transfered to midpoint_algo method
		while	(fabs(PnlComputation(undl, rt,strike, beVol,time_to_mat))>0.00001)
		{
			beVol=(volMin+volMax)/2;
			
			if(PnlComputation(undl, rt,strike, beVol,time_to_mat) > 0)
			{
				volMax=beVol;
			}
			else
			{
				volMin=beVol;
			}
		
		}
		m_bevol=beVol;
		return bevol;
		*/
		return 0.0;
	}
	double beVolatilityComputation::get_BeVol() const
	{
		return m_bevol;
	}

	void beVolatilityComputation::update_strike(const double strike)
	{
		m_strike = strike;
	}
	
	std::vector<double> beVolatilityComputation::read_TtoM() const
	{
		return m_time_to_mat;
	}
	double beVolatilityComputation::get_rate() const
	{
		return m_rt;
	}
	std::vector<double> beVolatilityComputation::read_undl()
	{
		return m_undl.read_underlying();
	}

	
	beVolatilityComputation::~beVolatilityComputation()
	{
		//delete[] p_undl;
		//p_undl = nullptr;
	}
}