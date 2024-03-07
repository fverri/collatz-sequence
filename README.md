# collatz-sequence

This project introduces an ultra-optimized calculator designed to explore the Collatz Conjecture, using advanced C programming techniques and parallelism with OpenMP to achieve the highest performance.

## Features

- **High-Level Optimization**: Utilizes `-O3` optimization for quicker and more efficient execution.
- **Parallel Processing with OpenMP**: Boosts efficiency on multicore systems by employing multiple execution threads.
- **Caching Mechanism**: Implements caching to save intermediate results, reducing redundant computations.

## Prerequisites

Your environment should include:
- A C compiler that supports OpenMP, such as `gcc` or `clang`.
- Access to a terminal or command line interface.

## Installation and Compilation

1. **Clone the Repository**: Begin by cloning this repository to your local machine with `git`:

   ```bash
   git clone https://github.com/fverri/collatz-sequence.git
   ```

2. **Navigate to the Directory**: Move to the cloned project's directory:

   ```bash
   cd collatz-sequence
   ```

3. **Compile the Program**: You can compile the program using `gcc` or `clang`. Choose the appropriate command based on your compiler:

   **Using gcc**:
   ```bash
   gcc src/main.c -o collatz-sequence -O3 -march=native -fopenmp -flto -lgomp
   ```

   **Using clang**:
   ```bash
   clang src/main.c -o collatz-sequence -O3 -march=native -fopenmp -flto -lomp
   ```

## Usage

After compilation, run the program with the following syntax:

```bash
./collatz-sequence <base_number> <limit> <num_threads> <cache_size>
```

Where:
- `<base_number>`: The starting number for Collatz sequences calculations.
- `<limit>`: The maximum number up to which sequences will be calculated.
- `<num_threads>`: The number of execution threads to use.
- `<cache_size>`: The cache size for storing intermediate results to enhance calculation efficiency.

### Execution Example

To compute Collatz sequences starting from number 1 up to 1,000,000, using 4 threads and a cache size of 1,000,000:

```bash
./collatz-sequence 1 1000000 4 1000000
```

## Contributions

Contributions to this project are encouraged. To contribute:
- Fork the repository.
- Create a new branch for your feature.
- Submit a Pull Request with your changes.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE.md) file for details.
