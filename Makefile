all: julia mandelbrot buddhabrot
julia: julia.cpp
	g++ julia.cpp -o julia
mandelbrot: mandelbrot.cpp
	g++ mandelbrot.cpp -o mandelbrot
buddhabrot: buddhabrot.cpp
	g++ buddhabrot.cpp -o buddhabrot
