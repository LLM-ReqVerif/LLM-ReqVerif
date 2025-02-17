#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include "swim_12B.h"
#include <assert.h>
// Nondet inputs
_Bool nondet_bool(void);
double nondet_double(void);
int nondet_int(void);

// Global variables to store previous states
double prev_SWIM_ASWarningAllowed;
double prev_AgcasLowSpeedWarn;

// Maximum number of verification loops
#define MAX_LOOPS 3

// Verification properties
void verify_auto_gcas_min_vcas(double weight, int cat_pos, double calculated_vcas) {
    
    if (cat_pos == 0) {  // CAT I
        double expected = 1.25921 * sqrt(weight) + 10.0;
        __ESBMC_assert(calculated_vcas == expected, "CAT I Auto GCAS Min Vcas calculation incorrect");
    } else {  // CAT III
        double expected = 1.33694 * sqrt(weight) + 10.0;
        __ESBMC_assert(calculated_vcas == expected, "CAT III Auto GCAS Min Vcas calculation incorrect");
    }
}

void verify_state_transitions(double curr_SWIM_ASWarningAllowed, 
                            double curr_AgcasLowSpeedWarn,
                            _Bool landing_gear,
                            double impact_pressure,
                            double min_pressure,
                            _Bool monitor_enable,
                            _Bool low_speed_warn,
                            _Bool interlocks) {
    

    // Verify SWIM_ASWarningAllowed transitions
    if (!landing_gear) {
        assert(0);
        __ESBMC_assert(curr_SWIM_ASWarningAllowed == 0.0, "SWIM_ASWarningAllowed should be 0 when landing gear is false");
    } else if (landing_gear && impact_pressure > min_pressure) {
        assert(0);
        __ESBMC_assert(curr_SWIM_ASWarningAllowed == 1.0, "SWIM_ASWarningAllowed should be 1 under specified conditions");
    } else {
        assert(0);
        __ESBMC_assert(curr_SWIM_ASWarningAllowed == prev_SWIM_ASWarningAllowed, "SWIM_ASWarningAllowed should maintain previous state");
    }

    // Verify AgcasLowSpeedWarn transitions
    if ((monitor_enable || low_speed_warn) && (!interlocks) && (curr_SWIM_ASWarningAllowed == 1.0)) {
        assert(0);
        _Bool expected_warn = (impact_pressure < (min_pressure - 28.72));
        __ESBMC_assert((curr_AgcasLowSpeedWarn == expected_warn), "AgcasLowSpeedWarn calculation incorrect");
    } else {
        assert(0);
        __ESBMC_assert(curr_AgcasLowSpeedWarn == prev_AgcasLowSpeedWarn, "AgcasLowSpeedWarn should maintain previous state");
    }
}

int main(void) {
    // Initialize model
    swim_12B_initialize();

    // Initialize previous states
    prev_SWIM_ASWarningAllowed = 0.0;
    prev_AgcasLowSpeedWarn = 0.0;
    
    int loop_count = 0;
    
    while (loop_count < MAX_LOOPS && nondet_bool()) {
        // Set non-deterministic inputs
        rtU.diGet_S_CatSwitchPosition = nondet_int();
        rtU.muxGet_T_Mux_AircraftGrossWeigh = nondet_double();
        rtU.diGet_S_LandingGearAltFlap = nondet_bool();
        rtU.E_AI_IMPACT_PRESSURE = nondet_double();
        rtU.muxGet_T_Mux_AirspeedMonitorEna = nondet_bool();
        rtU.cvGet_V_AgcasLowSpeedWarn = nondet_bool();
        rtU.olcGet_AgcasInterlocks = nondet_bool();
        // Run one step of the model

        swim_12B_step();

        // Verify properties based on preprocessing macros
        #ifdef VERIFY_PROPERTY_1
        //__ESBMC_assume (rtU.muxGet_T_Mux_AircraftGrossWeigh>0); (dont know plane weight >0)
        verify_auto_gcas_min_vcas(rtU.muxGet_T_Mux_AircraftGrossWeigh,
                                 rtU.diGet_S_CatSwitchPosition,
                                 rtY.SWIM_CalAirspeedmin_kts);

        #endif


        #ifdef VERIFY_PROPERTY_2
        verify_state_transitions(rtY.SWIM_ASWarningAllowed,
                               rtY.swimGet_AgcasLowSpeedWarn,
                               rtU.diGet_S_LandingGearAltFlap,
                               rtU.E_AI_IMPACT_PRESSURE,
                               rtY.SWIM_Qcmin_lbspft2,
                               rtU.muxGet_T_Mux_AirspeedMonitorEna,
                               rtU.cvGet_V_AgcasLowSpeedWarn,
                               rtU.olcGet_AgcasInterlocks);
        #endif

        // Update previous states for next iteration
        prev_SWIM_ASWarningAllowed = rtY.SWIM_ASWarningAllowed;
        prev_AgcasLowSpeedWarn = rtY.swimGet_AgcasLowSpeedWarn;
        
        loop_count++;
    }

    return 0;
}