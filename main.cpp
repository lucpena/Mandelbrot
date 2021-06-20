#include <iostream>
#include <fstream>
#include <math.h>

int32_t findMandelbrot(double cr, double ci, int32_t max_interations) {

    int32_t i = 0;
    double zr = 0.0, zi = 0.0;

    while (i < max_interations && zr * zr + zi * zi < 4.0) { // Magnitude function

        double temp = zr * zr - zi * zi + cr;
        zi = 2.0 * zr * zi + ci;
        zr = temp;
        i++;

    }

    return i;

}

// Integer to Real
double mapToReal(int32_t x, int32_t imageWidth, double minR, double maxR) {

    double range = maxR - minR;
    return x * (range / imageWidth) + minR;

}

// Integer to Imaginary
double mapToImaginary(int32_t y, int32_t imageHeight, double minI, double maxI) {

    double range = maxI - minI;
    return y * (range / imageHeight) + minI;

}

int main(){

    // Get the input values from a text file
    std::ifstream fin("input.txt");

    int32_t imageWidth, imageHeight, maxN;
    double minR, maxR, minI, maxI;

    if(!fin){

        std::cerr << "Error opening the file..." << std::endl;
        std::cin.ignore();
        return 0;

    }

    fin >> imageWidth >> imageHeight >> maxN;
    fin >> minR >> maxR >> minI >> maxI;

    fin.close();

    // Open the output file and writes the PPM header for the img output
    std::ofstream fout("mandelbrot.ppm");
    
    fout << "P3" << std::endl;                                  // Sets the image as PPM
    fout << imageWidth << " " << imageHeight << std::endl;      // Dimensions
    fout << "256" << std::endl;                                 // Max RGB numbers

    // Now we generate the image.
    // Going through every pixel.
    for( uint32_t y = 0; y < imageHeight; y++ ) {       // Rows
        for( uint32_t x = 0; x < imageWidth; x++ ){     // Columns

            // Find the real and imaginary values for C
            double cr = mapToReal(x, imageWidth, minR, maxR);
            double ci = mapToReal(y, imageHeight, minI, maxI);

            // Find the number of iterations in the Manelbrot
            int32_t n = findMandelbrot(cr, ci, maxN);

            // Mapping the result number to a RGB value
            int  r = ( n % 256);
            int  g = ( n % 256);
            int  b = ( n % 256);

            // Output the image
            fout <<  r << " " << g << " " << b << " ";

        }

        fout << std::endl;
    }

    fout.close();
    std::cout << "Success." << std::endl;
    return 0;
}
