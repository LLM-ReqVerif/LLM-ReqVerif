/*
 * Verification code for euler321_I2B_12B using ESBMC
 */

#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include "euler321_I2B_12B.h"

// Constants for verification
#define MAX_LOOPS 10
#define PI 3.14159265358979323846
#define EPSILON 1e-6

// Non-deterministic inputs
double nondet_double(void);
_Bool nondet_bool(void);

// Previous state storage for verification
double prev_Vi[3];
double prev_Vb[3];
double prev_theta;

// Helper functions for matrix operations
double calculate_determinant(const double matrix[9]) {
    return matrix[0] * (matrix[4] * matrix[8] - matrix[5] * matrix[7]) -
           matrix[1] * (matrix[3] * matrix[8] - matrix[5] * matrix[6]) +
           matrix[2] * (matrix[3] * matrix[7] - matrix[4] * matrix[6]);
}

double calculate_dot_product(const double v1[3], const double v2[3]) {
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

double calculate_vector_magnitude(const double v[3]) {
    return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

int main(void) {
    // Initialize model
    euler321_I2B_12B_initialize();
    
    // Loop counter
    int i = 0;
    
    while(i < MAX_LOOPS && nondet_bool()) {
        i++;
        
        // Set non-deterministic inputs
        rtU.phi = nondet_double();
        rtU.theta = nondet_double();
        rtU.psi = nondet_double();
        for(int j = 0; j < 3; j++) {
            rtU.Vi[j] = nondet_double();
            prev_Vi[j] = rtU.Vi[j];
        }
        prev_theta = rtU.theta;
        
        // Run one step
        euler321_I2B_12B_step();
        
        // Store output vector
        for(int j = 0; j < 3; j++) {
            prev_Vb[j] = rtY.Vb[j];
        }

        // Verify properties based on requirements
        
        #ifdef VERIFY_PROPERTY_1
        // Verify DCM321 matrix multiplication order
        __ESBMC_assert(fabs(rtY.DCM321[0] - cos(rtU.theta)*cos(rtU.psi)) < EPSILON,
                      "Property 1: DCM321 matrix multiplication order incorrect");
        #endif
        
        #ifdef VERIFY_PROPERTY_2
        // Verify vector transformation
        double transformed_vector[3] = {0};
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                transformed_vector[i] += rtY.DCM321[i*3 + j] * rtU.Vi[j];
            }
        }
        for(int i = 0; i < 3; i++) {
            __ESBMC_assert(fabs(rtY.Vb[i] - transformed_vector[i]) < EPSILON,
                          "Property 2: Vector transformation incorrect");
        }
        #endif
        
        #ifdef VERIFY_PROPERTY_3
        // Verify magnitude preservation
        double input_mag = calculate_vector_magnitude(rtU.Vi);
        double output_mag = calculate_vector_magnitude(rtY.Vb);
        __ESBMC_assert(fabs(input_mag - output_mag) < EPSILON,
                      "Property 3: Vector magnitude not preserved");
        #endif
        
        #ifdef VERIFY_PROPERTY_4
        // Verify matrix invertibility except at singularity
        if(fabs(fabs(rtU.theta) - PI/2) > EPSILON) {
            double det = calculate_determinant(rtY.DCM321);
            __ESBMC_assert(fabs(det - 1.0) < EPSILON,
                          "Property 4: Matrix not invertible");
        }
        #endif
        
        #ifdef VERIFY_PROPERTY_5
        // Verify unique mapping for different theta
        if(i > 1 && fabs(prev_theta - rtU.theta) > EPSILON) {
            _Bool different_output = false;
            for(int j = 0; j < 3; j++) {
                if(fabs(prev_Vb[j] - rtY.Vb[j]) > EPSILON) {
                    different_output = true;
                    break;
                }
            }
            __ESBMC_assert(different_output,
                          "Property 5: Non-unique mapping for different theta");
        }
        #endif
        
        #ifdef VERIFY_PROPERTY_6
        // Verify orthogonality of rows and columns
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                double row_i[3] = {rtY.DCM321[i*3], rtY.DCM321[i*3+1], rtY.DCM321[i*3+2]};
                double row_j[3] = {rtY.DCM321[j*3], rtY.DCM321[j*3+1], rtY.DCM321[j*3+2]};
                double dot = calculate_dot_product(row_i, row_j);
                if(i == j) {
                    __ESBMC_assert(fabs(dot - 1.0) < EPSILON,
                                 "Property 6: Row not normalized");
                } else {
                    __ESBMC_assert(fabs(dot) < EPSILON,
                                 "Property 6: Rows not orthogonal");
                }
            }
        }
        #endif
        
        #ifdef VERIFY_PROPERTY_7
        // Verify DCM321 * DCM321^T = I
        double identity[9] = {1,0,0, 0,1,0, 0,0,1};
        double product[9] = {0};
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                for(int k = 0; k < 3; k++) {
                    product[i*3+j] += rtY.DCM321[i*3+k] * rtY.DCM321[j*3+k];
                }
                __ESBMC_assert(fabs(product[i*3+j] - identity[i*3+j]) < EPSILON,
                              "Property 7: DCM321 * DCM321^T != I");
            }
        }
        #endif
        
        #ifdef VERIFY_PROPERTY_8
        // Verify determinant = 1
        double det = calculate_determinant(rtY.DCM321);
        __ESBMC_assert(fabs(det - 1.0) < EPSILON,
                      "Property 8: Determinant != 1");
        #endif
    }
    
    return 0;
}