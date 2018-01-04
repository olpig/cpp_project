#include <iostream>
#include <cmath>

namespace project
{
	class bevolatilities()
	{
	//Pourquoi tu utilises du virtual? La classe n'est pas une classe mère, personne n'en hérite
	public:
		bevolatilities(std::size_t size);//& vol = //insert code for vector of 0// ); Si on lui impose une valeur arbitraire on ne pourra plus la modifier après
		//est-ce que le const va marcher si on veut le modifier après
		//Le constructeur ne doit prendre que la taille du vecteur en param je crois
		double get_bevolatility(std::size_t index) const; //read method
		void set_bevolatility(std::size_t index, double bevol) const; //Question pour const encore car on veut modifier un vector qui est constant
		//type void car on ne renvoie rien 
		~bevolatilities();
		//virtual double get_bevolatility(std::size_t index) const; //read method
		//virtual double set_bevolatility(std::size_t index, double bevol) const; //write method
		//virtual ~volatility();
	//protected: //a-t-on besoin de protected si personne n'hérite de cette classe

	private:
		std::vector<double> m_bevols;
	};


	class rate()
	{
	public:
		virtual rates(std::vector<double> rates);
		virtual double get_rate(double maturity) const;
		virtual ~rates();
	protected:

	private:
		std::vector<double> m_rates;
	};
	//Je me pose la question de la redondance de la classe flat_rate car 
	//en soi flatrate= rate avec un vecteur de taille 1
	class flat_rate() : public rate
	{
	public:
		explicit flat_rate(double rate);
		virtual double get_rate() const;
		//virtual double get_rate(double maturity) const;//SI c'est un taux fixe, pas besoin de la maturité
		virtual ~flat_rate();
	protected:

	private:
		double m_rate;
	};
	
	class underlying()
	{
		public:
			underlying(std::vector<double> UndlData);
			double get_underlying(std::size_t UndlPos);
			
			~underlying();
		
		private:
			std::vector<double> m_UndlData;
	}
	
	
	//Une classe pricer fait-elle vraiment sens en terme de mémoire
	// Sachant que le time to mat évolue et qu'en soit cette classe
	// ne contiendra que des fonctions
	// Du coup peut-être qu'en terme de mémoire et de perf on sera gagnant en n'implémant que des fonctions
	double BSPricer(double undl, int time_to_mat, double strike,rate rt ,double vol,std::normal_distribution norm_dist);
	//double undl parce que je n'ai besoin que d'un undl précis
	double Delta(underlying undl, int time_to_mat, double strike,rate rt ,double vol);	
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









}
