#include <iostream>
#include <cmath>
#include "underlying.hpp"

namespace project
{
#ifndef CLASSES_HPP
#define CLASSES_HPP

#include <iostream>
#include <cmath>
#include <vector>

namespace project
{	
	class beVolatilityComputation
	{
	public:
		beVolatilityComputation(underlying undl, double rt,double strike, double volstart,vector<int> time_to_mat);
		double ComputeBeVolatility(underlying undl, double rt,double strike, double vol,vector<int> time_to_mat);
		double get_BeVol() const;
		
		~beVolatilityComputation();
	private:
		double PnlComputation(underlying undl, double rt,double strike, double vol,vector<int> time_to_mat);
		//On utilise la fonction directement dans ComputeBeVolatility donc pas besoin de l'avoir en public
		double m_bevol;//Stock la bevol
		underlying m_undl;
		double rt;
		double m_strike;
		double m_vol; //Je ne la nomme pas volstart car sa v&aleur devrait changer mais à checker
		vector<int> m_time_to_mat;
	}
}
#endif

//commentaire Mounah
//Une classe pricer fait-elle vraiment sens en terme de mémoire
// Sachant que le time to mat évolue et qu'en soit cette classe
// ne contiendra que des fonctions
// Du coup peut-être qu'en terme de mémoire et de perf on sera gagnant en n'implémant que des fonctions


/*
class pricer()
{
public:
pricer(underlying undl, int time_to_mat, double strike,double rt ,double vol);
double compute_delta();
double compute_price(); //is this really needed?
protected:
private:
std::vector<double> m_volatility;
};
*/





}
