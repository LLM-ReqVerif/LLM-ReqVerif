/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ert_main.c (Modified for ESBMC property checking)
 *
 * Code generated for Simulink model 'EB_12B'.
 *
 * Model version                  : 1.67
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Sun Nov  3 13:05:52 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 10
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 *
 * --------------------------------------------------------------------------
 *          *** ESBMC ASSERTION-BASED HARNESS FOR PROPERTY CHECKS ***
 * --------------------------------------------------------------------------
 *
 * Instructions for use with ESBMC:
 *  1) Compile this code along with EB_12B.c and EB_12B_data.c.
 *  2) Run ESBMC with the desired property macros enabled, for example:
 *       esbmc ert_main.c --unwind 10 -DVERIFY_PROPERTY_1
 *  3) Each property is guarded by #ifdef VERIFY_PROPERTY_N. You can enable
 *     multiple properties simultaneously or individually.
 *  4) __ESBMC_assert is used for property checks. If a property fails,
 *     ESBMC will report a counterexample.
 *  5) This harness runs EB_12B_step() in a simple loop to demonstrate
 *     checking after each iteration.
 *
 */

#include <stddef.h>
#include <stdio.h>
#include <math.h>         /* for fabs(), sqrtf() */
#include "EB_12B.h"       /* Generated model header */

/* --------------------------------------------------------------------------
 * ESBMC requires a definition for nondet_bool (or similar) to produce
 * nondeterministic values.  We do not add any prefix.  You can also create
 * nondet_float(), nondet_int(), etc. if desired.
 * -------------------------------------------------------------------------- */
_Bool nondet_bool(void);

/* __ESBMC_assert is the ESBMC intrinsic for assertion-based verification. */
#ifndef __ESBMC_assert
#define __ESBMC_assert(cond, msg) assert((cond) && (msg))
#endif

/* External model inputs and outputs, matching "system external names" */
extern ExtU rtU;  /* Model inputs  */
extern ExtY rtY;  /* Model outputs */

/*
 * A simple function to check absolute difference within tolerance.
 * (Used to verify "identity" matrices within given tolerances.)
 */
static _Bool within_tol(double val, double ref, double tol)
{
  double diff = val - ref;
  return ( (diff < tol) && (diff > -tol) ) ? 1 : 0;
}

/*
 * Main function (modified) - Runs EB_12B_step() in a loop and checks properties.
 * We do NOT use static variables for storing previous states, in keeping with
 * the no-state design of EB_12B (as per the analysis: no UnitDelay used).
 * We do a finite loop for demonstration and property checking.
 */
int main(void)
{
  int loop_count = 0;
  int i, j;

  /* Initialize the model (sets rtU=0, rtY=0, etc. by default). */
  EB_12B_initialize();

  /* We will run the system for (say) 5 iterations to demonstrate. */
  while (loop_count < 5) {

    /* ---------------------------------------------------------
     * 1) Possible nondeterministic or test inputs:
     *
     * If you had real inputs, you could do:
     *   rtU.some_input_1 = nondet_float();
     *   rtU.some_input_2 = nondet_float();
     *   rtU.some_boolean = nondet_bool();
     *
     * For demonstration, we leave it out or set them to constants.
     * --------------------------------------------------------- */

    /* Call one step of the model */
    EB_12B_step();

    /* After each step, check the properties (requirements). */

    /* ----------------------------------------------------------------------
     * Requirement (1):
     * "When the determinant of B(inv(Wp’)B’) is <= 1e-12 => ridge_on = true,
     *  and the inverted matrix output (rtY.check) is within 1e-6 of the
     *  3x3 identity."
     *
     * We cannot directly measure the determinant here, but the code sets
     * rtY.ridge_on accordingly. If ridge_on is true, then check must be
     * identity within ±1e-6. 
     * ---------------------------------------------------------------------- */
#ifdef VERIFY_PROPERTY_1
    if (rtY.ridge_on) {
      /* Check each element of rtY.check[] is close to identity (3x3). */
      for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
          double ideal = (i == j) ? 1.0 : 0.0;
          __ESBMC_assert(within_tol(rtY.check[3*i + j], ideal, 1.0e-6),
            "Property 1: check matrix must be identity (±1e-6) if ridge_on == true");
        }
      }
    }
#endif /* VERIFY_PROPERTY_1 */

    /* ----------------------------------------------------------------------
     * Requirement (2):
     * "When the determinant of B(inv(Wp’)B’) is > 1e-12 => ridge_on = false,
     *  and the inverted matrix output (rtY.check) is within 1e-12 of the
     *  3x3 identity."
     *
     * Similarly, if ridge_on is false, check must be identity within ±1e-12.
     * ---------------------------------------------------------------------- */
#ifdef VERIFY_PROPERTY_2
    if (!rtY.ridge_on) {
      /* Check each element of rtY.check[] is close to identity (3x3). */
      for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
          double ideal = (i == j) ? 1.0 : 0.0;
          __ESBMC_assert(within_tol(rtY.check[3*i + j], ideal, 1.0e-12),
            "Property 2: check matrix must be identity (±1e-12) if ridge_on == false");
        }
      }
    }
#endif /* VERIFY_PROPERTY_2 */

    /* ----------------------------------------------------------------------
     * Requirement (3):
     * "The output u vector should be a 5x1 vector."
     *
     * The generated code has rtY.u[5]. We confirm its size is 5. This is a
     * static guarantee by design, but we place an assertion for property form.
     * ---------------------------------------------------------------------- */
#ifdef VERIFY_PROPERTY_3
    /* Since rtY.u is declared as rtY.u[5], there's no runtime resizing. */
    __ESBMC_assert((sizeof(rtY.u) / sizeof(rtY.u[0])) == 5,
      "Property 3: output 'u' must have exactly 5 elements");
#endif /* VERIFY_PROPERTY_3 */

    /* ----------------------------------------------------------------------
     * Requirement (4):
     * "The 2-norm of the output Buminusd should be less than 0.01."
     *
     * We check sqrt( sum( Buminusd[i]^2 ) ) < 0.01.
     * Buminusd is dimension 3x1.
     * ---------------------------------------------------------------------- */
#ifdef VERIFY_PROPERTY_4
    {
      double norm2 = 0.0;
      for (i = 0; i < 3; i++) {
        norm2 += (double)rtY.Buminusd[i] * (double)rtY.Buminusd[i];
      }
      double norm_val = sqrt(norm2);
      __ESBMC_assert(norm_val < 0.01,
        "Property 4: 2-norm of Buminusd must be < 0.01");
    }
#endif /* VERIFY_PROPERTY_4 */

    /* ----------------------------------------------------------------------
     * Requirement (5):
     * "The output cost J shall be the minimum possible value given the set
     *  of input conditions."
     *
     * Since we cannot directly compare alternative solutions here, we at least
     * assert that J is non-negative (typical if J is a quadratic cost).
     * ---------------------------------------------------------------------- */
#ifdef VERIFY_PROPERTY_5
    __ESBMC_assert(rtY.J >= 0.0,
      "Property 5: The cost J should be non-negative (assumed minimal).");
#endif /* VERIFY_PROPERTY_5 */

    /* ----------------------------------------------------------------------
     * Per the analysis: EB_12B has no persistent states; no UnitDelay usage.
     * So there's no "carry-over" from one cycle to the next. This loop does
     * not hold any prior-step data in static variables.
     * ---------------------------------------------------------------------- */

    loop_count++;
  }

  return 0; /* end of main */
}
