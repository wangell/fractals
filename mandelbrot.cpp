#include <iostream>
#include <complex>
#include <cmath>
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{
	const int xres = 10000;
	const int yres = 10000;

	const double min_x = -2.0;
	const double max_x = .8;
	const double min_y = -1.3;
	const double max_y = 1.3;

	const int max_iter = 120;

	const double pix_worth_x = (abs(min_x) + abs(max_x))/xres;
	const double pix_worth_y = (abs(min_y) + abs(max_y))/yres;

	ofstream q;
	q.open(argv[1]);
	q<<"P3\n"<<xres<<" "<<yres<<"\n255\n";

	for (int y = 0; y < yres; ++y)
	{
		if (y%1000 == 0)
			cout<<"Line: "<<y<<endl;
		for (int x = 0; x < xres; ++x)
		{
			complex<double> c(min_x+x*pix_worth_x, min_y+y*pix_worth_y);
			complex<double> z(0,0);
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
				q<<0<<" "<<0<<" "<<(255/max_iter)*k<<" ";
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
