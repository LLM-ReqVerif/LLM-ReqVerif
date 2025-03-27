#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "euler321_I2B_12B.h"

// Utility function to print a matrix
void print_matrix(const char* label, real_T matrix[9], int rows, int cols) {
    printf("%s:\n", label);
    for (int i = 0; i < rows; i++) {
        printf("  ");
        for (int j = 0; j < cols; j++) {
            printf("%10.6f ", matrix[i * cols + j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Function to compare expected and actual results
int check_result(real_T actual, real_T expected, real_T tolerance) {
    return fabs(actual - expected) <= tolerance;
}

int main() {
    // Initialize values from the counterexample
    // phi_1 = 411775/65536 (approximately 6.2831...)
    // theta_1 = 617663/131072 (approximately 4.7124...)
    // psi_1 = 617663/131072 (approximately 4.7124...)
    
    // Convert fraction to floating-point
    rtU.phi = 411775.0 / 65536.0;
    rtU.theta = 617663.0 / 131072.0;
    rtU.psi = 617663.0 / 131072.0;
    
    printf("Test inputs:\n");
    printf("phi = %f radians\n", rtU.phi);
    printf("theta = %f radians\n", rtU.theta);
    printf("psi = %f radians\n", rtU.psi);
    
    // Initialize a test vector in inertial frame
    rtU.Vi[0] = 1.0;
    rtU.Vi[1] = 0.0;
    rtU.Vi[2] = 0.0;
    
    // Run the function under test
    euler321_I2B_12B_initialize();
    euler321_I2B_12B_step();
    
    // Print the DCM output
    print_matrix("DCM321", rtY.DCM321, 3, 3);
    
    // Print the transformed vector
    printf("Transformed vector Vb = [%f, %f, %f]\n\n", 
           rtY.Vb[0], rtY.Vb[1], rtY.Vb[2]);
    
    // Check if DCM321_1 matches the counterexample value of -1/4
    printf("Checking against counterexample value:\n");
    printf("Expected DCM321[0] = -0.25 (from counterexample)\n");
    printf("Actual DCM321[0] = %f\n", rtY.DCM321[0]);
    
    // Verify against the specification
    // For Euler 321, the DCM should be orthogonal (transpose = inverse)
    // Let's check if the product of DCM with its transpose is identity
    real_T transpose[9];
    real_T product[9] = {0};
    
    // Compute transpose
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            transpose[i * 3 + j] = rtY.DCM321[j * 3 + i];
        }
    }
    
    // Multiply DCM * transpose
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                product[i * 3 + j] += rtY.DCM321[i * 3 + k] * transpose[k * 3 + j];
            }
        }
    }
    
    print_matrix("DCM * DCM^T (should be identity)", product, 3, 3);
    
    // Check determinant = 1
    real_T det = 
        rtY.DCM321[0] * (rtY.DCM321[4] * rtY.DCM321[8] - rtY.DCM321[5] * rtY.DCM321[7]) -
        rtY.DCM321[1] * (rtY.DCM321[3] * rtY.DCM321[8] - rtY.DCM321[5] * rtY.DCM321[6]) +
        rtY.DCM321[2] * (rtY.DCM321[3] * rtY.DCM321[7] - rtY.DCM321[4] * rtY.DCM321[6]);
    
    printf("Determinant of DCM: %f (should be 1.0 for a valid rotation matrix)\n", det);
    
    // Check whether the resulting matrix is a valid rotation matrix
    int valid_rotation = 1;
    real_T tolerance = 1e-6;
    
    // Check if product is identity
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            real_T expected = (i == j) ? 1.0 : 0.0;
            if (!check_result(product[i * 3 + j], expected, tolerance)) {
                valid_rotation = 0;
                printf("Error: DCM * DCM^T[%d,%d] = %f, expected %f\n", 
                       i, j, product[i * 3 + j], expected);
            }
        }
    }
    
    // Check determinant
    if (!check_result(det, 1.0, tolerance)) {
        valid_rotation = 0;
        printf("Error: Determinant = %f, expected 1.0\n", det);
    }
    
    if (valid_rotation) {
        printf("PASS: DCM is a valid rotation matrix\n");
    } else {
        printf("FAIL: DCM is not a valid rotation matrix\n");
    }
    
    return 0;
}
