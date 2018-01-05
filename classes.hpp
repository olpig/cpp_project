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
		bevolatility(std::size_t size);//& vol = //insert code for vector of 0// ); Si on lui impose une valeur arbitraire on ne pourra plus la modifier après
		//est-ce que le const va marcher si on veut le modifier après
		//Le constructeur ne doit prendre que la taille du vecteur en param je crois
		double get_bevolatility(std::size_t index) const; //read method
		void set_bevolatility(std::size_t index, double bevol); //const; //Question pour const encore car on veut modifier un vector qui est constant
		//type void car on ne renvoie rien 
		~bevolatility();

	private:
		std::vector<double> m_bevol;
	};


	class rate
	{
	public:
		explicit rate(std::vector<double> rates);
		virtual double get_rate(std::size_t maturity) const;
		virtual ~rate();
	protected:

	private:
		std::vector<double> m_rate;
	};
	//Je me pose la question de la redondance de la classe flat_rate car 
	//en soi flatrate= rate avec un vecteur de taille 1
	class flat_rate : public rate
	{
	public:
		flat_rate(double rate);
		virtual double get_rate() const;
		virtual ~flat_rate();
	protected:

	private:
		double m_rate;
	};
	
	double BSPricer(double spot, int time_to_mat, double strike, double rt ,double vol);
	
	//double undl parce que je n'ai besoin que d'un undl précis
	double Delta(double spot, int time_to_mat, double strike, double rt ,double vol);	


	double normal_cdf(double x);
	double normal_pdf(double x);

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
