#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to allocate memory for a 2D array
int** alloc_2d_array(int n) {
    int** arr = (int**)malloc(n * sizeof(int*)); 
    for (int i = 0; i < n; i++) {
        arr[i] = (int*)malloc(n * sizeof(int));
    }
    return arr;
}
// Function to deallocate memory for a 2D array
void dealloc_2d_array(int** arr, int n) {
    for (int i = 0; i < n; i++)
        free(arr[i]);
    free(arr);
}
int** create_empty_matrix(int n) {
    int** matrix = (int**)malloc(n * sizeof(int*)); 
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)calloc(n, sizeof(int));
    }
    return matrix;
}

// Function to fill a 2D array with random values
void fill_random(int** arr, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            arr[i][j] = rand() % 1001; // Generate random integer between 0 and 1000
}




// Function to perform matrix transpose in-place
void matrix_transpose_inplace_ij(int** A, int n) {
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            int temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
}
void matrix_transpose_inplace_ji(int** A, int n) {
    for (int j = 0; j < n; j++)
        for (int i = j + 1; i < n; i++) {
            int temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
}


void matrix_transposeij(int** A, int** B, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            B[i][j] = A[j][i];
}
void matrix_transposeji(int** A, int** B, int n) {
    for (int j = 0; j < n; j++)
        for (int i = 0; i < n; i++)
            B[i][j] = A[j][i];
}

int main() {
    srand(time(NULL)); // Seed random number generator

    // Open file for writing
    FILE *file = fopen("transpose_times.txt-10", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Write header to file
    // fprintf(file, "Matrix Multiplication Times:\n");

    // Varying matrix sizes
    int sizes[] = {100, 200, 300, 400, 500};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    // Measure time for matrix multiplication
    // printf("Matrix Multiplication Times:\n");
    for (int n = 1; n <= 100; n++) {
        printf("%d\n",n);
        int** A = alloc_2d_array(n);

        fill_random(A, n);

        //////////////////////// 1
        int** B= create_empty_matrix(n);
        clock_t start = clock();
        matrix_transposeij(A,B,n);
        clock_t end = clock();
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        fprintf(file, "Configuration: normal, Size %d: %.6f seconds\n", n, time_spent);
        dealloc_2d_array(B, n);
    
        //////////////////////// 1
        start = clock();
        matrix_transpose_inplace_ij(A,n);
        end = clock();
        time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        fprintf(file, "Configuration: inplace, Size %d: %.6f seconds\n", n, time_spent);


        dealloc_2d_array(A, n);
    }
    fclose(file);
    return 0;
}
