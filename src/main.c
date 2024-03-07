#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Function to calculate the sequence length of a given number
int calculate_sequence_length(long long number, int *cache, int cache_size) {
    int length = 1;

    while (number != 1) {
        // Use cached value if available
        if (number < cache_size && cache[number]) {
            length += cache[number] - 1;
            break;
        }
        // Collatz conjecture operation
        number = (number % 2) ? 3 * number + 1 : number >> 1;
        ++length;
    }

    return length;
}

int main(int argc, char *argv[]) {
    // Check for correct number of arguments
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <base_number> <limit> <num_threads> <cache_size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Parse command line arguments
    long long base_number = atoll(argv[1]);
    long long limit = atoll(argv[2]);
    int num_threads = atoi(argv[3]);
    int cache_size = atoi(argv[4]);

    // Allocate memory for cache, aligned for better performance
    int *cache = aligned_alloc(64, cache_size * sizeof(int));
    if (!cache) {
        fprintf(stderr, "Failed to allocate memory for cache.\n");
        return EXIT_FAILURE;
    }

    // Initialize cache
    #pragma omp parallel for num_threads(num_threads) schedule(static)
    for (int i = 0; i < cache_size; ++i) {
        cache[i] = 0;
    }
    cache[1] = 1;

    int longest_sequence_length = 0;
    long long longest_number = 0;
    double start_time = omp_get_wtime();

    // Find the number with the longest Collatz sequence
    #pragma omp parallel num_threads(num_threads)
    {
        int local_longest = 0;
        long long local_longest_num = 0;

        #pragma omp for schedule(dynamic, 64)
        for (long long i = base_number; i <= limit; ++i) {
            int length = calculate_sequence_length(i, cache, cache_size);
            if (length > local_longest) {
                local_longest = length;
                local_longest_num = i;
            }

            // Cache the length if within cache size
            if (i < cache_size) {
                cache[i] = length;
            }
        }

        // Update global maximum in a critical section
        #pragma omp critical
        {
            if (local_longest > longest_sequence_length) {
                longest_sequence_length = local_longest;
                longest_number = local_longest_num;
            }
        }
    }

    free(cache);
    double end_time = omp_get_wtime();

    // Print results
    printf("Longest seq: %d (Number: %lld)\n", longest_sequence_length, longest_number);
    printf("Execution time: %.2f seconds\n", end_time - start_time);

    return EXIT_SUCCESS;
}
