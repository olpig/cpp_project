#ifndef UNDERLYING_HPP
#define UNDERLYING_HPP

#include <iostream>
#include <cmath>
#include <vector>
//for the parser part:
#include <iterator>
//#include <iostream>
#include <fstream>
#include <sstream>
//#include <vector>
#include <string>

namespace undl
{
	class underlying
	{
		public:
			underlying(const std::vector<double> UndlData, const std::vector<double> Dates);
			double get_underlying(std::size_t index);
			double get_date(std::size_t index);
			~underlying();
		
		private:
			std::vector<double> m_UndlData;
			std::vector<double> m_Date;
	};

	//class representing one row of the csv file
	class CSVRow
	{
	public:
		std::string const& operator[](std::size_t index) const;
		std::size_t size() const;
		void readNextRow(std::istream& str);

	private:
		//m_data is a vector of lenght = nb of columns in the csv file
		std::vector<std::string> m_data;
	};

}
#endif

