#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include "NLGuidance_12B.h"

// Global verification constants
#define MAX_STEPS 10
#define EPSILON 1e-6
#define T 0.02  // Sample period from original code

// Previous state storage
real_T prev_yout[3];

// Nondet inputs declaration
real_T nondet_real(void);
_Bool nondet_bool(void);

// Helper functions
real_T vector_magnitude(const real_T v[3]) {
    return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

real_T dot_product(const real_T v1[3], const real_T v2[3]) {
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

void cross_product(const real_T v1[3], const real_T v2[3], real_T result[3]) {
    result[0] = v1[1]*v2[2] - v1[2]*v2[1];
    result[1] = v1[2]*v2[0] - v1[0]*v2[2];
    result[2] = v1[0]*v2[1] - v1[1]*v2[0];
}

// Verification properties
#ifdef VERIFY_PROPERTY_1
void verify_port_side_maintenance(void) {
    real_T Xr[3];
    // Calculate relative position vector
    for (int i = 0; i < 3; i++) {
        Xr[i] = rtU.Xtarg[i] - rtU.Xv[i];
    }
    // Cross product z-component for port-side verification
    real_T cross_z = Xr[0]*rtU.Vv[1] - Xr[1]*rtU.Vv[0];
    __ESBMC_assert(cross_z > 0, "Port-side maintenance violated");
}
#endif

#ifdef VERIFY_PROPERTY_2
void verify_aim_point_1(void) {
    real_T vec1[3], vec2[3];
    // Calculate vectors from target to aim point and aim point to vehicle
    for (int i = 0; i < 3; i++) {
        vec1[i] = rtY.yout[i] - rtU.Xtarg[i];
        vec2[i] = rtU.Xv[i] - rtY.yout[i];
    }
    real_T dot = dot_product(vec1, vec2);
    __ESBMC_assert(fabs(dot) < EPSILON, "Aim point 1 perpendicular alignment violated");
}
#endif

#ifdef VERIFY_PROPERTY_3
void verify_aim_point_2(void) {
    real_T vec1[3], vec2[3];
    for (int i = 0; i < 3; i++) {
        vec1[i] = rtY.yout[i] - rtU.Xtarg[i];
        vec2[i] = rtU.Xv[i] - rtY.yout[i];
    }
    real_T dot = dot_product(vec1, vec2);
    __ESBMC_assert(fabs(dot) < EPSILON, "Aim point 2 perpendicular alignment violated");

}
#endif

#ifdef VERIFY_PROPERTY_4
void verify_ccw_loiter(void) {
    real_T cross_z = (rtY.yout[0] - rtU.Xtarg[0])*(rtU.Xv[1] - rtU.Xtarg[1]) -
                     (rtY.yout[1] - rtU.Xtarg[1])*(rtU.Xv[0] - rtU.Xtarg[0]);
    __ESBMC_assert(cross_z > 0, "CCW loiter rotation violated");
}
#endif

#ifdef VERIFY_PROPERTY_5
void verify_inside_standoff_recovery(void) {
    real_T dist_new = sqrt(pow(rtY.yout[0] - rtU.Xtarg[0], 2) +
                          pow(rtY.yout[1] - rtU.Xtarg[1], 2) +
                          pow(rtY.yout[2] - rtU.Xtarg[2], 2));

    __ESBMC_assert(dist_new >= rtU.r, "Inside standoff recovery violated");
}
#endif

#ifdef VERIFY_PROPERTY_6
void verify_transient_behavior(void) {
    real_T max_change = (vector_magnitude(rtU.Vv) + vector_magnitude(rtU.Vt)) * T;
    real_T actual_change = sqrt(pow(rtY.yout[0] - prev_yout[0], 2) +
                               pow(rtY.yout[1] - prev_yout[1], 2) +
                               pow(rtY.yout[2] - prev_yout[2], 2));

    __ESBMC_assert(actual_change <= max_change, "Transient behavior bounds violated");
}
#endif

#ifdef VERIFY_PROPERTY_7
void verify_in_plane_navigation(void) {
    __ESBMC_assert(fabs(rtY.yout[2] - rtU.Xv[2]) < EPSILON, "In-plane navigation violated");
}
#endif

void initialize_inputs(void) {
    // Initialize all inputs with nondet values
    for (int i = 0; i < 3; i++) {
        rtU.Xtarg[i] = nondet_real();
        rtU.Xv[i] = nondet_real();
        rtU.Vv[i] = nondet_real();
        rtU.Vt[i] = nondet_real();
    }
    rtU.r = nondet_real();
    
    // Save initial output state
    for (int i = 0; i < 3; i++) {
        prev_yout[i] = rtY.yout[i];
    }
}

int main(void) {
    // Initialize model
    NLGuidance_12B_initialize();
    
    // Initialize inputs with nondet values
    initialize_inputs();
    
    int step = 0;
    while (step < MAX_STEPS) {
        // Save previous state
        for (int i = 0; i < 3; i++) {
            prev_yout[i] = rtY.yout[i];
        }
        
        // Step the model
        NLGuidance_12B_step();
        
        // Verify all properties after each step
        #ifdef VERIFY_PROPERTY_1
        verify_port_side_maintenance();
        #endif
        
        #ifdef VERIFY_PROPERTY_2
        verify_aim_point_1();
        #endif
        
        #ifdef VERIFY_PROPERTY_3
        verify_aim_point_2();
        #endif
        
        #ifdef VERIFY_PROPERTY_4
        verify_ccw_loiter();
        #endif
        
        #ifdef VERIFY_PROPERTY_5
        verify_inside_standoff_recovery();
        #endif
        
        #ifdef VERIFY_PROPERTY_6
        verify_transient_behavior();
        #endif
        
        #ifdef VERIFY_PROPERTY_7
        verify_in_plane_navigation();
        #endif
        
        // Update inputs for next iteration
        initialize_inputs();
        
        step++;
    }
    
    return 0;
}