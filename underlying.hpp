#ifndef UNDERLYING_HPP
#define UNDERLYING_HPP

#include <iostream>
#include <cmath>
#include <vector>
//for the parser:
#include <iterator>
#include <fstream>
#include <sstream>
#include <string>

namespace undl
{
	class underlying
	{
		public:
			underlying(const std::vector<double> UndlData, const std::vector<double> Dates);
			double get_underlying(std::size_t index);
			double get_date(std::size_t index);
			std::vector<double> read_underlying();
			std::vector<double> read_date();
			std::size_t get_size();
			~underlying();
		
		private:
			std::vector<double> m_UndlData;
			std::vector<double> m_Date;
			std::size_t m_size;
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

	class parser
	{
	public:
		parser();
		void readfile();
		//std::istream& operator>>(std::istream& str, undl::CSVRow& data);
		std::vector<double> get_dates();
		std::vector<double> get_data();
		~parser();

	private:
		std::vector<double> m_v1;
		std::vector<double> m_v2;
	};

}
#endif

