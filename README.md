# 3x3 Rubik's Cube Solver
## Ivan Alekseevich Shtarev, Danil Andreevich Plotnikov, Group 5151003/30002
### Peter the Great St. Petersburg Polytechnic University. Institute of Computer Science and Cybersecurity. Higher School of Cybersecurity.

## Description

This project simulates and solves a 3x3 Rubik's Cube. The program is written in C and uses several external libraries for the implementation and visualization of the solving algorithm. All required libraries are included in the project and linked statically.

## Project Structure

- `src/` - source files of the program
- `include/` - header files
- `lib_macos/` - libraries for building on macOS
- `lib_linux/` - libraries for building on Linux
- `lib_win/` - libraries for building on Windows

## Requirements

- GCC (GNU Compiler Collection)
- MinGW (for building on Windows, includes `mingw32-make`)

## Build Instructions

To build the project on macOS and Linux, use the following command: `make`. For Windows, use the same command or an equivalent alternative.

## Running the Program

After a successful build, run the resulting executable file:

```sh
./rubik_solver
```

## Usage Instructions

### Controls

- **I** — resets the cube to its initial (solved) state.
- **R** — randomizes the cube by performing a series of random rotations.
- **Colored buttons next to I and R** — rotate the cube's faces:
  - Left mouse button — clockwise rotation.
  - Right mouse button — counterclockwise rotation.
- **O** — opens a file with solving steps:
  - Displays a system dialog for file selection.
  - File format: each line represents an action. Notation: F (Front), B (Back), U (Up), D (Down), L (Left), R (Right), number of rotations (optional), `'` for counterclockwise rotation (optional).
- **N** — performs the next step from the file with solving steps:
  - Displays the instruction for the step.
  - If no file is open or there are no more steps to execute, displays a message.
- **C** — opens a cube input window for solving:
  - Switches the context, making the main window inactive.
- **S** — solves the cube and offers to save the solution steps to a file:
  - Loads the step file to be executed.
  - After solving, steps can be executed sequentially by pressing the N button.

## Cube Input Window

### Description

- **Cyan squares** — squares with undefined colors.
- **Magenta square** — the square awaiting color input from the user.
- **Colored buttons in the bottom right corner** — used to select the color of the current square.
- After all square colors are set, the input window automatically closes, and the entered cube state is transferred to the main window.

### Loading a Cube from a File

- The **F** button in the bottom left corner of the cube input window — opens a system dialog for file selection.
  - File format: six lines, each representing one face of the cube in the following order: blue, orange, white, red, yellow, green.
  - Both uppercase and lowercase letters are accepted.
- When loading from a file, all manually entered squares are ignored, and the cube's state from the file is displayed in the main window.

## License

This project is distributed under the MIT License. Refer to the `LICENSE` file for more details.
