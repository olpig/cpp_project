// TO COMPILE:
//
// WINDOWS USERS
// mkdir build
// cd build
// cmake -G "NMake Makefiles" ..
// nmake
#include <iostream>
#include <cmath>
#include "underlying.hpp"

namespace undl
{

	underlying::underlying(const std::vector<double> UndlData, const std::vector<double> Dates)
		: m_UndlData(UndlData), m_Date(Dates)
	{
		m_size = m_UndlData.size();
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
		/*
		delete[] m_UndlData;
		m_UndlData= nullptr;
		*/
		//m_UndlData is a vector not a pointer
	}
	std::vector<double> underlying::read_underlying()
	{
		return m_UndlData;
	}
	std::vector<double> underlying::read_date()
	{
		return m_Date;
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
	std::istream& operator>>(std::istream& str, undl::CSVRow& data)
	{
		data.readNextRow(str);
		return str;
	}
	void parser::readfile()
	{

		//set the name of the file to open (this could be done via command line)
		//requires the full path of the file
		std::string filepath;

		std::cout << "Please, enter the full file path: ";
		std::getline(std::cin, filepath);
		std::cout << "Treating file: " << filepath << std::endl;

		std::ifstream file(filepath);

		undl::CSVRow row;

		while (file >> row)
		{
			//adding element by element to v1 and v2
			m_v1.push_back(std::stod(row[0]));
			m_v2.push_back(std::stod(row[1]));
		}
	}
	std::vector<double> parser::get_dates()
	{
		return m_v1;
	}
	std::vector<double> parser::get_data()
	{
		return m_v2;
	}


}