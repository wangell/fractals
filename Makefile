all: julia mandelbrot buddhabrot viewer
julia: julia.cpp
	g++ julia.cpp -o bin/julia
mandelbrot: mandelbrot.cpp
	g++ mandelbrot.cpp -o bin/mandelbrot -fopenmp
buddhabrot: buddhabrot.cpp
	g++ buddhabrot.cpp -o bin/buddhabrot -fopenmp
viewer: viewer.cpp
	g++ viewer.cpp -o bin/viewer -lSDL
