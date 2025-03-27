#include <stddef.h>
#include <stdio.h>
#include "integrator_12B.h"
#include <math.h>
// Nondet declarations for inputs
double nondet_double(void);
_Bool nondet_bool(void);

// Previous state tracking
double prev_output;
double prev_input;

void rt_OneStep(void) {
    /* Step the model */
    integrator_12B_step();
    
    /* Update previous states */
    prev_output = rtY.yout;
    prev_input = rtU.cmd;
}

int main(void) {
    unsigned int i = 0;
    const unsigned int MAX_STEPS = 1000;
    
    /* Initialize model */
    integrator_12B_initialize();

    /* Initialize inputs with nondet values */
    rtU.cmd = nondet_double();
    rtU.T = nondet_double();
    rtU.TL = nondet_double();
    rtU.BL = nondet_double();
    rtU.reset = nondet_bool();
    rtU.ic = nondet_double();
    
    /* Reset behavior verification */
    #ifdef VERIFY_PROPERTY_1
        // Normal IC bounds
        if (rtU.reset && rtU.ic <= rtU.TL && rtU.ic >= rtU.BL) {
            rt_OneStep();
            __ESBMC_assert(rtY.yout == rtU.ic, "Reset with bounded IC failed");
        }
        
        // High IC
        if (rtU.reset && rtU.ic > rtU.TL && rtU.TL >= rtU.BL) {
            rt_OneStep();
            __ESBMC_assert(rtY.yout == rtU.TL, "Reset with high IC failed");
        }
        
        // Low IC
        if (rtU.reset && rtU.ic < rtU.BL && rtU.TL >= rtU.BL) {
            rt_OneStep();
            __ESBMC_assert(rtY.yout == rtU.BL, "Reset with low IC failed");
        }
        
        // Inverted limits high
        if (rtU.reset && rtU.ic >= rtU.BL && rtU.TL < rtU.BL) {
            rt_OneStep();
            __ESBMC_assert(rtY.yout == rtU.BL, "Reset with inverted limits high failed");
        }
        
        // Inverted limits low
        if (rtU.reset && rtU.ic <= rtU.TL && rtU.TL < rtU.BL) {
            rt_OneStep();
            __ESBMC_assert(rtY.yout == rtU.TL, "Reset with inverted limits low failed");
        }
    #endif

    /* Main verification loop */
    while (i < MAX_STEPS) {
        /* Store previous values */
        prev_output = rtY.yout;
        prev_input = rtU.cmd;
        
        /* Get new nondet inputs */
        rtU.cmd = nondet_double();
        rtU.reset = nondet_bool();
        
        
        rt_OneStep();
        
        /* Output bounds verification */
#ifdef VERIFY_PROPERTY_2

            if (rtU.TL >= rtU.BL) {
                __ESBMC_assert(rtY.yout >= rtU.BL && rtY.yout <= rtU.TL,
                              "Normal limits bounds check failed");
            } else {
                __ESBMC_assert(rtY.yout >= rtU.TL && rtY.yout  <= rtU.BL,
                              "Inverted limits bounds check failed");
            }
        #endif

        /* Normal operation integration verification */
        #ifdef VERIFY_PROPERTY_3
            if (!rtU.reset && rtU.TL >= rtU.BL) {
                double expected = 0.5 * rtU.T * (rtU.cmd + prev_input) + prev_output;
                if (expected >= rtU.BL && expected <= rtU.TL) {
                    __ESBMC_assert(rtY.yout == expected,
                                 "Normal integration calculation failed");
                }
            }
        #endif
        
        #ifdef VERIFY_PROPERTY_4A
        /* Constant input integration verification */
        if (i == 100 && rtU.cmd == 1.0 && rtU.T == 0.1 && !rtU.reset) {
            double expected = 10.0;  
            __ESBMC_assert(rtY.yout - expected <= 0.1 && 
                        expected - rtY.yout <= 0.1,
                        "Constant input integration failed after 10 seconds");
        }
        #endif

        /* Cosine input integration verification */
        #ifdef VERIFY_PROPERTY_4B
            if (rtU.T == 0.1 && !rtU.reset && 
                rtU.TL >= rtU.BL && rtY.yout > rtU.BL && rtY.yout < rtU.TL) {
                // Assuming rtU.cmd follows cosine pattern
                double expected_sin = sin(i * rtU.T);
                __ESBMC_assert(rtY.yout - expected_sin <= 0.1 && 
                              expected_sin - rtY.yout <= 0.1,
                              "Cosine input integration failed");
            }
        #endif

        i++;
    }

    return 0;
}