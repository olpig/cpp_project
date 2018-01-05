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

	underlying::underlying(const std::vector<double> UndlData)
		: m_UndlData(UndlData)
	{
	}

	double underlying::get_underlying(std::size_t index)
	{
		return m_UndlData[index];
	}

	underlying::~underlying()
	{
		/*
		delete[] m_UndlData;
		m_UndlData= nullptr;
		*/
		//m_UndlData is a vector not a pointer
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

}