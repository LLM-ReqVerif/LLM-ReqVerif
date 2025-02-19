#include <stdio.h>
#include <math.h>
#include "NLGuidance_12B.h"

// External variables declaration
extern ExtU rtU;
extern ExtY rtY;

void print_vectors(const char* prefix, double v1, double v2, double v3) {
    printf("%s: [%.6e, %.6e, %.6e]\n", prefix, v1, v2, v3);
}

int main(void) {
    // Initialize the model
    NLGuidance_12B_initialize();
    
    // Set up the input values that trigger the failure (from ESBMC counterexample)
    rtU.Xtarg[0] = 0.0;  // From State 1
    rtU.Xv[0] = -4.439375e+9;  // From State 2
    rtU.Vv[0] = -1.370168e-308;  // From State 3
    rtU.Vt[0] = 0.0;  // From State 4
    
    rtU.Xtarg[1] = 3.652324e-306;  // From State 5
    rtU.Xv[1] = -1.343041e-306;  // From State 6
    rtU.Vv[1] = -7.589484e-309;  // From State 7
    rtU.Vt[1] = 0.0;  // From State 8
    
    rtU.Xtarg[2] = 0.0;  // From State 9
    rtU.Xv[2] = 0.0;  // From State 10
    rtU.Vv[2] = 0.0;  // From State 11
    rtU.Vt[2] = 0.0;  // From State 12
    
    rtU.r = 0.0;  // From State 13
    
    printf("Initial state:\n");
    print_vectors("Target position (Xtarg)", rtU.Xtarg[0], rtU.Xtarg[1], rtU.Xtarg[2]);
    print_vectors("Vehicle position (Xv)", rtU.Xv[0], rtU.Xv[1], rtU.Xv[2]);
    print_vectors("Vehicle velocity (Vv)", rtU.Vv[0], rtU.Vv[1], rtU.Vv[2]);
    printf("Standoff radius (r): %.6e\n\n", rtU.r);
    
    // Calculate relative position vector (Xr)
    double Xr[3];
    for (int i = 0; i < 3; i++) {
        Xr[i] = rtU.Xtarg[i] - rtU.Xv[i];
    }
    
    // Calculate cross product z-component
    double cross_z = Xr[0]*rtU.Vv[1] - Xr[1]*rtU.Vv[0];
    
    printf("Verification results:\n");
    print_vectors("Relative position (Xr)", Xr[0], Xr[1], Xr[2]);
    printf("Cross product z-component: %.6e\n", cross_z);
    printf("Port-side maintenance property: %s\n", 
           (cross_z > 0.0) ? "PASSED" : "FAILED");
    
    // Step the model
    NLGuidance_12B_step();
    
    printf("\nModel output:\n");
    print_vectors("Output position (yout)", rtY.yout[0], rtY.yout[1], rtY.yout[2]);
    
    return 0;
}