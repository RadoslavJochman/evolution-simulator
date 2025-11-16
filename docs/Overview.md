
## Project Overview

### Introduction

This project implements a simulation environment where creatures evolve and interact within a defined habitat. The core elements of the simulation include creatures with genetic information (genome), a configurable environment, and neural networks that control creature behavior.

### Classes and Interactions

#### `Creature`

The `Creature` class represents individual entities within the simulation. Each creature has a position, genome, and various types of neurons (sensor and action) that form its neural network (brain). Key functionalities include movement, genome manipulation, neural network construction, and interaction with the environment.

#### `Environment`

The `Environment` class manages the habitat where creatures reside. It tracks creature positions, handles creature movements, and manages the lifecycle of creatures including breeding  and population control.

#### Neurons (`SensorNeuron`, `InternalNeuron`, `ActionNeuron`)

These classes define the neural network structure within each `Creature`. `SensorNeuron` classes gather environmental data, `InternalNeuron` processes this data (weighted sum), and `ActionNeuron` classes execute behaviors based on the observed information.

#### Graphics and User Interface (`GridWidget`, `DialogWindow`, `MainWindow`)

These classes provide a visual interface for observing the simulation. `GridWidget` displays the creatures and their interactions, `DialogWindow` allows configuration of simulation parameters, and `MainWindow` orchestrates the simulation lifecycle.

### Key Concepts

-   **Genome**: Represented as hexadecimal strings, genomes dictate creature behaviors and attributes.
-   **Neural Network**: Composed of sensor neurons that perceive the environment, internal neurons that process data, and action neurons that execute behaviors.
-   **Simulation Lifecycle**: Managed by the `Environment` class, including creature movement, breeding, and environmental changes.

### Extending the Project

To extend the project:

-   **Add new neuron types**: Define new sensor or action neuron classes inheriting from `SensorNeuron` or `ActionNeuron`.
-   **Modify creature behaviors**: Adjust neural network connections or genome structure in the `Creature` class.
-   **Add new selection criteria**: Create new functions in `Environment` that decides after each generation which creatures will be killed.
-   **Enhance visual representation**: Update `GridWidget` to visualize additional creature attributes or environmental features.
