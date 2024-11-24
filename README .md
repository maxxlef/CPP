# Introduction
This document covers two small projects that provided me with hands-on experience in C++. The first project simulates autonomous cars driving on a circular road, where I apply object-oriented programming concepts and basic system simulation. The second project focuses on maze generation and pathfinding, with an emphasis on working with pointers and dynamic memory management. For both projects, I use VIBES to incorporate graphical features, and I will explain how to install and use it for visualization.

# Table of Contents

- [A. Graphical Displays with VIBes](#a-graphical-displays-with-vibes)
  - [A1. Installation / Option 1: Direct Download of the Executable](#a1-installation--option-1-direct-download-of-the-executable)
  - [A2. Installation / Option 2: Compile from Source](#a2-installation--option-2-compile-from-source)
  - [A3. Communicating with VIBes](#a3-communicating-with-vibes)
- [B. Autonomous Car](#b-autonomous-car)
  - [B1. Overview](#b1-overview)
  - [B2. Code Structure](#b2-code-structure)
  - [B3. How to Run](#b3-how-to-run)
- [C. Maze](#c-maze)
  - [C1. Overview](#c1-overview)
  - [C2. Code Structure](#c2-code-structure)
  - [C3. How to Run](#c3-how-to-run)
- [Conclusion](#conclusion)



# A. Graphical Displays with VIBes

The VIBes software was developed at ENSTA Bretagne to provide simple graphical features decoupled from the main program logic. It allows you to visualize the path and the robot navigating it. VIBes operates as a standalone executable that runs in parallel with your project. Your project must send graphical instructions to VIBes to display objects. VIBes functions as a graphical server, awaiting commands to render visualizations.
There are two methods (A1 or A2) to install and use VIBes on personal machines.
## A1. Installation / Option 1: Direct Download of the Executable
Precompiled VIBes executables are available on the development repository’s Releases page: https://github.com/ENSTABretagneRobotics/VIBES/releases.
For Linux systems, download the file named VIBes-x.x.x-linux.AppImage.
## A2. Installation / Option 2: Compile from Source
This second option allows you to use the latest features of VIBes, which are optional for this course. The source code for VIBes is available at the following repository:  
https://github.com/ENSTABretagneRobotics/VIBES.
1. Clone the repository in a separate directory using the following command:  
 'git clone https://github.com/ENSTABretagneRobotics/VIBES' 
 (If needed, configure a proxy using git config --global http.proxy http://proxy_address:8080.)
2. Install the required packages (administrative rights are necessary):  
 sudo apt-get install qt5-default libqt5svg5-dev  
3. The VIBes viewer executable must be compiled independently. Navigate to the ./VIBES/viewer/ directory and compile the project using the following commands:  
 `mkdir build`  
 `cd build`  
 `cmake ..`  
 `make`  
 This creates a binary file named VIBes-viewer, which is locally accessible from the build directory.  
4. Optionally, you can install VIBes on your machine (e.g., in system directories outside the build folder) by running:  
 `make install`  
 This allows you to access VIBes directly from the terminal without specifying its path.  
## A3. Communicating with VIBes  
1. Execute the software to launch the graphical server.  
2. Start the VIBes-viewer executable, which will wait for graphical instructions from your project to render objects on the screen.  
By following these steps, you will have VIBes installed and running on your machine.

# B. Autonomous car
## B1. Overview
This project simulates a group of autonomous cars driving on a circular road. The cars regulate their speed and maintain a safe distance from the vehicle in front of them, creating a dynamic, collision-free system. The main goal of this project is to explore key programming concepts in C++, including object-oriented programming, simulation of dynamic systems, and inter-object interactions.

## B2. Code Structure
### main.cpp
The main program file:  
- Initializes the simulation with cars and a road.
- Links cars to create a circular chain.
- Runs a time-stepped simulation to evolve the system and display the results.
### Classes
- **Road**:
Represents a circular road.
Handles operations like distance calculations and collision detection.
- **Car**:
A base class representing a generic car.
Provides attributes like position and speed, and basic methods for movement.
- **AutonomousCar** (inherits from Car):
Adds logic for adapting speed based on the distance to the car in front.
Implements a control law to maintain a safe following distance.
 ## B3. How to run
 - Run VIBES
 - `g++ *.cpp -o run`
 - `./run`

# C. Maze
## C1. Overview
This project implements a graph structure, defines the shortest path search, and visualizes the result. I have gained a deeper understanding of pointers and dynamic memory allocation in C++, although some memory leaks remain unresolved in the code.
## C2. Code Structure
### main.cpp
This file includes the core logic for creating, visualizing, and solving a maze. It includes the following functionalities:  

- Maze Creation: Functions for generating a maze grid of cells and their respective neighbors (paths between cells).
- Graph Visualization: Using the vibes library to visually represent the maze and the paths between cells.
- File Input/Output: Read a maze from a file, save the maze to a file, and load or display the maze accordingly.
- Pathfinding: Implementations for searching the shortest path between the start and end points within the maze.

### Classes and structures 
1. **Cell** Class
Represents a single cell in the maze. It holds coordinates (_x, _y), a list of neighbors, and flags to track the cell's state (e.g., whether it's part of the path).  

2. **Maze** Struct
Holds pointers to the start and end cells of the maze. It's a simple structure that tracks the maze boundaries.

3. **Path** Class
Manages the path through the maze using a linked list of Cell objects. It provides methods to add cells to the path and display connections between them.  

## C3. How to run
 - Run VIBES
 - `g++ *.cpp -o run`
 - `./run`

### Conclusion
The comments in the code are written in French, but I hope the brief explanations provided here will be sufficient for understanding its structure and functionality.

