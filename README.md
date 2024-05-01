#Powder Simulator

A simple powder toy-like program for my software engineering class

## How to run

- Make sure CMake is installed
- run `cmake .` in the root of the project, then `make` in the same directory
- run `./powdersim` for linux and mac, or `./powdersim.exe` for windows

## Documentation

This project uses Doxygen to document its files. Included in this project is a `Doxyfile.txt` located in the docs directory. This Doxyfile contains the correct configuration to create proper documentation.
To run Doxygen:
- Make sure Doxygen is installed.
- Adjust the input and output configuration in the Doxyfile as needed
- In command line run `doxygen`
- Search for where Doxygen created the `html` folder
- Once in the `html` folder search for `index.html` and open it to view our documentation.
