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

// Function to perform matrix multiplication
void matrix_multiply1(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++){
                C[i][j] += A[i][k] * B[k][j];
        }}}
}

void matrix_multiply2(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++){
        for (int k = 0; k < n; k++){
            for (int j = 0; j < n; j++) {
                C[i][j] += A[i][k] * B[k][j];
        }}}
}
void matrix_multiply3(int** A, int** B, int** C, int n) {
    for (int j = 0; j < n; j++){
        for (int k = 0; k < n; k++){
            for (int i = 0; i < n; i++) {
                C[i][j] += A[i][k] * B[k][j];
        }}}
}
void matrix_multiply4(int** A, int** B, int** C, int n) { 
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++){
            for (int k = 0; k < n; k++){
                C[i][j] += A[i][k] * B[k][j];
        }}}
}
void matrix_multiply5(int** A, int** B, int** C, int n) {
    for (int k = 0; k < n; k++){ 
        for (int j = 0; j < n; j++) {
            for (int i = 0; i < n; i++){
                C[i][j] += A[i][k] * B[k][j];
        }}}
}
void matrix_multiply6(int** A, int** B, int** C, int n) {
    for (int k = 0; k < n; k++){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++) {   
                C[i][j] += A[i][k] * B[k][j];
        }}}
}

// Function to perform matrix transpose in-place
void matrix_transpose_inplace(double** A, int n) {
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            double temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
}

// Function to perform matrix transpose using an additional array
void matrix_transpose(double** A, double** B, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            B[i][j] = A[j][i];
}

int main() {
    srand(time(NULL)); // Seed random number generator

    // Open file for writing
    FILE *file = fopen("multiplication_times.txt", "w");
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
    for (int n = 1; n <= 60; n++) {
        printf("%d\n",n);
        int** A = alloc_2d_array(n);
        int** B = alloc_2d_array(n);


        fill_random(A, n);
        fill_random(B, n);

        //////////////////////// 1
        int** C = create_empty_matrix(n);
        clock_t start = clock();
        matrix_multiply1(A, B, C, n);
        clock_t end = clock();
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        fprintf(file, "Configuration: ijk, Size %d: %.6f seconds\n", n, time_spent);
        dealloc_2d_array(C, n);

        /////////////////////2
        C = create_empty_matrix(n);
        start = clock();
        matrix_multiply2(A, B, C, n);
        end = clock();
        time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        fprintf(file, "Configuration: ikj, Size %d: %.6f seconds\n", n, time_spent);
        dealloc_2d_array(C, n);

        /////////////////////3
        C = create_empty_matrix(n);
        start = clock();
        matrix_multiply3(A, B, C, n);
        end = clock();
        time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        fprintf(file, "Configuration: jki, Size %d: %.6f seconds\n", n, time_spent);
        dealloc_2d_array(C, n);

        /////////////////////4
        C = create_empty_matrix(n);
        start = clock();
        matrix_multiply4(A, B, C, n);
        end = clock();
        time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        fprintf(file, "Configuration: jik, Size %d: %.6f seconds\n", n, time_spent);
        dealloc_2d_array(C, n);

        /////////////////////5
        C = create_empty_matrix(n);
        start = clock();
        matrix_multiply5(A, B, C, n);
        end = clock();
        time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        fprintf(file, "Configuration: kji, Size %d: %.6f seconds\n", n, time_spent);
        dealloc_2d_array(C, n);

        /////////////////////6
        C = create_empty_matrix(n);
        start = clock();
        matrix_multiply6(A, B, C, n);
        end = clock();
        time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        fprintf(file, "Configuration: kij, Size %d: %.6f seconds\n", n, time_spent);
        dealloc_2d_array(C, n);






        dealloc_2d_array(A, n);
        dealloc_2d_array(B, n);
    }


    // Measure time for matrix transpose
    // printf("\nMatrix Transpose Times:\n");
    // for (int k = 0; k < num_sizes; k++) {
    //     int n = sizes[k];
    //     double** A = alloc_2d_array(n);
    //     double** B = alloc_2d_array(n);

    //     fill_random(A, n);

    //     clock_t start = clock();
    //     matrix_transpose(A, B, n);
    //     clock_t end = clock();
    //     double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    //     printf("Size %d: %.6f seconds\n", n, time_spent);

    //     dealloc_2d_array(A, n);
    //     dealloc_2d_array(B, n);
    // }
    fclose(file);
    return 0;
}
