#include <stddef.h>
#include <stdio.h>
#include "fsm_12B_global.h"

// Nondet inputs
_Bool nondet_bool();
double nondet_double();

// Global variables for state tracking
double prev_UnitDelay_DSTATE;
double prev_UnitDelay1_DSTATE;
_Bool prev_UnitDelay2_DSTATE;

int main(int argc, const char *argv[]) {
    // Initialize model
    fsm_12B_global_initialize();
    
    // Set maximum iterations
    const int MAX_ITERATIONS = 10;
    int iter = 0;

    while (iter < MAX_ITERATIONS && rtmGetErrorStatus(rtM) == NULL) {
        // Save previous states
        prev_UnitDelay_DSTATE = rtDW.UnitDelay_DSTATE;
        prev_UnitDelay1_DSTATE = rtDW.UnitDelay1_DSTATE;
        prev_UnitDelay2_DSTATE = rtDW.UnitDelay2_DSTATE;

        // Set nondet inputs
        rtU.limits = nondet_bool();
        rtU.standby = nondet_bool();
        rtU.supported = nondet_bool();
        rtU.apfail = nondet_bool();
        rtDW.Merge_p[0] = nondet_bool();  // MODE
        rtDW.Merge_p[1] = nondet_bool();  // REQUEST
        rtDW.Merge_p[2] = nondet_bool();  // PULL

        // Step the model
        fsm_12B_global_step();

        // Verify properties based on requirements
        #ifdef VERIFY_PROPERTY_1
            if (rtU.limits && !rtU.standby && rtU.supported && !rtU.apfail) {
                __ESBMC_assert(rtY.pullup == 1, "Property 1: Pullup should be true under specified conditions");
            }
        #endif

        #ifdef VERIFY_PROPERTY_2
            if (prev_UnitDelay_DSTATE == 0.0 && rtU.standby) {
                __ESBMC_assert(rtDW.Merge == 3.0, "Property 2: Should transition to STANDBY state");
            }
        #endif

        #ifdef VERIFY_PROPERTY_3
            if (prev_UnitDelay_DSTATE == 0.0 && rtU.supported && prev_UnitDelay2_DSTATE) {
                __ESBMC_assert(rtDW.Merge == 1.0, "Property 3: Should transition to NOMINAL state");
            }
        #endif

        #ifdef VERIFY_PROPERTY_4
            if (prev_UnitDelay_DSTATE == 1.0 && !prev_UnitDelay2_DSTATE) {
                __ESBMC_assert(rtDW.Merge == 2.0, "Property 4: Should transition to MANEUVER state");
            }
        #endif

        #ifdef VERIFY_PROPERTY_5
            if (prev_UnitDelay_DSTATE == 1.0 && rtU.standby) {
                __ESBMC_assert(rtDW.Merge == 3.0, "Property 5: Should transition to STANDBY state from NOMINAL");
            }
        #endif

        #ifdef VERIFY_PROPERTY_6
            if (prev_UnitDelay_DSTATE == 2.0 && rtU.standby && prev_UnitDelay2_DSTATE) {
                __ESBMC_assert(rtDW.Merge == 3.0, "Property 6: Should transition to STANDBY state from MANEUVER");
            }
        #endif

        #ifdef VERIFY_PROPERTY_7
            if (prev_UnitDelay_DSTATE == 2.0 && rtU.supported && prev_UnitDelay2_DSTATE) {
                __ESBMC_assert(rtDW.Merge == 0.0, "Property 7: Should transition to TRANSITION state");
            }
        #endif

        #ifdef VERIFY_PROPERTY_8
            if (prev_UnitDelay_DSTATE == 3.0 && !rtU.standby) {
                __ESBMC_assert(rtDW.Merge == 0.0, "Property 8: Should transition to TRANSITION state from STANDBY");
            }
        #endif

        #ifdef VERIFY_PROPERTY_9
            if (prev_UnitDelay_DSTATE == 3.0 && rtU.apfail) {
                __ESBMC_assert(rtDW.Merge == 2.0, "Property 9: Should transition to MANEUVER state on apfail");
            }
        #endif

        #ifdef VERIFY_PROPERTY_10
            if (prev_UnitDelay1_DSTATE == 0.0 && rtU.limits) {
                __ESBMC_assert(rtDW.Merge_g == 2.0, "Property 10: Sensor should transition to FAULT state");
            }
        #endif

        #ifdef VERIFY_PROPERTY_11
            if (prev_UnitDelay1_DSTATE == 0.0 && !rtDW.Merge_p[1]) {
                __ESBMC_assert(rtDW.Merge_g == 1.0, "Property 11: Sensor should transition to TRANSITION state");
            }
        #endif

        #ifdef VERIFY_PROPERTY_12
            if (prev_UnitDelay1_DSTATE == 2.0 && !rtDW.Merge_p[1] && !rtU.limits) {
                __ESBMC_assert(rtDW.Merge_g == 1.0, "Property 12: Sensor should transition from FAULT to TRANSITION");
            }
        #endif

        #ifdef VERIFY_PROPERTY_13
            if (prev_UnitDelay1_DSTATE == 1.0 && rtDW.Merge_p[1] && rtDW.Merge_p[0]) {
                __ESBMC_assert(rtDW.Merge_g == 0.0, "Property 13: Sensor should transition to NOMINAL state");
            }
        #endif

        // Verify state updates
        __ESBMC_assert(rtDW.UnitDelay_DSTATE == rtDW.Merge, "UnitDelay state update failed");
        __ESBMC_assert(rtDW.UnitDelay1_DSTATE == rtDW.Merge_g, "UnitDelay1 state update failed");
        __ESBMC_assert(rtDW.UnitDelay2_DSTATE == !(rtDW.Merge_g == 2.0), "UnitDelay2 state update failed");

        iter++;
    }

    return 0;
}