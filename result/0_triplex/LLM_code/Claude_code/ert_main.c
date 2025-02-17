#include <stddef.h>
#include <stdio.h>
#include "triplex_12B.h"
#include <math.h>
// Global constants for verification
#define MAX_LOOPS 10
#define TLEVEL 100
#define PCLIMIT 5

// Global variables to track previous states
float prev_sel_val;
int prev_fc;

// Nondet inputs
float nondet_float(void);
_Bool nondet_bool(void);

// Helper function to check if miscompare exists
_Bool check_miscompare(float ia, float ib, float ic) {
    return (fabsf(ia - ib) > TLEVEL) || 
           (fabsf(ib - ic) > TLEVEL) || 
           (fabsf(ia - ic) > TLEVEL);
}
void rt_OneStep(void);
void rt_OneStep(void)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  /* Step the model */
  triplex_12B_step();

  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

int main(int argc, const char *argv[]) {
    // Initialize model
    triplex_12B_initialize();
    
    // Variables to track state
    int loop_count = 0;
    _Bool first_failure_occurred = 0;
    _Bool second_failure_occurred = 0;
    
    // Input variables
    float ia, ib, ic;
    
    while(loop_count < MAX_LOOPS) {
        // Get nondeterministic inputs
        ia = nondet_float();
        ib = nondet_float();
        ic = nondet_float();
        
        // Store previous values
        prev_sel_val = rtDW.Merge;
        prev_fc = rtDW.Delay1_DSTATE[2];
        
        // Run one step of the system
        rt_OneStep();

        if (rtDW.Delay1_DSTATE[0] > PCLIMIT) {
            second_failure_occurred = 1;
        }
        
        // RM-001: First Failure Detection
        #ifdef VERIFY_PROPERTY_1
        if (check_miscompare(ia, ib, ic) && !first_failure_occurred) {
            __ESBMC_assert(rtDW.Delay1_DSTATE[0] > prev_fc || 
                          rtDW.Delay1_DSTATE[2] != 0,
                          "RM-001: PC should increment or fault should be detected");
            
            if (rtDW.Delay1_DSTATE[0] > PCLIMIT) {
                __ESBMC_assert(rtDW.Delay1_DSTATE[2] != 0,
                              "RM-001: Fault code should be set after PClimit");
                first_failure_occurred = 1;
            }
        }
        #endif
        
        // RM-002: No-Fail Selection
        #ifdef VERIFY_PROPERTY_2
        if (rtDW.Delay1_DSTATE[2] == 0) {
            float mid_val;
            if (ia <= ib && ib <= ic) mid_val = ib;
            else if (ia <= ic && ic <= ib) mid_val = ic;
            else if (ib <= ia && ia <= ic) mid_val = ia;
            else if (ib <= ic && ic <= ia) mid_val = ic;
            else if (ic <= ia && ia <= ib) mid_val = ia;
            else mid_val = ib;
            
            __ESBMC_assert(fabsf(rtDW.Merge - mid_val) < 0.001,
                          "RM-002: Output should be mid-value in no-fail state");
        }
        #endif
        
        // RM-003: Single-Fail Selection
        #ifdef VERIFY_PROPERTY_3
        if (rtDW.Delay1_DSTATE[2] != 0 && !second_failure_occurred) {
            float expected_val;
            switch(rtDW.Delay1_DSTATE[2]) {
                case 1: // Branch C failed
                    expected_val = (ia + ib) / 2.0f;
                    break;
                case 2: // Branch B failed
                    expected_val = (ia + ic) / 2.0f;
                    break;
                case 4: // Branch A failed
                    expected_val = (ib + ic) / 2.0f;
                    break;
                default:
                    expected_val = rtDW.Merge;
            }
            __ESBMC_assert(fabsf(rtDW.Merge - expected_val) < 0.001,
                          "RM-003: Output should be average of remaining inputs");
        }
        #endif
        
        // RM-004: Second Failure Handling
        #ifdef VERIFY_PROPERTY_4
        if (rtDW.Delay1_DSTATE[2] != 0 && check_miscompare(ia, ib, ic)) {
            if (!second_failure_occurred) {
                __ESBMC_assert(fabsf(rtDW.Merge - prev_sel_val) < 0.001,
                              "RM-004: Output should remain unchanged during second failure");
                __ESBMC_assert(rtDW.Delay1_DSTATE[0] >= prev_fc,
                              "RM-004: PC should increment during second failure");
            }
        }
        #endif
        
        loop_count++;
    }
    
    return 0;
}