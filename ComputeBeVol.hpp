#ifndef COMPUTEBEVOL_HPP
#define COMPUTEBEVOL_HPP

#include <iostream>
#include <cmath>
#include <vector>
#include <iostream>
#include <cmath>
#include "underlying.hpp"

namespace project
{
	class beVolatilityComputation
	{
	public:
		beVolatilityComputation(undl::underlying undl, double rt, double strike, double volstart);
		//read methods
		std::vector<double> read_TtoM() const;
		double get_BeVol() const;
		double get_rate() const;
		double read_vol_start() const;
		std::vector<double> read_undl();

		//write methods
		void update_strike(const double strike);

		//this is the method that updates beVol
		double ComputeBeVolatility(undl::underlying undl, double rt,double strike, double vol, std::vector<int> time_to_mat);
		
		//other methods		
		double PnlComputation(undl::underlying undl, double rt, double strike, double vol, std::vector<int> time_to_mat);
		double midpoint_algo(double min_vol, double max_vol, double tol, std::size_t max_iter);
		
		~beVolatilityComputation();

	private:
		//On utilise la fonction directement dans ComputeBeVolatility donc pas besoin de l'avoir en public
		double m_bevol;//Stock la bevol
		undl::underlying m_undl;
		double m_rt;
		double m_strike;
		double m_vol; //Je ne la nomme pas volstart car sa valeur devrait changer mais à checker
		std::vector<double> m_time_to_mat;
	};
}
#endif
