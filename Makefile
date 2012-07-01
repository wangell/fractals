all: julia mandelbrot
julia: julia.cpp
	g++ julia.cpp -o julia
mandelbrot: mandelbrot.cpp
	g++ mandelbrot.cpp -o mandelbrot
