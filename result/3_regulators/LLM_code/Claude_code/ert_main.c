#include <stddef.h>
#include <stdio.h>
#include "regs_12B.h"
#include <math.h>
#include <assert.h>

// Non-deterministic inputs
_Bool nondet_bool();
double nondet_double();
int nondet_int();

// Constants
#define SAMPLE_RATE 100
#define CYCLE_LIMIT 100
#define MAX_CYCLES 1000

// Global variables for tracking previous values
double prev_lcvdt = 0.0;
double prev_mcvdt = 0.0;
double prev_ncvdt = 0.0;
double prev_xcvdt = 0.0;
double prev_hcvdt = 0.0;

// Counters for consecutive violations
int roll_accel_count = 0;
int pitch_accel_count = 0;
int yaw_accel_count = 0;
int axial_accel_count = 0;
int height_accel_count = 0;

void check_requirements(void) {
    #ifdef VERIFY_PROPERTY_1
    // Roll Acceleration Limit
    if (fabs(rtY.lcvdt_cmd_fcs_dps2) > 50.0) {
        roll_accel_count++;
    } else {
        roll_accel_count = 0;
    }
    //__ESBMC_assert(roll_accel_count <= CYCLE_LIMIT, "Roll acceleration limit violated for too long");
    assert(roll_accel_count <= CYCLE_LIMIT);
    #endif

    #ifdef VERIFY_PROPERTY_2
    // Pitch Acceleration Limit
    if (fabs(rtY.mcvdt_cmd_fcs_dps2) > 50.0) {
        pitch_accel_count++;
    } else {
        pitch_accel_count = 0;
    }
    //__ESBMC_assert(pitch_accel_count <= CYCLE_LIMIT, "Pitch acceleration limit violated for too long");
    assert(pitch_accel_count <= CYCLE_LIMIT);
    #endif

    #ifdef VERIFY_PROPERTY_3
    // Yaw Acceleration Limit
    if (fabs(rtY.ncvdt_cmd_fcs_dps2) > 50.0) {
        yaw_accel_count++;
    } else {
        yaw_accel_count = 0;
    }
    __ESBMC_assert(yaw_accel_count <= CYCLE_LIMIT, "Yaw acceleration limit violated for too long");
    #endif

    #ifdef VERIFY_PROPERTY_4
    // Axial Acceleration Limit
    if (fabs(rtY.xcvdt_cmd_fcs_fps2) > 32.0) {
        axial_accel_count++;
    } else {
        axial_accel_count = 0;
    }
    __ESBMC_assert(axial_accel_count <= CYCLE_LIMIT, "Axial acceleration limit violated for too long");
    #endif

    #ifdef VERIFY_PROPERTY_5
    // Height Acceleration Limit
    if (fabs(rtY.hcvdt_cmd_fcs_fps2) > 32.0) {
        height_accel_count++;
    } else {
        height_accel_count = 0;
    }
    __ESBMC_assert(height_accel_count <= CYCLE_LIMIT, "Height acceleration limit violated for too long");
    #endif

    #ifdef VERIFY_PROPERTY_6
    // Roll Rate of Change Limit
    
    double roll_rate = (rtY.lcvdt_cmd_fcs_dps2 - prev_lcvdt) * SAMPLE_RATE;
    __ESBMC_assert(fabs(roll_rate) <= 50.0, "Roll rate of change limit violated");
    prev_lcvdt = rtY.lcvdt_cmd_fcs_dps2;
    #endif

    #ifdef VERIFY_PROPERTY_7
    // Pitch Rate of Change Limit
    double pitch_rate = (rtY.mcvdt_cmd_fcs_dps2 - prev_mcvdt) * SAMPLE_RATE;
    __ESBMC_assert(fabs(pitch_rate) <= 50.0, "Pitch rate of change limit violated");
    prev_mcvdt = rtY.mcvdt_cmd_fcs_dps2;
    #endif

    #ifdef VERIFY_PROPERTY_8
    // Yaw Rate of Change Limit
    double yaw_rate = (rtY.ncvdt_cmd_fcs_dps2 - prev_ncvdt) * SAMPLE_RATE;
    __ESBMC_assert(fabs(yaw_rate) <= 50.0, "Yaw rate of change limit violated");
    prev_ncvdt = rtY.ncvdt_cmd_fcs_dps2;
    #endif

    #ifdef VERIFY_PROPERTY_9
    // Axial Rate of Change Limit
    double axial_rate = (rtY.xcvdt_cmd_fcs_fps2 - prev_xcvdt) * SAMPLE_RATE;
    __ESBMC_assert(fabs(axial_rate) <= 32.0, "Axial rate of change limit violated");
    prev_xcvdt = rtY.xcvdt_cmd_fcs_fps2;
    #endif

    #ifdef VERIFY_PROPERTY_10
    // Height Rate of Change Limit
    double height_rate = (rtY.hcvdt_cmd_fcs_fps2 - prev_hcvdt) * SAMPLE_RATE;
    __ESBMC_assert(fabs(height_rate) <= 32.0, "Height rate of change limit violated");
    prev_hcvdt = rtY.hcvdt_cmd_fcs_fps2;
    #endif
}

void set_nondet_inputs(void) {
    // Set non-deterministic inputs for all channels
    rtU.lcv_cmd_fcs_dps = nondet_double();
    rtU.lcv_fps_dps = nondet_double();
    rtU.mcv_cmd_fcs_dps = nondet_double();
    rtU.mcv_fcs_dps = nondet_double();
    rtU.ncv_cmd_fcs_dps = nondet_double();
    rtU.beta_adc_deg = nondet_double();
    rtU.beta_dot = nondet_double();
    rtU.vtas_adc_kts = nondet_double();
    rtU.ncv_fcs_dps = nondet_double();
    rtU.xcv_cmd_fcs_fps = nondet_double();
    rtU.dcv_fcs_fps = nondet_double();
    rtU.hcv_cmd_fcs_fps = nondet_double();
    rtU.zcv_fcs_fps = nondet_double();
}

int main(int argc, const char *argv[]) {
    (void)(argc);
    (void)(argv);

    // Initialize model
    regs_12B_initialize();

    // Main verification loop
    int cycle_count = 0;
    
    while( cycle_count < MAX_CYCLES) {
        set_nondet_inputs();
        
        // Run one step of the model
        regs_12B_step();
        
        // Check all requirements
        check_requirements();
        
        cycle_count++;
    }

    return 0;
}