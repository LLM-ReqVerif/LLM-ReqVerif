/*
 * File: ert_main.c
 *
 * Custom main for ESBMC property checks on triplex_12B.
 */

#include <stddef.h>
#include <stdio.h>
#include <math.h> /* fabs */
#include "triplex_12B.h" /* Include the model's header file */

/* ---------------- Nondeterministic Input Declarations ---------------- */
_Bool nondet_bool(void);
double nondet_double(void);

/* ---------------- Main Function for ESBMC Verification ---------------- */
int main(void)
{
  /* Local iteration count */
  int loop_count = 0;
  const int MAX_LOOP = 10;

  /* Variables to hold old (previous-cycle) states and outputs */
  double PC_prev = 0.0;   /* from rtDW.Delay1_DSTATE[0] */
  double TC_prev = 0.0;   /* from rtDW.Delay1_DSTATE[1] */
  double FC_prev = 0.0;   /* from rtDW.Delay1_DSTATE[2] */
  double sel_val_prev = 0.0;

  /* Initialize the system */
  triplex_12B_initialize();

  /* We'll run the system for MAX_LOOP cycles */
  while (loop_count < MAX_LOOP)
  {
    /* ---------- 1) Assign nondeterministic inputs each cycle ---------- */
    rtU.ia      = nondet_double();
    rtU.ib      = nondet_double();
    rtU.ic      = nondet_double();
    rtU.Tlevel  = nondet_double();
    rtU.PClimit = nondet_double();

    /* Read the previous states for property checks (before stepping) */
    PC_prev       = rtDW.Delay1_DSTATE[0];
    TC_prev       = rtDW.Delay1_DSTATE[1];
    FC_prev       = rtDW.Delay1_DSTATE[2];
    sel_val_prev  = rtY.sel_val;  /* Last cycle’s selected value */

    /* ---------- 2) Step the model (one global step) ---------- */
    triplex_12B_step();

    /*
     * After the step:
     *  - The new states are visible in rtDW.Delay1_DSTATE[..] at the end of triplex_12B_step()
     *  - The new outputs are in rtY.sel_val, rtY.FC, etc.
     */

    /* For convenience in property checks: */
    double PC_new = rtDW.Delay1_DSTATE[0];
    double TC_new = rtDW.Delay1_DSTATE[1];
    double FC_new = rtDW.Delay1_DSTATE[2];
    double sel_val_new = rtY.sel_val;

    /* ---------------------------------------------------------------------
     * [RM-001] "In the no-fail state, a mis-compare that lasts more than the
     *           persistence limit shall be reported as a failure."
     *
     *   Check (informally) that if we were in FC_prev == 0,
     *   and if PC has now exceeded PClimit, then we must have latched FC_new != 0.
     * --------------------------------------------------------------------- */
#ifdef VERIFY_PROPERTY_1
    {
      /* Only check if we were in no-fail previously */
      if (FC_prev == 0.0)
      {
        /*
         * If PC_new > rtU.PClimit (this cycle’s input) and the system says
         * there's a single-branch miscompare, then FC_new should be latched (nonzero).
         *
         * We can't strictly track "more than PClimit cycles" in a single step,
         * but we approximate that if PC_new > rtU.PClimit now, it implies
         * the code was supposed to latch a failure this cycle.
         */
        double cur_PClimit = rtU.PClimit; /* This cycle’s input */
        if (PC_new > cur_PClimit)
        {
          __ESBMC_assert((FC_new == 1.0 || FC_new == 2.0 || FC_new == 4.0),
            "[RM-001] A single branch must be latched as failed once PC_new > PClimit.");
        }
      }
    }
#endif /* VERIFY_PROPERTY_1 */

    /* ---------------------------------------------------------------------
     * [RM-002] "In the no-fail state, the mid-value shall be the selected value."
     *
     *   If FC_new == 0, then sel_val_new must be the mid of (ia, ib, ic).
     *   (We check the final output at end of this cycle.)
     * --------------------------------------------------------------------- */
#ifdef VERIFY_PROPERTY_2
    {
      if (FC_new == 0.0)
      {
        /* Sort ia, ib, ic to find the mid value quickly */
        double a[3];
        a[0] = rtU.ia; a[1] = rtU.ib; a[2] = rtU.ic;

        /* Simple Bubble Sort for 3 elements just for demonstration */
        for(int i = 0; i < 3; i++)
        {
          for(int j = 0; j < 2; j++)
          {
            if(a[j] > a[j+1])
            {
              double temp = a[j];
              a[j] = a[j+1];
              a[j+1] = temp;
            }
          }
        }
        double mid_val = a[1];

        __ESBMC_assert(fabs(sel_val_new - mid_val) < 1e-12,
          "[RM-002] sel_val must be the mid-value if no-fail state (FC==0).");
      }
    }
#endif /* VERIFY_PROPERTY_2 */

    /* ---------------------------------------------------------------------
     * [RM-003] "In the single-fail state, the average of the remaining two
     *           good branches shall be the selected value."
     *
     *   If FC_new is 1, 2, or 4 => indicates which branch failed.
     *   Then sel_val_new = average of the two good channels.
     * --------------------------------------------------------------------- */
#ifdef VERIFY_PROPERTY_3
    {
      if (FC_new == 1.0) /* Single-BranchC-Fail => use (ia+ib)/2 */
      {
        double expected = (rtU.ia + rtU.ib)/2.0;
        __ESBMC_assert(fabs(sel_val_new - expected) < 1e-12,
          "[RM-003] FC=1 => sel_val should be (ia + ib)/2.");
      }
      if (FC_new == 2.0) /* Single-BranchB-Fail => use (ia+ic)/2 */
      {
        double expected = (rtU.ia + rtU.ic)/2.0;
        __ESBMC_assert(fabs(sel_val_new - expected) < 1e-12,
          "[RM-003] FC=2 => sel_val should be (ia + ic)/2.");
      }
      if (FC_new == 4.0) /* Single-BranchA-Fail => use (ib+ic)/2 */
      {
        double expected = (rtU.ib + rtU.ic)/2.0;
        __ESBMC_assert(fabs(sel_val_new - expected) < 1e-12,
          "[RM-003] FC=4 => sel_val should be (ib + ic)/2.");
      }
    }
#endif /* VERIFY_PROPERTY_3 */

    /* ---------------------------------------------------------------------
     * [RM-004] "If a second failure is in progress, the selected value shall
     *           remain unchanged from the previous selected value."
     *
     *   The code effectively stops monitoring after a second failure attempt.
     *   If FC_prev != 0, we are in single-fail. If a new mis-compare is
     *   pushing for a second fail, the code maintains the old sel_val
     *   (it does not recalculate for 2-fail states).
     *
     *   This check is approximate: we see if FC_prev != 0 and
     *   if there's an additional large mis-compare that *could* trigger
     *   a second fail. Then we assert the sel_val did not change.
     * --------------------------------------------------------------------- */
#ifdef VERIFY_PROPERTY_4
    {
      if (FC_prev != 0.0)
      {
        /* Approx: if any new miscompare among the "good" channels is above Tlevel,
         * we consider that a 'second failure in progress'.
         * Then we require sel_val to remain the same as last cycle.
         */
        double diffAB = fabs(rtU.ia - rtU.ib);
        double diffAC = fabs(rtU.ia - rtU.ic);
        double diffBC = fabs(rtU.ib - rtU.ic);

        double th = rtU.Tlevel; /* This cycle Tlevel */

        /* If there's any new mis-compare above threshold among the presumably good branches */
        _Bool second_miscompare = 0;

        /* Determine which branch is failed from FC_prev (1=>Cfail, 2=>Bfail, 4=>Afail) */
        if (FC_prev == 1.0) /* C failed previously => check A,B difference only */
        {
          if (diffAB > th) second_miscompare = 1;
        }
        else if (FC_prev == 2.0) /* B failed => check A,C difference only */
        {
          if (diffAC > th) second_miscompare = 1;
        }
        else if (FC_prev == 4.0) /* A failed => check B,C difference only */
        {
          if (diffBC > th) second_miscompare = 1;
        }

        if (second_miscompare)
        {
          __ESBMC_assert(
            fabs(sel_val_new - sel_val_prev) < 1e-12,
            "[RM-004] If second failure is in progress, sel_val should remain unchanged."
          );
        }
      }
    }
#endif /* VERIFY_PROPERTY_4 */

    /*
     * 7) Check if persistent states properly hold values from previous cycles.
     *    The model's code updates Delay states at the *end* of the step function.
     *    So next iteration, we should see PC_prev == PC_new, etc.
     *    We'll do that check next time around.
     *    (No separate assertion needed here, but if you want, you can add a property
     *     that compares iteration n+1's PC_prev with iteration n's PC_new.)
     */

    /* Move to next iteration */
    loop_count++;
  }

  /* End of while loop - normal termination */
  return 0;
}

/* ------------
 * ESBMC requires these nondeterministic stubs.
 * Adjust return types as needed:
 *------------ */
_Bool nondet_bool(void)
{
  _Bool b;
  return b; /* The solver decides what b is */
}
double nondet_double(void)
{
  double x;
  return x; /* The solver decides the double value */
}
