/*
 * ESBMC Verification for EB_12B
 * Based on formal specifications from formal_specification.txt
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "EB_12B.h"

// ESBMC assertion macro
#define __ESBMC_assert(cond, msg) \
  if(!(cond)) { \
    printf("Assertion failed: %s\n", msg); \
    __ESBMC_assert(0, "Assertion failure"); \
  }

// Nondet functions for input generation
extern real_T nondet_real();
extern _Bool nondet_bool();

// Helper functions
real_T matrix_determinant_3x3(const real_T matrix[9]) {
    return matrix[0] * (matrix[4] * matrix[8] - matrix[5] * matrix[7]) -
           matrix[1] * (matrix[3] * matrix[8] - matrix[5] * matrix[6]) +
           matrix[2] * (matrix[3] * matrix[7] - matrix[4] * matrix[6]);
}

real_T vector_norm_2(const real_T vector[3]) {
    return sqrt(vector[0]*vector[0] + vector[1]*vector[1] + vector[2]*vector[2]);
}

void identity_matrix_3x3(real_T matrix[9]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix[i*3 + j] = (i == j) ? 1.0 : 0.0;
        }
    }
}

_Bool is_close_to_identity(const real_T matrix[9], real_T tolerance) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            real_T expected = (i == j) ? 1.0 : 0.0;
            if (fabs(matrix[i*3 + j] - expected) > tolerance) {
                return 0; // False
            }
        }
    }
    return 1; // True
}

// Set up test cases
void setup_high_det_case() {
    // Control effectiveness matrix with high determinant
    rtU.B_j[0] = 1.0; rtU.B_j[1] = 0.0; rtU.B_j[2] = 0.0;
    rtU.B_j[3] = 0.0; rtU.B_j[4] = 1.0; rtU.B_j[5] = 0.0;
    rtU.B_j[6] = 0.0; rtU.B_j[7] = 0.0; rtU.B_j[8] = 1.0;
    rtU.B_j[9] = 0.5; rtU.B_j[10] = 0.5; rtU.B_j[11] = 0.0;
    rtU.B_j[12] = 0.0; rtU.B_j[13] = 0.5; rtU.B_j[14] = 0.5;
    
    // Note: up is not directly accessible in rtU based on code analysis
    // Wp and d are constants in rtConstP
}

void setup_low_det_case() {
    // Control effectiveness matrix with low determinant
    rtU.B_j[0] = 1.0; rtU.B_j[1] = 0.0; rtU.B_j[2] = 0.0;
    rtU.B_j[3] = 1.0; rtU.B_j[4] = 1e-7; rtU.B_j[5] = 0.0;
    rtU.B_j[6] = 0.0; rtU.B_j[7] = 0.0; rtU.B_j[8] = 1.0;
    rtU.B_j[9] = 0.5; rtU.B_j[10] = 0.5; rtU.B_j[11] = 0.0;
    rtU.B_j[12] = 0.0; rtU.B_j[13] = 0.5; rtU.B_j[14] = 0.5;
}

// Generate random inputs within constraints
void generate_random_inputs() {
    // Random control effectiveness matrix
    for (int i = 0; i < 15; i++) {
        rtU.B_j[i] = nondet_real();
        // Constrain to reasonable values to avoid overflow
        rtU.B_j[i] = rtU.B_j[i] > 10.0 ? 10.0 : (rtU.B_j[i] < -10.0 ? -10.0 : rtU.B_j[i]);
    }
}

// Calculate control solution cost
real_T calculate_cost(real_T u_vector[5]) {
    real_T cost = 0.0;
    for (int i = 0; i < 5; i++) {
        // Using the identity matrix for Wp (which seems to be the default from rtConstP)
        cost += u_vector[i] * u_vector[i];
    }
    return cost;
}

// Alternative solution generation for cost comparison
void generate_alternative_solution(real_T alt_u[5]) {
    for (int i = 0; i < 5; i++) {
        alt_u[i] = rtY.u[i] + 0.1; // Small variation from optimal solution
    }
}

// Main function with verification
int main() {
    // Initialize model and variables
    EB_12B_initialize();
    
    real_T identity[9];
    identity_matrix_3x3(identity);
    
    int max_iterations = 5;
    
    // Run the model for verification
    for (int i = 0; i < max_iterations; i++) {
        // Either use deterministic test cases or generate random inputs
        if (i == 0) {
            setup_high_det_case();
        } else if (i == 1) {
            setup_low_det_case();
        } else {
            generate_random_inputs();
        }
        
        // Run the model
        EB_12B_step();
        
        // Verify requirements after each step
        
        // Requirement 1: Ridge Regression Accuracy (High Det)
        #ifdef VERIFY_PROPERTY_1
        if (!rtY.ridge_on) {
            real_T tolerance = 1e-12;
            _Bool check_is_identity = is_close_to_identity(rtY.check, tolerance);
            __ESBMC_assert(check_is_identity, 
                          "PROPERTY 1: check matrix should be close to identity for high determinant case");
        }
        #endif
        
        // Requirement 2: Ridge Regression Accuracy (Low Det)
        #ifdef VERIFY_PROPERTY_2
        if (rtY.ridge_on) {
            real_T tolerance = 1e-6;
            _Bool check_is_identity = is_close_to_identity(rtY.check, tolerance);
            __ESBMC_assert(check_is_identity, 
                          "PROPERTY 2: check matrix should be close to identity for low determinant case");
        }
        #endif
        
        // Requirement 3: Control Solution Vector Size
        #ifdef VERIFY_PROPERTY_3
        for (int j = 0; j < 5; j++) {
            _Bool valid_u = !isnan(rtY.u[j]) && !isinf(rtY.u[j]);
            __ESBMC_assert(valid_u, 
                          "PROPERTY 3: control solution vector elements must be valid numbers");
        }
        #endif
        
        // Requirement 4: Error Constraint
        #ifdef VERIFY_PROPERTY_4
        real_T error_norm = vector_norm_2(rtY.Buminusd);
        __ESBMC_assert(error_norm < 0.01, 
                      "PROPERTY 4: error vector norm should be less than 0.01");
        #endif
        
        // Requirement 5: Cost Minimization
        #ifdef VERIFY_PROPERTY_5
        real_T original_cost = rtY.J;
        real_T alt_solution[5];
        generate_alternative_solution(alt_solution);
        real_T alt_cost = calculate_cost(alt_solution);
        __ESBMC_assert(original_cost <= alt_cost, 
                      "PROPERTY 5: original solution cost should be minimal");
        #endif
    }
    
    return 0;
}