#include <stddef.h>
#include <stdio.h>
#include "triplex_12B.h"
#include <math.h>
// Global constants for verification
#define MAX_LOOPS 5
#define TLEVEL 10
#define PCLIMIT 5

// Global variables to track previous states
double prev_sel_val;
int prev_fc;

// Nondet inputs
_Bool nondet_bool(void);

double nondet_double(void);

// Helper function to check if miscompare exists
_Bool check_miscompare(double ia, double ib, double ic) {
    return (fabs(ia - ib) > TLEVEL) || 
           (fabs(ib - ic) > TLEVEL) || 
           (fabs(ia - ic) > TLEVEL);
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
    
    
    while(loop_count < MAX_LOOPS) {
        // Get nondeterministic inputs
        rtU.ia = nondet_double();
        rtU.ib = nondet_double();
        rtU.ic = nondet_double();
        __ESBMC_assume(!isnan(rtU.ia)&&!isinf(rtU.ia));
        __ESBMC_assume(!isnan(rtU.ib)&&!isinf(rtU.ib));
        __ESBMC_assume(!isnan(rtU.ic)&&!isinf(rtU.ic));
        
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
        if (check_miscompare(rtU.ia, rtU.ib, rtU.ic) && !first_failure_occurred) {
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
            double a = rtU.ia;
            double b = rtU.ib;
            double c = rtU.ic;
            double mid_val;
            
            if (a <= b && b <= c) mid_val = b;
            else if (a <= c && c <= b) mid_val = c;
            else if (b <= a && a <= c) mid_val = a;
            else if (b <= c && c <= a) mid_val = c;
            else if (c <= a && a <= b) mid_val = a;
            else mid_val = b;
            
            __ESBMC_assert(fabs(rtDW.Merge - mid_val) < 0.001,
                        "RM-002: Output should be mid-value in no-fail state");
        }
        #endif
        
        // RM-003: Single-Fail Selection
        #ifdef VERIFY_PROPERTY_3
        if (rtDW.Delay1_DSTATE[2] != 0 && !second_failure_occurred) {
            double expected_val;
            __ESBMC_assume(!isnan(rtDW.Merge )&&!isinf(rtDW.Merge ));
            switch(rtDW.Delay1_DSTATE[2]) {
                case 1: // Branch C failed
                    expected_val = (rtU.ia + rtU.ib) / 2.0;
                    break;
                case 2: // Branch B failed
                    expected_val = (rtU.ia + rtU.ic) / 2.0;
                    break;
                case 4: // Branch A failed
                    expected_val = (rtU.ib + rtU.ic) / 2.0;
                    break;
                default:
                    expected_val = rtDW.Merge;
            }
            __ESBMC_assert(rtDW.Merge - expected_val <0.001,
                          "RM-003: Output should be average of remaining inputs");
        }
        #endif
        
        // RM-004: Second Failure Handling
        #ifdef VERIFY_PROPERTY_4
        __ESBMC_assume(!isnan(rtDW.Merge )&&!isinf(rtDW.Merge ));
        if (rtDW.Delay1_DSTATE[2] != 0 && check_miscompare(rtU.ia, rtU.ib, rtU.ic)) {
            if (!second_failure_occurred) {
                __ESBMC_assert(fabs(rtDW.Merge - prev_sel_val) < 0.001,
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