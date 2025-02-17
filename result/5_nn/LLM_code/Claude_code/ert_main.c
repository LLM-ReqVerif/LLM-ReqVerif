#include <stddef.h>
#include <stdio.h>
#include "nn_12B.h"
#include <math.h>

// Verification control macros
//#define VERIFY_PROPERTY_1
//#define VERIFY_PROPERTY_2
//#define VERIFY_PROPERTY_3
//#define VERIFY_PROPERTY_4

// Constants for verification
#define MAX_LOOP_COUNT 100
#define EPSILON 0.01

// Truth data structure (simplified for example)
double truth_data[200][3];

// Non-deterministic input generators
double nondet_double(void);
_Bool nondet_bool(void);

// Helper function for Requirement 4
int find_truth_idx(double x, double y) {
    for(int i = 0; i < 200; i++) {
        if(fabs(truth_data[i][0] - x) < EPSILON && 
           fabs(truth_data[i][1] - y) < EPSILON) {
            return i;
        }
    }
    return -1;
}

void rt_OneStep(void) {
    nn_12B_step();
}

int main(int argc, const char *argv[]) {
    (void)(argc);
    (void)(argv);

    // Initialize model
    nn_12B_initialize();
    
    // Variables for derivative calculations
    double prev_x = 0.0;
    double prev_y = 0.0;
    double prev_z = 0.0;
    _Bool first_iteration = 1;
    
    int loop_count = 0;
    while(loop_count < MAX_LOOP_COUNT && nondet_bool()) {
        // Set non-deterministic inputs
        rtU.x = nondet_double();
        rtU.y = nondet_double();
        
        // Execute one step
        rt_OneStep();
        
        // Requirement 1: Maximum Output Value
        #ifdef VERIFY_PROPERTY_1
        __ESBMC_assert(rtY.z <= 1.1, "Requirement 1: Output exceeds maximum value");
        #endif
        
        // Requirement 2: Minimum Output Value
        #ifdef VERIFY_PROPERTY_2
        __ESBMC_assert(rtY.z >= -0.2, "Requirement 2: Output below minimum value");
        #endif
        
        // Requirement 3: Spatial Derivatives Bounds
        #ifdef VERIFY_PROPERTY_3
        if (!first_iteration) {
            double dx = rtU.x - prev_x;
            double dy = rtU.y - prev_y;
            
            if (dx != 0) {
                double dz_dx = (rtY.z - prev_z) / dx;
                __ESBMC_assert(dz_dx >= -35.0 && dz_dx <= 10.0, 
                              "Requirement 3: x-derivative out of bounds");
            }
            
            if (dy != 0) {
                double dz_dy = (rtY.z - prev_z) / dy;
                __ESBMC_assert(dz_dy >= -35.0 && dz_dy <= 10.0, 
                              "Requirement 3: y-derivative out of bounds");
            }
        }
        #endif
        
        // Requirement 4: Truth Data Matching
        #ifdef VERIFY_PROPERTY_4
        int truth_idx = find_truth_idx(rtU.x, rtU.y);
        if (truth_idx != -1) {
            __ESBMC_assert(fabs(rtY.z - truth_data[truth_idx][2]) <= 0.01,
                          "Requirement 4: Output doesn't match truth data");
        }
        #endif
        
        // Update previous values for next iteration
        prev_x = rtU.x;
        prev_y = rtU.y;
        prev_z = rtY.z;
        first_iteration = 0;
        
        loop_count++;
    }
    
    return 0;
}