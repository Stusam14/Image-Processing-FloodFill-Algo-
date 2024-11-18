# building_a_video_from_a_large_image

# A program which creates images filtered according to a certain treshold and it depicts the forground pixels.

This program was/is built as part of an Assingment for my C++ course, it mainly focues on the basics of programming in C++
Getting started

when testing an image , the are multiple images provide , write the name of any of the pgm images converted from png

- Use the command : “make” to compile the code files
- use the command : ./findcomp -s min max -t treshold -w image_out_name -p

# The main behaviour of program files:

# The PGMimageProcessor.h file

- PGMimageProcessor.h file contains all the function prototypes implemented in the PGMImageProcessor.cpp file , it has classes declared holding
  the methods, it consist of construtors and destructors for memory clean up after use.

# The PGMimageProcessor.cpp file

The PGMimageProcessor consist of the necessary code iplementation for reading the pgm image file , storing the data from the image ,
extracting the components and using a flood fill algorithm to get specific components , and contains getter and setters to gain access to private variable

# The ConnectedComponent.h file

- ConnectedComponent.h file contains all the function prototypes implemented in the ConnectedComponent.cpp file , it has classes declared holding
  the methods, it consist of construtors and destructors for memory clean up after use.

# The ConnectedComponent.cpp file

- The ConnectedComponent consist of the necessary code iplementation for storing the components data or storing the data from the image ,
  and contains getter and setters to gain access to private variable

# Tester.cpp

- test the program with differenet set of image inputs , treshold , and min max value

# The Driver.cpp file

- entry point of the pprohram which handles commnad line inputs and outputs as well as execution order of the program.

# This is the entry point of the program , it contains function calls for executions , and is an entry point for command line inputs.

# Makefile

- Build : use “make”
- clean command : cleans up extra object and target files after compiling
