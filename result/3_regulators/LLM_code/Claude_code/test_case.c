#include <stdio.h>
#include <math.h>
#include "regs_12B.h"

#define SAMPLE_RATE 100

void print_inputs() {
    printf("Current Inputs:\n");
    printf("lcv_cmd_fcs_dps: %f\n", rtU.lcv_cmd_fcs_dps);
    printf("lcv_fps_dps: %f\n", rtU.lcv_fps_dps);
    printf("vtas_adc_kts: %f\n", rtU.vtas_adc_kts);
}

void print_outputs() {
    printf("Current Outputs:\n");
    printf("lcvdt_cmd_fcs_dps2: %f\n", rtY.lcvdt_cmd_fcs_dps2);
}

int main() {
    double prev_lcvdt = 0.0;
    
    // Initialize model
    regs_12B_initialize();
    
    // Set up the input conditions that ESBMC found problematic
    rtU.lcv_cmd_fcs_dps = 0.0;  // We'll use 0 as our determinate value
    rtU.lcv_fps_dps = -1.2214e+35;  // The problematic value from ESBMC
    rtU.vtas_adc_kts = 1028.0;
    
    // Set all other inputs to 0 as per ESBMC counterexample
    rtU.mcv_cmd_fcs_dps = 0.0;
    rtU.mcv_fcs_dps = 0.0;
    rtU.ncv_cmd_fcs_dps = 0.0;
    rtU.beta_adc_deg = 0.0;
    rtU.beta_dot = 0.0;
    rtU.ncv_fcs_dps = 0.0;
    rtU.xcv_cmd_fcs_fps = 0.0;
    rtU.dcv_fcs_fps = 0.0;
    rtU.hcv_cmd_fcs_fps = 0.0;
    rtU.zcv_fcs_fps = 0.0;

    printf("Starting test case for roll rate violation...\n\n");
    
    // Print initial state
    printf("Initial state:\n");
    print_inputs();
    printf("\n");

    // Run one step of the model
    regs_12B_step();
    
    // Print outputs
    print_outputs();
    printf("\n");

    // Calculate roll rate
    double roll_rate = (rtY.lcvdt_cmd_fcs_dps2 - prev_lcvdt) * SAMPLE_RATE;
    
    printf("Roll rate: %f degrees/s^2\n", roll_rate);
    printf("Absolute roll rate: %f degrees/s^2\n", fabs(roll_rate));
    
    if (fabs(roll_rate) > 50.0) {
        printf("\nTEST FAILED: Roll rate exceeds limit of 50 degrees/s^2\n");
        printf("Roll rate violation: %f degrees/s^2\n", fabs(roll_rate));
        return 1;
    } else {
        printf("\nTEST PASSED: Roll rate within limits\n");
        return 0;
    }
}