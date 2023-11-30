# Simulation of Evolution

## 1. Introduction

### 1.1 Purpose
The purpose of this program is to simulate the process of evolution, allowing users to observe the emergence, adaptation, and progression of populations over time.

### 1.2 Scope
The simulation will focus on key aspects of evolution, including reproduction, mutation, natural selection, and environmental factors.

## 2. System Requirements

### 2.1 Software Requirements
- Operating System: Windows 10, macOS, or Linux
- Programming Language: C++ (C++11 or later)
- External Libraries: Qt, Matplot++

## 3. Functional Requirements

### 3.1 Population Initialization
The program will generate an initial population of organisms with random genetic traits or with user defined traits.

### 3.2 Reproduction
Organisms will reproduce based on their genetic traits, passing on a combination of their genetic material to the next generation.

### 3.3 Mutation
Random mutations may occur during reproduction, introducing genetic diversity to the population.

### 3.4 Natural Selection
Environmental factors will affect the survival and reproduction of organisms, simulating natural selection. Fitness functions will determine an organism's likelihood of survival.

### 3.5 Environmental Changes
The environment may undergo changes over time, influencing the selection pressures on the population. These changes are induced by the user.

### 3.6 Simulation Time
The user can specify the duration of the simulation and observe the changes in the population over time. Also the simulation can be paused at any time.

### 3.7 Visualization
The program will provide graphical representation of the evolving population, including population size, genetic diversity, and environmental changes.

### 3.8 Data Logging
The simulation will log relevant data at each generation, allowing users to analyze the evolutionary process retrospectively and create graphs.

## 4. Non-functional Requirements

### 4.3 User Interface
The user interface should be implemented using simple graphical interface, providing controls for adjusting simulation parameters, starting and pausing the simulation, and viewing results.

### 4.4 Extensibility
The program should be designed to allow for easy extension and modification of the simulation rules, genetic traits, and environmental factors.

## 5. Testing

### 5.1 Unit Testing
Individual components of the simulation, such as reproduction and mutation functions, should be thoroughly tested.

### 5.2 Integration Testing
The integration of different components should be tested to ensure they work together seamlessly.

## 6. Documentation

### 6.1 User Manual
A comprehensive user manual will be provided, explaining the program's functionality, parameters, and how to interpret the results.

### 6.2 Code Documentation
The source code will be thoroughly documented, providing comments and explanations for each function and module.
