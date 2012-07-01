#include <iostream>
#include <complex>
#include <cmath>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv)
{
	const int xres = 5700;
	const int yres = 5500;

	const double min_x = -1.4;
	const double max_x = 1.6;
	const double min_y = -1.0;
	const double max_y = 1.0;

	const int max_iter = 120;

	const double pix_worth_x = (abs(min_x) + abs(max_x))/xres;
	const double pix_worth_y = (abs(min_y) + abs(max_y))/yres;
	
	const complex<double> c(-1.125, .25);

	ofstream q;
	q.open("julia.ppm");
	q<<"P3\n"<<xres<<" "<<yres<<"\n255\n";

	for (int y = 0; y < yres; ++y)
	{
		for (int x = 0; x < xres; ++x)
		{
			complex<double> z(min_x+x*pix_worth_x, min_y+y*pix_worth_y);
			bool outside = false;
			int k = 0;
			for (k = 0; k < max_iter; ++k)
			{
				z = (z*z) + c;
				if (abs(z) > 2)
				{
					outside = true;
					break;
				}
				
			}
			if (outside)
			{
				q<<(254/max_iter)*k<<" "<<0<<" "<<0<<" ";
			}
			else
			{
				q<<0<<" "<<0<<" "<<0<<" ";
			}
		}
		q<<endl;
	}
	q.close();
}
