# SlimCRYPT

SlimCRYPT is a selection of five encryption algorithms (AES, DES, TEA, SHA-1, Blowfish) implemented in C and intended to be used on any microcontroller platform. On project completion each implementation will be evaluated for time and memory usage.

## Table of Contents
1. [About the Project](#about-the-project)
2. [Project Status](#project-status)
3. [Getting Started](#getting-started)
4. [Authors](#authors)

# About the Project

SlimCRYPT is not only an implementation of selected encryption algorithms but also a full featured evaluation framework for measuring how many clock cycles it took to complete an encryption or decryption of selected algorithm. This project is a part of my master thesis at Silesian University of Technology in Gliwice.

# Project Status

Currently working on implementing a cycle accurate measurements using built-in hardware timers and interupts on ATMega328p.

# Getting Started

Code is developed in Microchip Studio and thus only running the `.atsln` solution file is necessery to start working on the project

# Authors

* **[Michał Granda](https://github.com/majcoch)**
