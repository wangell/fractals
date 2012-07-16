#include <iostream>
#include <fstream>
#include <cstdlib>
#include <complex>

#define USE_OPEN_MP

using namespace std;

const bool mandelbrot_calc(const complex<double> c, int max_iter);
const void mandelbrot_plot(const complex<double> c, int max_iter, int, int);

const int x_res = 3000; //5000
const int y_res = 3000;

long plot[y_res][x_res];

int main(int argc, char** argv)
{
	const unsigned int max_iter = 300000000; //20000000
	const int brot_iter = 10000;//2000

	const double min_x = -2;
	const double max_x = .8;
	const double min_y = -1.3;
	const double max_y = 1.3;

	const int pix_x = x_res/(abs(min_x)+abs(max_x));
	const int pix_y = y_res/(abs(min_y)+abs(max_y));

	float prog_counter;

	srand((unsigned)time(NULL));

	cout<<"Generating image..."<<endl;

	#ifdef USE_OPEN_MP
	#pragma omp parallel for schedule(dynamic)
	#endif
	for (int curr_iter = 0; curr_iter < max_iter; ++curr_iter)
	{
		//Generate random
		double c_real = ((double)rand()/(double)RAND_MAX) * 2.8 - 2;
		double c_imag = ((double)rand()/(double)RAND_MAX) * 2.6 - 1.3;

		//Multiply by proper pixel value for plotting
		complex<double> c(c_real,c_imag);

		if(!mandelbrot_calc(c, brot_iter))
		{
			mandelbrot_plot(c, brot_iter, pix_x, pix_y);
		}

	}

	cout<<"Writing image..."<<endl;
	
	ofstream q;
	q.open("../img/buddha.ppm");
	q<<"P3\n"<<x_res<<" "<<y_res<<"\n255\n";

	double long max_val = 0;

	for (int y = 0; y < y_res; ++y)
	{
		for (int x = 0; x < x_res; ++x)
		{
			if (plot[y][x] > max_val)
				max_val = plot[y][x];
		}
	}

	cout<<"Max RGB value: "<<max_val<<endl;

	for (int y = 0; y < y_res; ++y)
	{
		for (int x = 0; x < x_res; ++x)
		{
			q<<0<<" "<<0<<" "<<ceil(((double)255/(double long)max_val)*plot[x][y])<<" ";
		}
		q<<endl;
	}
	q.close();
}

const bool mandelbrot_calc(const complex<double> c, int max_iter)
{
	complex<double> z(0,0);
	for (int j = 0; j < max_iter; ++j)
	{
		z = (z*z) + c;
		if (abs(z) > 2)
		{
			return false;
		}
	}
	return true;
}

const void mandelbrot_plot(const complex<double> c, int max_iter, int pix_x, int pix_y)
{
	complex<double> z(0,0);
	for (int j = 0; j < max_iter; ++j)
	{
		int x = (real(z)+2)*pix_x;
		int y = (imag(z)+1.3)*pix_y;
		if ((x < 0) || (x > x_res-1))
			continue;
		if ((y < 0) || (y > y_res-1))
			continue;
//		cout<<plot[y][x]<<" "<<y<<" "<<x<<" "<<z<<endl;
		if ((imag(z) != 0) && (real(z) != 0))
		{
			plot[y][x] += 1;
		}
		z = (z*z) + c;
		if (abs(z) > 2)
		{
			return;
		}
	}
}
