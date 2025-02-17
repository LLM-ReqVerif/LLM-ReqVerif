/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  
 * Not for government, commercial, or other organizational use.
 *
 * Example ERT main with ESBMC verification assertions for swim_12B.
 *
 * The code below:
 *   1) Initializes the model,
 *   2) Runs a loop with nondeterministic inputs,
 *   3) Calls swim_12B_step(),
 *   4) Checks requirement properties (#ifdef VERIFY_PROPERTY_n),
 *   5) Stores state variables to verify they are kept correctly across cycles.
 *
 * Instructions:
 *   - Define (via your build command) the macros VERIFY_PROPERTY_1, 
 *     VERIFY_PROPERTY_2, etc. to enable each requirement's checks.
 *   - Do NOT define them here in the code.
 *   - Use ESBMC (or a similar model checker) to run verification on this code.
 *
 *   e.g., esbmc ert_main.c -DVERIFY_PROPERTY_1
 *
 * Note: This example is illustrative and may require adaptation for actual 
 *       integration with your environment and toolchain.
 */

#include <math.h>
#include <stdio.h>
#include "swim_12B.h"  /* Include the generated code header */

/* ESBMC-style nondeterministic booleans/doubles. 
   The actual signatures may differ depending on your environment. */
_Bool nondet_bool(void);
double nondet_double(void);



int main(void)
{
  /*
   * We store "previous" cycle states in non-static globals (or locals),
   * to confirm that the generated code is indeed preserving them 
   * through its rtDW.UnitDelay_DSTATE variables, etc.
   */
  double old_ASWarningAllowed   = 0.0; /* For rtDW.UnitDelay_DSTATE   */
  double old_LowSpeedWarn       = 0.0; /* For rtDW.UnitDelay_DSTATE_d */

  /* Initialize the model once before the loop. */
  swim_12B_initialize();

  /* Run a bounded loop to simulate multiple step cycles. */
  for (int i = 0; i < 10; i++)
  {
    /*
     * Nondeterministically choose input values each iteration.
     * Adjust or constrain them as needed for your environment.
     */
    rtU.diGet_S_CatSwitchPosition        = (nondet_bool()) ? 0 : 1;  /* 0 => CAT I, 1 => CAT III */
    rtU.muxGet_T_Mux_AircraftGrossWeigh  = nondet_double();         /* e.g., must be >= 0 in reality */
    rtU.diGet_S_LandingGearAltFlap       = nondet_bool();
    rtU.E_AI_IMPACT_PRESSURE             = nondet_double();         /* e.g., must be >= 0 in reality */
    rtU.muxGet_T_Mux_AirspeedMonitorEna  = nondet_bool();
    rtU.cvGet_V_AgcasLowSpeedWarn        = nondet_bool();
    rtU.olcGet_AgcasInterlocks           = nondet_bool();

    /* Step the model (one cycle) */
    swim_12B_step();

    /*
     * REQUIREMENT 1:
     * "The SWIM Airspeed algorithm shall output the minimum AGCAS airspeed 
     *  required to perform a 2g flyup as follows:
     *   IF CAT I,  Auto GCAS Minimum Vcas (knots) = 1.25921 * sqrt(GW) + 10.0
     *   IF CAT III,Auto GCAS Minimum Vcas (knots) = 1.33694 * sqrt(GW) + 10.0"
     */
#ifdef VERIFY_PROPERTY_1
    if (rtU.diGet_S_CatSwitchPosition == 0) {
      /* CAT I */
      double expectedCatI = 1.25921 * sqrt(rtU.muxGet_T_Mux_AircraftGrossWeigh) + 10.0;
      /* Using a small tolerance for floating-point comparison */
      __ESBMC_assert(
        fabs(rtY.SWIM_CalAirspeedmin_kts - expectedCatI) < 1e-5,
        "REQ1 (CAT I) violated: SWIM_CalAirspeedmin_kts mismatch"
      );
    } else {
      /* CAT III */
      double expectedCatIII = 1.33694 * sqrt(rtU.muxGet_T_Mux_AircraftGrossWeigh) + 10.0;
      __ESBMC_assert(
        fabs(rtY.SWIM_CalAirspeedmin_kts - expectedCatIII) < 1e-5,
        "REQ1 (CAT III) violated: SWIM_CalAirspeedmin_kts mismatch"
      );
    }
#endif /* VERIFY_PROPERTY_1 */


    /*
     * REQUIREMENT 2 (Logic-based with state):
     * "When a low speed warning is allowed, as computed by the SWIM Airspeed 
     *  algorithm, a low speed warning shall be true when the vehicle air data 
     *  impact pressure is less than the warning trigger for minimum impact 
     *  pressure in which a safe AGCAS evasive maneuver can be accomplished."
     *
     * Also includes verifying that the previous state is retained if conditions 
     * are not met for update.
     */
#ifdef VERIFY_PROPERTY_2

    /* 
     * PART A: Check the "SWIM_ASWarningAllowed" state retention or update.
     * Condition for setting SWIM_ASWarningAllowed = 1.0 is:
     *   if (diGet_S_LandingGearAltFlap == true) AND
     *      (E_AI_IMPACT_PRESSURE > SWIM_Qcmin_lbspft2),
     *   else remain old.
     */
    {
      _Bool conditionForASWarn =
        rtU.diGet_S_LandingGearAltFlap &&
        (rtU.E_AI_IMPACT_PRESSURE > rtY.swimGet_QcMinEnable_lbspft2);

      if (!conditionForASWarn) {
        /* If it should not be set anew, it must remain the same as last cycle. */
        __ESBMC_assert(
          rtY.SWIM_ASWarningAllowed == old_ASWarningAllowed,
          "REQ2 (ASWarningAllowed) state not retained correctly"
        );
      } else {
        /* If the condition is true, we expect it set to 1.0. 
           (Though the real code might also allow it to remain 1.0 from before;
            we check at least that it is not incorrectly 0.0 if it was triggered.) */
        __ESBMC_assert(
          rtY.SWIM_ASWarningAllowed == 1.0,
          "REQ2 (ASWarningAllowed) should be set to 1.0 under trigger condition"
        );
      }
    }

    /*
     * PART B: Check the "swimGet_AgcasLowSpeedWarn" update logic:
     *   1) The enabling condition is:
     *      ( (muxGet_T_Mux_AirspeedMonitorEna OR cvGet_V_AgcasLowSpeedWarn)
     *        AND (!olcGet_AgcasInterlocks)
     *        AND (SWIM_ASWarningAllowed == 1.0) ).
     *   2) If enabled, then "swimGet_AgcasLowSpeedWarn = (E_AI_IMPACT_PRESSURE < (SWIM_Qcmin_lbspft2 - 28.72))"
     *   3) Otherwise, it remains the previous value.
     */
    {
      _Bool enableCondition = (_Bool)(
        (rtU.muxGet_T_Mux_AirspeedMonitorEna || rtU.cvGet_V_AgcasLowSpeedWarn) &&
        (!rtU.olcGet_AgcasInterlocks) &&
        (rtY.SWIM_ASWarningAllowed == 1.0)
      );
      double threshold = rtY.swimGet_QcMinEnable_lbspft2 - 28.72;

      if (!enableCondition) {
        /* If it's not enabled, it must retain its previous value. */
        __ESBMC_assert(
          rtY.swimGet_AgcasLowSpeedWarn == old_LowSpeedWarn,
          "REQ2 (LowSpeedWarn) state not retained correctly"
        );
      } else {
        /* If it's enabled, check if E_AI_IMPACT_PRESSURE < threshold => must be 1.0,
           else it remains the previous cycle's value. */
        if (rtU.E_AI_IMPACT_PRESSURE < threshold) {
          __ESBMC_assert(
            rtY.swimGet_AgcasLowSpeedWarn == 1.0,
            "REQ2: Low speed warning shall be true under threshold condition"
          );
        } else {
          /* If not below threshold, it remains old. */
          __ESBMC_assert(
            rtY.swimGet_AgcasLowSpeedWarn == old_LowSpeedWarn,
            "REQ2 (LowSpeedWarn) should not change if impact pressure >= threshold"
          );
        }
      }
    }
#endif /* VERIFY_PROPERTY_2 */

    /*
     * Update "old" states to see if the next iteration 
     * preserves them correctly (per requirement).
     */
    old_ASWarningAllowed = rtY.SWIM_ASWarningAllowed;
    old_LowSpeedWarn     = rtY.swimGet_AgcasLowSpeedWarn;
  } /* end for */

  return 0;
}
