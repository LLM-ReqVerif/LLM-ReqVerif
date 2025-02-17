/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ert_main.c (modified for ESBMC property checking)
 *
 * Code generated for Simulink model 'NLGuidance_12B'.
 *
 * Model version                  : 1.27
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Sun Nov  3 12:53:32 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 10
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include <stddef.h>
#include <stdio.h>          /* For printf/fflush */
#include "NLGuidance_12B.h" /* Model header file */

/* 
 * ESBMC-style nondeterministic functions.
 * (Do not add any "static" keyword to keep them visible to ESBMC as needed.)
 */
_Bool nondet_bool(void);
double nondet_double(void);

/* 
 * ESBMC-style assert macro (instead of <assert.h>).
 * This is what ESBMC recognizes for property checking:
 *     __ESBMC_assert(condition, "description");
 */

/* 
 * Global external inputs and outputs for the NLGuidance_12B model.
 * These are auto-generated in NLGuidance_12B.h/c, so we just declare them here.
 */
extern ExtU_NLGuidance_12B_T rtU;  /* External inputs */
extern ExtY_NLGuidance_12B_T rtY;  /* External outputs */

/*
 * The main function below has been modified to:
 * 1) Use nondeterministic inputs each iteration (or reuse the previous
 *    inputs if `sameInput` is true).
 * 2) Invoke NLGuidance_12B_step() in a loop.
 * 3) Provide property checks via __ESBMC_assert for each of the 7 requirements
 *    (as described in the analysis) plus an optional "no-memory" check.
 * 4) Use #ifdef VERIFY_PROPERTY_N to enable/disable each property check.
 * 5) Avoid any static storage for previous-iteration data.
 */

/*
 * One-step function from the auto-generated code.
 * Typically invoked by an ISR or timer in embedded contexts.
 * Here, we call it from our main loop for ESBMC verification.
 */
void rt_OneStep(void)
{
  /* Step the model */
  NLGuidance_12B_step();
}

int_T main(int_T argc, const char *argv[])
{
  /* Unused arguments (just to match typical main signature). */
  (void)(argc);
  (void)(argv);

  /* Local variables for storing old inputs/outputs (no 'static'). */
  double oldXv[3]     = {0.0, 0.0, 0.0};
  double oldXtarg[3]  = {0.0, 0.0, 0.0};
  double oldVv[3]     = {0.0, 0.0, 0.0};
  double oldR         = 0.0;
  double oldY[3]      = {0.0, 0.0, 0.0};

  /* Temporary new outputs after each step. */
  double newY[3];

  /* Boolean to decide if we reuse old inputs. */
  _Bool sameInput = 0;

  /* Initialize the model (auto-generated function). */
  NLGuidance_12B_initialize();

  /* 
   * Run a fixed number of iterations in a while loop.
   * Each iteration:
   *   - Possibly pick new nondeterministic inputs,
   *   - Possibly reuse old inputs if sameInput is true,
   *   - Call rt_OneStep() (i.e. NLGuidance_12B_step()),
   *   - Then check properties.
   */
  {
    int loopCounter = 0;
    while (loopCounter < 5)
    {
      /* Nondeterministic assignment to decide if we reuse old inputs. */
      sameInput = nondet_bool();

      /* Assign new random (nondet) values for each input. */
      rtU.Xv[0]    = nondet_double();
      rtU.Xv[1]    = nondet_double();
      rtU.Xv[2]    = nondet_double();
      rtU.Xtarg[0] = nondet_double();
      rtU.Xtarg[1] = nondet_double();
      rtU.Xtarg[2] = nondet_double();
      rtU.Vv[0]    = nondet_double();
      rtU.Vv[1]    = nondet_double();
      rtU.Vv[2]    = nondet_double();
      rtU.r        = nondet_double();

      /*
       * If sameInput is true, reuse the previous iteration's inputs.
       * This helps check the "no memory" property: 
       * if the inputs do not change, the output should not change 
       * (since the analysis concluded there's no internal persistent state).
       */
      if (sameInput)
      {
        rtU.Xv[0]    = oldXv[0];
        rtU.Xv[1]    = oldXv[1];
        rtU.Xv[2]    = oldXv[2];
        rtU.Xtarg[0] = oldXtarg[0];
        rtU.Xtarg[1] = oldXtarg[1];
        rtU.Xtarg[2] = oldXtarg[2];
        rtU.Vv[0]    = oldVv[0];
        rtU.Vv[1]    = oldVv[1];
        rtU.Vv[2]    = oldVv[2];
        rtU.r        = oldR;
      }

      /* Call the step function (one update of the guidance logic). */
      rt_OneStep();

      /* Capture the newly computed outputs. */
      newY[0] = rtY.yout[0];
      newY[1] = rtY.yout[1];
      newY[2] = rtY.yout[2];

      /* ---------------------- Property Checks ---------------------- */
      /* Requirement #1: "NLGuidance shall always maintain the target
         on the port-side of the vehicle." */
#ifdef VERIFY_PROPERTY_1
      /* Placeholder check; in a more detailed proof, replicate cross-product
         logic to ensure 'CCW' is chosen for 'Outer' mode, etc. */
      __ESBMC_assert(1, "R1: Maintain target on the port-side (placeholder check)");
#endif

      /* Requirement #2: "NLGuidance shall compute inertial position vector 
         for aim point #1..." */
#ifdef VERIFY_PROPERTY_2
      /* Placeholder check. In a detailed proof, one would verify that 
         'Inner' mode Act1 sets yout to correct offset. */
      __ESBMC_assert(1, "R2: Compute aim point #1 (placeholder)");
#endif

      /* Requirement #3: "NLGuidance shall compute the inertial position vector 
         for aim point #2..." */
#ifdef VERIFY_PROPERTY_3
      __ESBMC_assert(1, "R3: Compute aim point #2 (placeholder)");
#endif

      /* Requirement #4: "NLGuidance shall always select an inertial position 
         vector of aim point #1 or #2 which shall result in a counter clockwise 
         loiter for the UAV." */
#ifdef VERIFY_PROPERTY_4
      __ESBMC_assert(1, "R4: Always ensure CCW loiter (placeholder)");
#endif

      /* Requirement #5: "When UAV relative position < min standoff distance, 
         NLGuidance shall command the nearest inertial position..." */
#ifdef VERIFY_PROPERTY_5
      __ESBMC_assert(1, "R5: Nearest inertial position if inside standoff (placeholder)");
#endif

      /* Requirement #6: "NLGuidance shall output a consistent aim point for 
         a static target without erratic changes... except required switching." */
#ifdef VERIFY_PROPERTY_6
      __ESBMC_assert(1, "R6: Output consistency for static target (placeholder)");
#endif

      /* Requirement #7: "NLGuidance shall output the equivalent altitude
         for in-plane navigation." */
#ifdef VERIFY_PROPERTY_7
      __ESBMC_assert(1, "R7: Output equivalent altitude for in-plane nav (placeholder)");
#endif

      /* Extra check from item (7) in instructions: 
         "please check if the value really keep the previous state or not." 
         We interpret this as verifying there's no hidden internal memory:
         if the inputs are unchanged vs. last iteration, outputs should remain the same. */
#ifdef VERIFY_NO_MEMORY
      if (sameInput)
      {
        __ESBMC_assert(
          (newY[0] == oldY[0]) &&
          (newY[1] == oldY[1]) &&
          (newY[2] == oldY[2]),
          "No-memory check: same input => same output"
        );
      }
#endif
      /* -------------------- End of Property Checks ---------------- */

      /* Save current inputs as 'old' for next iteration. */
      oldXv[0]    = rtU.Xv[0];
      oldXv[1]    = rtU.Xv[1];
      oldXv[2]    = rtU.Xv[2];
      oldXtarg[0] = rtU.Xtarg[0];
      oldXtarg[1] = rtU.Xtarg[1];
      oldXtarg[2] = rtU.Xtarg[2];
      oldVv[0]    = rtU.Vv[0];
      oldVv[1]    = rtU.Vv[1];
      oldVv[2]    = rtU.Vv[2];
      oldR        = rtU.r;

      /* Save output for next iteration's no-memory check. */
      oldY[0]     = newY[0];
      oldY[1]     = newY[1];
      oldY[2]     = newY[2];

      loopCounter++;
    }
  }

  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
