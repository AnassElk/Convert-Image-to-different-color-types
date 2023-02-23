Image Processing Project
------------------------

This project is a C++ program that implements various image processing functions. The program consists of several C++ header and source files that are used to define classes, structs, and functions that perform specific tasks related to image processing.

Dependencies
------------

This project has the following dependencies:

- C++ compiler that supports C++17


Files and Directories
---------------------

The project consists of the following files and directories:

- `Pixel.h`: Header file that defines the Pixel class template
- `Image.h`: Header file that defines the Image base class
- `ImageRGB.h`: Header file that defines the ImageRGB class, which inherits from Image
- `ImageGris.h`: Header file that defines the ImageGris class, which inherits from Image
- `ImageNB.h`: Header file that defines the ImageNB class, which inherits from Image
- `Librairie.h`: Header file that defines the Librairie class, which manages a collection of images
- `Foncteurs.h`: Header file that defines several functors used for image processing
- `UtilitaireConversion.h`: Header file that defines several functions used for image conversion
- `Pixel.cpp`: Source file that implements the Pixel class template
- `Image.cpp`: Source file that implements the Image base class
- `ImageRGB.cpp`: Source file that implements the ImageRGB class
- `ImageGris.cpp`: Source file that implements the ImageGris class
- `ImageNB.cpp`: Source file that implements the ImageNB class
- `Librairie.cpp`: Source file that implements the Librairie class
- `Foncteurs.cpp`: Source file that implements the functors defined in Foncteurs.h
- `UtilitaireConversion.cpp`: Source file that implements the functions defined in UtilitaireConversion.h
- `main.cpp`: Source file that contains the main function, which tests the image processing functions

Usage
-----

The `main` function in `main.cpp` contains several tests that demonstrate the functionality of the various classes and functions defined in this project. To run the tests, build and run the project as described in the previous section.

The program loads several test images from the `Originaux` directory and performs various image processing operations on them, including pixel manipulation, image conversion, and image comparison. The program then saves the processed images to the `Copies` directory.

The program also prints the results of the tests to the console, indicating whether each test passed or failed. The total number of points earned by passing the tests is also printed to the console.
