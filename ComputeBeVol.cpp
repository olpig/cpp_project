// TO COMPILE:
//
// WINDOWS USERS
// mkdir build
// cd build
// cmake -G "NMake Makefiles" ..
// nmake
#include <iostream>
#include <cmath>
#include "ComputeBeVol.hpp"

namespace project
{

	beVolatilityComputation::beVolatilityComputation(underlying undl, double rt,double strike, double volstart,vector<int> time_to_mat)
		:m_undl(undl),m_rt(rt),m_strike(strike),m_vol(volstart),m_time_to_mat(time_to_mat)
		{
		}
	double beVolatilityComputation::PnlComputation(underlying undl, double rt,double strike, double vol,vector<int> time_to_mat)
	{	

		double BSPrice0; //Call price at the beginning
		double BSPriceT; //Call price at the end
		double Delta;
		double UndlOld;
		double UndlNew;
		double PnL=0.;
		UndlOld=undl.getundl(time_to_mat.begin());
		BSPrice0=BSPricer(UndlOld, time_to_mat.begin(), strike, rt, vol);
		//Je ne suis pas sur de moi pour la valeur de getundl et de time_to_mat, Je veux prendre la première et la dernière valeur à chaque fois 
		BSPriceT=BSPricer(undl.get_undl(time_to_mat.end()), time_to_mat.end(), strike, rt, vol);
		PnL=BSPriceT-BSPrice0;
		//1er delta
		for(int i = 1; i< time_to_mat.size; ++i) //Il faut voir si les vecteurs commencent à 0 ou à 1
        {
			UndlNew=undl.getundl(i);//verifier que le type concorde car on avait peut etre mis un size_t pour l'index de l'undl
			Delta=BSPricer(UndlOld, time_to_mat[i-1], strike, rt, vol);//On Calcul delta en t-1
			PnL+=Delta*(UndlNew-UndlOld);
			UndlOld=UndlNew;
        }
		return PnL;
	}
	double beVolatilityComputation::ComputeBeVolatility(underlying undl, double rt,double strike, double vol,vector<int> time_to_mat)
	{
		//Je vais implémenter la méthode de la dichotomy
		double beVol;
		double volMin;
		double volMax;
		volMin=0;
		volMax=0.5;
		beVol=(volMin+volMax)/2;//Je fais deux fois le même calcul mais pour l'instant je n'ai pas eu d'autres idées
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
	}
	double beVolatilityComputation::get_BeVol() const
	{
		return m_bevol;
	}
	beVolatilityComputation::~beVolatilityComputation()
	{
	}
}