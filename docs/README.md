
# Simulation of evolution

## Overview

This project simulates a dynamic environment with evolving creatures. The simulation includes various neural types, allowing creatures to perceive their environment and take actions based on their neural activations. The creatures evolve over generations, adapting to their environment through mutation and breeding.
Higher level overview can be found [here](Overview.md)
## Features

- **Dynamic Environment**: The environment contains a grid where creatures interact, move, and evolve.
- **Neural Network**: Creatures have sensor, internal, and action neurons enabling them to perceive and respond to their environment.
- **Simulation Control**: A GUI interface to start, stop, and control the simulation.
- **Evolution**: Creatures evolve over generations with customizable parameters for mutation rates, population size, and more.
- **Visualization**: Real-time visualization of the simulation showing creature positions and colors representing their genomes.

## Installation

To install and run this project, follow these steps:
### Linux
1. **Build the project using CMake**:
    ```bash
    mkdir build
    cd build
    cmake ../src
    make
    ```
    The CMake configuration will automatically download and build all required dependencies.
    ### Windows
    Program can be build in VisualStudio as Cmake project. 

## Usage

### Running the Application

1. **Execute the Application**:
    Execute the compiled binary to start the application. You should see the main window of the simulation.

### Configuring the Simulation

1. **Open the Configuration Dialog**:
    Click on the `Configure Simulation` button in the main window to open the configuration dialog.

2. **Set Parameters**:
    In the configuration dialog, you can set the following parameters:
    - **Environment Size**: Size of the environment grid.
    - **Environment Type**: Type of the environment (e.g., square, west border, south border, dense).
    - **Kill Zone Size**: Size of the zone where creatures will be killed.
    - **Number of Creatures**: Initial number of creatures in the environment.
    - **Number of Genes**: Number of genes in each creature's genome.
    - **Max Internal Neurons**: Maximum number of internal neurons for each creature.
    - **Mutation Rate**: Rate at which mutations occur in the genome.
    - **Active Sensor Neurons**: List of active sensor neurons.
    - **Active Action Neurons**: List of active action neurons.
    - **Number of Generations**: Total number of generations to simulate.
    - **Number of Steps**: Number of steps each generation lasts.

3. **Start the Simulation**:
    Click the `OK` button to start the simulation with the chosen configuration.

### Controlling the Simulation

1. **Start/Stop**:
    Use the `Start` and `Stop` buttons to control the simulation.

2. **Reset**:
    Use the `Reset` button to reset the simulation to the initial state.

3. **Observing the Simulation**:
    The main window displays the simulation grid. Each creature is represented by a circle with a color corresponding to its genome. The creatures will move, interact, and evolve in real-time.

### Neuron Types

#### Sensor Neurons

- **RndNeuron**: Returns a random number.
- **BDyNeuron**: Returns the distance from the north/south border.
- **BDxNeuron**: Returns the distance from the east/west border.
- **BDNeuron**: Returns the nearest border distance.
- **LxNeuron**: Returns the nearest border distance.
- **LyNeuron**: Returns the y location.
- **DensNeuron**: Returns the population density in a radius of 2.

#### Action Neurons

- **MFRNeuron**: Moves forward or backward based on activation.
- **MrnNeuron**: Moves in a random direction.
- **MRLNeuron**: Moves right or left based on activation.
- **MxNeuron**: Moves along the x-axis.
- **MyNeuron**: Moves along the y-axis.
- **KillNeuron**: Kills the creature in front.

### Simulation Logic

#### Creature Behavior

1. **Movement**:
    - Creatures move based on the activations of their action neurons.
    - Movement directions are determined by the internal state and the sensor neurons' input.

2. **Interactions**:
    - Creatures can kill other creatures based on certain neuron activations.
    - The environment and other creatures influence the survival and actions of each creature.

3. **Evolution**:
    - After a set number of steps, a new generation is created.
    - Creatures breed and mutate, producing offspring with mixed and mutated genomes.
    - Evolutionary pressures are applied, favoring certain traits over others.

#### Environment Management

1. **Habitat**:
    - The environment is represented by a grid where creatures can move and interact.
    - The habitat is updated every step based on creature actions.

2. **Generation Cycle**:
    - At the end of each generation, the environment is updated with new creatures.
    - The simulation runs for a set number of generations, evolving the population over time.

### Environment Types

The environment type determines the specific conditions and obstacles that creatures will face. Here are the concrete environment types available in the simulation:

1. **Square Environment**:
    - At the end of each generation all the creature in square area in the center are killed

2. **West Border Environment**:
    - Creatures near the west (left) border are at higher risk.
    - At the end of each generation all the creature near west (left) border are killed

3. **South Border Environment**:
    - Similar to the west border environment but with a kill zone along the north (top) edge.

4. **Dense Environment**:
    - High population density areas are more dangerous.
    - Creatures in areas with high density are more likely to be killed, simulating resource competition and overcrowding effects.

