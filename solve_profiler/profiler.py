"""
This script compiles and executes a C script multiple times,
capturing and printing the time taken for each execution.

Constants:
    SCRIPT (str): The filename of the C script to be compiled and executed.
    ITER (int): The number of times the compiled executable should be run.

Functions:
    main(): Compiles the C script using gcc, determines the executable name based on the
            operating system, executes the compiled executable multiple times, captures
            and prints the time taken for each execution, and calculates
            and prints the average time taken over all executions.

Usage:
    Run this script directly to compile and execute the specified C script multiple times, 
    capturing and printing the time taken for each execution.
"""

import subprocess
import os


SCRIPT = "algo.c"
ITER = 1000


def main():
    """
    Compiles and executes a C script multiple times.
    Captures and prints the time taken for each execution.
    The function performs the following steps:
    1. Compiles a C script using gcc.
    2. Determines the executable name based on the operating system.
    3. Executes the compiled executable multiple times.
    4. Captures and prints the time taken for each execution.
    5. Calculates and prints the average time taken over all executions.
    """

    subprocess.run(
        ["gcc", SCRIPT, "-o", SCRIPT.split(".", maxsplit=1)[0]],
        check=True,
    )

    executable = (
        SCRIPT.split(".", maxsplit=1)[0] + ".exe"
        if os.name == "nt"
        else "./" + SCRIPT.split(".", maxsplit=1)[0]
    )

    print("Executing algo...")

    results = []
    for i in range(ITER):
        result = subprocess.run(
            [executable], capture_output=True, text=True, check=True
        )
        timetaken = result.stdout

        print(f"Iteration: {i + 1}. Time taken: {timetaken} ms")
        results.append(int(timetaken))
    print(f"Average time taken: {round(sum(results) / len(results), 1)} ms")


if __name__ == "__main__":
    main()
