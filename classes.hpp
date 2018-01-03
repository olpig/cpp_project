#include <iostream>
#include <cmath>

namespace project
{
	class volatility()
	{
	public:
		volatility(const std::vector<double>& vol = //insert code for vector of 0// );
		virtual double get_volatility(std::size_t index) const; //read method
		virtual double set_volatility(std::size_t index) const; //write method
		virtual ~volatility();
	protected:

	private:
		std::vector<double> m_volatility;
	};


	class rate()
	{
	public:

		virtual ~rate();
	protected:

	private:

	};

	class flat_rate() : public rate
	{
	public:
		explicit flat_rate(double rate);
		virtual double get_rate(double maturity) const;
		virtual ~flat_rate();
	protected:

	private:
		double m_rate;
	};

	class pricer()
	{
	public:
		pricer();
		double compute_delta();
		double compute_price(); //is this really needed?

	protected:


	private:
		std::vector<double> m_volatility;
		

	};









}

