# Heat Diffusion Simulation

## Overview
This project simulates heat diffusion in a three-dimensional space with a heat source. It compares explicit and implicit methods to analyze heat propagation in different materials.

## Features
- **Explicit Method:** Implements a straightforward approach to heat diffusion.
- **Implicit Method:** Uses a more stable method for solving heat diffusion equations.

## Results

### Explicit Method
Result of the program with thermal conductivity coefficient a = 0.000019:

![Explicit Method Result](explicit.png)

### Implicit Method
Result of the program with thermal conductivity coefficient a = 0.000216:

![Implicit Method Result](implicit.png)

## Code Structure
- **Explicit Method:**
  - Initializes temperature distribution.
  - Updates temperature using explicit method.
  - Outputs result to file.

- **Implicit Method:**
  - Initializes temperature distribution.
  - Updates temperature using implicit method.
  - Outputs result to file.

## Dependencies
- **C++ Standard Library**: For file handling and mathematical operations.
