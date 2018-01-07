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
#include "underlying.hpp"

namespace project
{

	underlying::underlying(const std::vector<double> UndlData, const std::vector<double> Dates)
		: m_UndlData(UndlData), m_Date(Dates)
	{
		m_size = m_UndlData.size();
		std::vector<double> res(get_size());
		std::vector<double> date = read_date();
		std::transform(date.begin(), date.end(), res.begin(), [&](double arg) {return get_date(0) - arg; });
		m_time_to_mat = res;
	}
	std::size_t underlying::get_size()
	{
		return m_size;
	}

	double underlying::get_underlying(std::size_t index)
	{
		return m_UndlData[index];
	}

	double underlying::get_date(std::size_t index)
	{
		return m_Date[index];
	}

	underlying::~underlying()
	{
	}
	std::vector<double> underlying::read_underlying()
	{
		return m_UndlData;
	}
	std::vector<double> underlying::read_date()
	{
		return m_Date;
	}
	std::vector<double> underlying::read_TtoM()
	{
		return m_time_to_mat;
	}

	std::string const& CSVRow::operator[](std::size_t index) const
	{
		return m_data[index];
	}
	std::size_t CSVRow::size() const
	{
		return m_data.size();
	}
	void CSVRow::readNextRow(std::istream& str)
	{
		std::string line;
		std::getline(str, line);
		std::stringstream lineStream(line);
		std::string cell;

		m_data.clear();

		while (std::getline(lineStream, cell, ','))
		{
			m_data.push_back(cell);
		}
		// This checks for a trailing comma with no data after it.
		if (!lineStream && cell.empty())
		{
			// If there was a trailing comma then add an empty element.
			m_data.push_back("");
		}
	}

	parser::parser()
		:m_v1(), m_v2()
	{
	}

	parser::~parser()
	{
	}
	std::istream& operator>>(std::istream& str, CSVRow& data)
	{
		data.readNextRow(str);
		return str;
	}
	void parser::readfile()
	{

		std::string filepath;

		std::cout << "Please, enter file name: ";
		std::getline(std::cin, filepath);
		std::cout << "Treating file: " << filepath << std::endl;

		std::ifstream file(filepath);

		CSVRow row;

		while (file >> row)
		{
			//adding element by element to v1 and v2
			m_v1.push_back(std::stod(row[0]));
			m_v2.push_back(std::stod(row[1]));
		}
	}
	std::vector<double> parser::get_v1()
	{
		return m_v1;
	}
	std::vector<double> parser::get_v2()
	{
		return m_v2;
	}


}