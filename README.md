# Evolution Simulator

A C++ simulation of neuro-evolution: a population of creatures, each controlled by a small
neural network encoded in its genome, lives on a grid and evolves under selection pressure.
Over successive generations the creatures breed, mutate, and adapt to survive their
environment — and you can watch it happen in real time through a Qt interface.

Inspired by the "evolving creatures with tiny brains" family of simulations (e.g. biosim4),
implemented from scratch in modern C++.

![Simulation screenshot](assets/demo.gif)

> _Replace the image above with a screenshot or, better, a short GIF of the simulation running.
> A visual project is sold by one good animation more than by any paragraph._

<!-- Optional badges — uncomment once the repo is public
![C++](https://img.shields.io/badge/C%2B%2B-23-blue)
![Build](https://img.shields.io/badge/build-CMake%20%2B%20vcpkg-green)
![Qt](https://img.shields.io/badge/GUI-Qt6-41cd52)
![License](https://img.shields.io/badge/license-MIT-lightgrey)
-->

---

## What it does

- **Genome-encoded brains.** Each creature carries a genome of hexadecimal genes. Every gene
  decodes into a wire of the creature's neural network — a connection between a *sensor*,
  *internal*, or *action* neuron, with a weight and an activation threshold.
- **Perceive → think → act.** Sensor neurons read the environment (borders, position, local
  density…), internal neurons combine those signals as weighted sums, and action neurons turn
  the result into movement or interaction.
- **Selection, breeding, mutation.** At the end of each generation the environment culls
  creatures according to a selection rule; survivors breed, their genomes recombine and mutate,
  and the next generation begins.
- **Live visualisation.** Creatures are drawn on the grid, each coloured by its genome, so
  related lineages share a colour and you can literally see structure emerge.

## How a genome becomes a brain

Each 8-digit hex gene is expanded to bits that specify:

| Field | Meaning |
|---|---|
| source type | sensor neuron vs internal neuron |
| source id | which neuron (taken modulo the number of active neurons) |
| end type | internal neuron vs action neuron |
| end id | which neuron |
| weight | strength of the connection |
| threshold | activation threshold of the target action neuron |

Decoding every gene wires up the network; the same genome also determines the creature's RGB
colour, so visually similar creatures are genetically similar.

## Neurons

**Sensor neurons** — `Rnd` (random), `BDx` / `BDy` (distance to the E–W / N–S border),
`BD` (nearest border), `Lx` / `Ly` (x / y position), `Dens` (local population density).

**Action neurons** — `MFR` (move forward/back), `MRL` (move left/right), `Mx` / `My`
(move along an axis), `Mrn` (move randomly), `Kill` (kill the creature ahead).

## Environments (selection rules)

- **Square** — creatures in a central square are culled each generation.
- **West / South border** — creatures near a chosen edge are culled.
- **Dense** — creatures in overcrowded regions are culled, modelling resource competition.

## Configuration

All parameters are set from the GUI's configuration dialog before a run: environment size and
type, kill-zone size, number of creatures, genes per genome, maximum internal neurons, mutation
rate, the active sensor/action neuron sets, and the number of generations and steps per
generation.

## Building

Requires a C++23 compiler, [CMake](https://cmake.org/) ≥ 3.22, and
[vcpkg](https://vcpkg.io/) (used to fetch Qt 6).

**Point CMake at vcpkg** by either setting the `VCPKG_ROOT` environment variable or adding vcpkg
as a submodule at the repo root (`git submodule add https://github.com/microsoft/vcpkg`). The
build picks up whichever it finds.

### Linux / macOS

```bash
cmake -S src -B build
cmake --build build
./build/SimulationOfEvolution
```

vcpkg resolves and builds the Qt dependency automatically on the first configure (this can take
a while the first time).

### Windows

Open the folder in Visual Studio as a CMake project, or use the `CMakePresets.json` — Qt is
supplied through vcpkg the same way.

## Project structure

```
.
├── src/            # sources + CMakeLists.txt + vcpkg.json
│   ├── Main.cpp
│   ├── Creature.{h,cpp}     # genome, brain-building, breeding, mutation
│   ├── Neurons.{h,cpp}      # sensor / internal / action neuron hierarchy
│   ├── Environment.{h,cpp}  # grid, movement, selection, generations
│   ├── QtGraphics.{h,cpp}   # GUI and rendering
│   └── utilities.h
├── docs/           # design overview and specification
├── assets/         # screenshot / GIF
├── README.md
└── LICENSE
```

## Possible extensions

The neuron hierarchy is designed to be extended: add a new sensor or action neuron by deriving
from `SensorNeuron` / `ActionNeuron`, add a new selection rule in `Environment`, or add
per-generation data logging to plot how diversity and population change over time.

## License

MIT — see [LICENSE](LICENSE).

## Author

Radoslav Jochman
