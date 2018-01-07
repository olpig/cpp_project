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
		beVolatilityComputation(undl::underlying undl, double rt);
		//overload with a vector for rates
		beVolatilityComputation(undl::underlying undl, std::vector<double> rt);
		//read methods
		std::vector<double> read_TtoM() const;// Est-ce vraiment utile?
		double get_BeVol() const;
		double get_rate() const;//Si on met directement l'objet rate ou flat rate on n'aura pas besoin de get_rate
		std::vector<double> read_undl();//est-ce vraiment utile?
		double get_strike() const;//est-ce vraiment utile?

		//write methods
		void update_strike(const double strike);

		//other methods		
		double PnlComputation(undl::underlying undl, double rt, double strike, double vol, std::vector<double> time_to_mat, std::size_t start);
		double PnlComputation(undl::underlying undl, std::vector<double> rt, double strike, double vol, std::vector<double> time_to_mat, std::size_t start);// avec une courbe des taux
		
		double midpoint_algo(double min_vol, double max_vol, double tol, std::size_t max_iter);
		
		~beVolatilityComputation();

	private:
		//On utilise la fonction directement dans ComputeBeVolatility donc pas besoin de l'avoir en public
		//Je mettrai ces 3 fonctions en private car elles ne sont pas nécessaires à l'extérieur de la classe
		/*double PnlComputation(undl::underlying undl, double rt, double strike, double vol, std::vector<double> time_to_mat, std::size_t start);
		double PnlComputation(undl::underlying undl, std::vector<double> rt, double strike, double vol, std::vector<double> time_to_mat, std::size_t start);// avec une courbe des taux
		double midpoint_algo(double min_vol, double max_vol, double tol, std::size_t max_iter);
		*/
		double m_bevol;//Stock la bevol
		undl::underlying m_undl;
		double m_rt;
		std::vector<double> m_rts;
		//std::vector<double> m_rts;// je ne sais pas si c'est nécessaire mais c'est pour l'overload au cas ou
		double m_strike;
		std::vector<double> m_time_to_mat;
	};
}
#endif