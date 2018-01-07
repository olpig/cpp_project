#include <iostream>
#include <cmath>
#include <vector>
#include "classes.hpp"
#include "underlying.hpp"
#include "ComputeBeVol.hpp"
#include "gnuplot_i.hpp" //Gnuplot class handles POSIX-Pipe-communikation with Gnuplot

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__)
 #include <conio.h>   //for getch(), needed in wait_for_key()
 #include <windows.h> //for Sleep()
 void sleep(int i) { Sleep(i*1000); }
#endif

#define SLEEP_LGTH 2  // sleep time in seconds
#define NPOINTS    50 // length of array

void wait_for_key(); // Programm halts until keypress

using std::cout;
using std::endl;

// To compile
//
// Windows users:
// mkdir build
// cd build
// cmake -G "NMake Makefiles" ..
// nmake

int main(int argc, char* argv[])
{
	//we first setup the data in an underlying object
	undl::parser file_stock;
	file_stock.readfile();
	undl::underlying UL(file_stock.get_data(), file_stock.get_dates());
	std::cout << "Date: " << UL.get_date(0) << " Stock Price: " << UL.get_underlying(0) << std::endl;
	std::cout << UL.get_size() << std::endl;
	// //std::vector<double> rates; A instancier avec une courbe de taux
	// //project::rate rate(rates); Si on utilise une courbe de taux
	//project::flat_rate rate(0.1);
	project::beVolatilityComputation tmp(UL, 0.0, 0.1);
	//project::beVolatilityComputation tmp(UL,rate.get_rate() , 0.1);
	double k = 50.0;
	double increment_k = 5.0;
	double max_k = 150.0;
	std::vector<double> v_beVol;
	double beVol = 0.0;
	std::size_t count = 0;
	std::vector<double> v_AllStrikes; //Je crée un vector avec tous les strikes pour le plotting
	

	while (k < max_k + 1)
	{
		tmp.update_strike(k);
		beVol = tmp.midpoint_algo(0.001, 1, 0.00001, 10000);
		v_beVol.push_back(beVol);
		v_AllStrikes.push_back(k);
		std::cout << "Breakeven vol at strike: " << tmp.get_strike() << " = " << v_beVol[count] << std::endl;
		count += 1;
		k += increment_k;
	}
	//
    // Plotting Using the GnuplotException class
    //
	// FOR MICROSOFT if path-variable for gnuplot is not set, do it with:
    //Gnuplot::set_GNUPlotPath("C:/Program Files/gnuplot/bin/");
    try
    {
        Gnuplot g1("lines");
		cout << endl << endl << "*** user-defined lists of points (x,y)" << endl;
        g1.set_grid();
        g1.set_style("points").plot_xy(v_AllStrikes,v_beVol,"user-defined points 2d");
		g1.showonscreen();
		wait_for_key();

    }
    catch (GnuplotException ge)
    {
        cout << ge.what() << endl;
    }
	//tmp.update_strike(100.0);
	//tmp.PnlComputation(UL, 0.0, tmp.get_strike(), 0.0619, tmp.read_TtoM(), UL.get_size() - 1);
	//std::cout << "Breakeven vol for strike " << tmp.get_strike() << " = " << tmp.midpoint_algo(0.001, 1, 0.00001, 10000) << std::endl;
		
	return 0;
}
void wait_for_key ()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__)  // every keypress registered, also arrow keys
    cout << endl << "Press any key to continue..." << endl;

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    _getch();
#elif defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
    cout << endl << "Press ENTER to continue..." << endl;

    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();
#endif
    return;
}
