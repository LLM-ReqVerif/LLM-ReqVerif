/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ert_main.c (Modified for ESBMC property verification)
 *
 * Code generated for Simulink model 'regs_12B' plus ESBMC assertions for
 * verifying the ten Inner Loop Regulator requirements. 
 *
 * Model version                  : 1.20
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Sun Nov  3 11:51:39 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 10
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include <stddef.h>
#include <stdio.h>
#include <math.h>    /* For fabs() */
#include "regs_12B.h"    /* Model header file */

/* Nondeterministic input prototypes for ESBMC */
_Bool nondet_bool(void);
double nondet_double(void);

/* ESBMC assertion macro is provided by the toolchain */
extern void __ESBMC_assert(_Bool, const char *);

/*=============================*/
/*       Configuration         */
/*=============================*/

/*
   We will run the model for a fixed number of loops (e.g. 200)
   and check the requirements on each iteration.
*/
#define MAX_ITERATIONS  200

/*
   Each requirement can be selectively verified by defining
   VERIFY_PROPERTY_n externally (e.g., -DVERIFY_PROPERTY_1).
   This file does NOT define them directly, in accordance with the request.
*/

/*=============================*/
/*       MAIN FUNCTION         */
/*=============================*/

int main(int argc, const char *argv[])
{
  (void)(argc);
  (void)(argv);

  /*
   * Local variables to keep track of previous cycle outputs (for
   * the transient change requirements #6-#10) and counters for
   * consecutive out-of-limit frames (for requirements #1-#5).
   */

  /* Previous step outputs (for rate-of-change checks) */
  double prev_lcvdt_cmd_fcs_dps2    = 0.0;
  double prev_mcvdt_cmd_fcs_dps2    = 0.0;
  double prev_ncvdt_cmd_fcs_dps2    = 0.0;
  double prev_xcvdt_cmd_fcs_fps2    = 0.0;
  double prev_hcvdt_cmd_fcs_fps2    = 0.0;

  /* Consecutive frames counter for out-of-limit magnitude (#1-#5) */
  int roll_accel_exceed_count       = 0;
  int pitch_accel_exceed_count      = 0;
  int yaw_accel_exceed_count        = 0;
  int axial_accel_exceed_count      = 0;
  int height_accel_exceed_count     = 0;

  /* Initialize the model */
  regs_12B_initialize();

  /* 
   * ESBMC generally tries all possible paths if inputs are nondet,
   * but we show how you could set inputs each iteration. If the user
   * wants pure nondeterminism, they might set them all to nondet_double()
   * in each loop below.
   */

  int i = 0;
  while ((rtmGetErrorStatus(rtM) == (NULL)) && (i < MAX_ITERATIONS))
  {
    /*
     * Optionally set or override inputs here each iteration:
     *
     * e.g.:
     * rtU.lcv_cmd_fcs_dps = nondet_double();
     * rtU.lcv_fps_dps     = nondet_double();
     * rtU.mcv_cmd_fcs_dps = nondet_double();
     * ...
     *
     * For demonstration, you could also fix them, or vary them, etc.
     * Below is purely illustrative (commented out). Uncomment if needed.
     */
    /*
    rtU.lcv_cmd_fcs_dps = nondet_double();
    rtU.lcv_fps_dps     = nondet_double();
    rtU.mcv_cmd_fcs_dps = nondet_double();
    rtU.mcv_fcs_dps     = nondet_double();
    rtU.ncv_cmd_fcs_dps = nondet_double();
    rtU.ncv_fcs_dps     = nondet_double();
    rtU.beta_adc_deg    = nondet_double();
    rtU.beta_dot        = nondet_double();
    rtU.vtas_adc_kts    = nondet_double();
    rtU.xcv_cmd_fcs_fps = nondet_double();
    rtU.dcv_fcs_fps     = nondet_double();
    rtU.hcv_cmd_fcs_fps = nondet_double();
    rtU.zcv_fcs_fps     = nondet_double();
    */

    /* Step the model (one cycle) */
    regs_12B_step();

    /*************************************************************************/
    /*          Verify Requirements #1-#5: Maximum acceleration limits       */
    /*   "Shall not exceed system capability for > 100 consecutive frames"   */
    /*************************************************************************/

    /* (1) Roll acceleration shall not exceed 50 deg/sec^2 for > 100 frames */
#ifdef VERIFY_PROPERTY_1
    if (fabs(rtY.lcvdt_cmd_fcs_dps2) > 50.0) {
      roll_accel_exceed_count++;
    } else {
      roll_accel_exceed_count = 0;  /* reset if back in range */
    }
    __ESBMC_assert(
      (roll_accel_exceed_count <= 100),
      "Requirement 1 violated: Roll accel > 50 deg/sec^2 for more than 100 consecutive frames."
    );
#endif

    /* (2) Pitch acceleration shall not exceed 50 deg/sec^2 for > 100 frames */
#ifdef VERIFY_PROPERTY_2
    if (fabs(rtY.mcvdt_cmd_fcs_dps2) > 50.0) {
      pitch_accel_exceed_count++;
    } else {
      pitch_accel_exceed_count = 0;
    }
    __ESBMC_assert(
      (pitch_accel_exceed_count <= 100),
      "Requirement 2 violated: Pitch accel > 50 deg/sec^2 for more than 100 consecutive frames."
    );
#endif

    /* (3) Yaw acceleration shall not exceed 50 deg/sec^2 for > 100 frames */
#ifdef VERIFY_PROPERTY_3
    if (fabs(rtY.ncvdt_cmd_fcs_dps2) > 50.0) {
      yaw_accel_exceed_count++;
    } else {
      yaw_accel_exceed_count = 0;
    }
    __ESBMC_assert(
      (yaw_accel_exceed_count <= 100),
      "Requirement 3 violated: Yaw accel > 50 deg/sec^2 for more than 100 consecutive frames."
    );
#endif

    /* (4) Airspeed (axial) acceleration shall not exceed 32 ft/sec^2 for > 100 frames */
#ifdef VERIFY_PROPERTY_4
    if (fabs(rtY.xcvdt_cmd_fcs_fps2) > 32.0) {
      axial_accel_exceed_count++;
    } else {
      axial_accel_exceed_count = 0;
    }
    __ESBMC_assert(
      (axial_accel_exceed_count <= 100),
      "Requirement 4 violated: Axial accel > 32 ft/sec^2 for more than 100 consecutive frames."
    );
#endif

    /* (5) Height acceleration shall not exceed 32 ft/sec^2 for > 100 frames */
#ifdef VERIFY_PROPERTY_5
    if (fabs(rtY.hcvdt_cmd_fcs_fps2) > 32.0) {
      height_accel_exceed_count++;
    } else {
      height_accel_exceed_count = 0;
    }
    __ESBMC_assert(
      (height_accel_exceed_count <= 100),
      "Requirement 5 violated: Height accel > 32 ft/sec^2 for more than 100 consecutive frames."
    );
#endif

    /****************************************************************************/
    /*     Verify Requirements #6-#10: Rate-of-change (transient) limits        */
    /*    "Shall not command changes in accel > limit from one frame to next"   */
    /****************************************************************************/

    /* (6) Roll acceleration rate-of-change <= 50 deg/sec^2/sec */
#ifdef VERIFY_PROPERTY_6
    {
      double delta_roll = rtY.lcvdt_cmd_fcs_dps2 - prev_lcvdt_cmd_fcs_dps2;
      __ESBMC_assert(
        (fabs(delta_roll) <= 50.0),
        "Requirement 6 violated: |ΔRoll accel| > 50 deg/sec^2/sec"
      );
    }
#endif

    /* (7) Pitch acceleration rate-of-change <= 50 deg/sec^2/sec */
#ifdef VERIFY_PROPERTY_7
    {
      double delta_pitch = rtY.mcvdt_cmd_fcs_dps2 - prev_mcvdt_cmd_fcs_dps2;
      __ESBMC_assert(
        (fabs(delta_pitch) <= 50.0),
        "Requirement 7 violated: |ΔPitch accel| > 50 deg/sec^2/sec"
      );
    }
#endif

    /* (8) Yaw acceleration rate-of-change <= 50 deg/sec^2/sec */
#ifdef VERIFY_PROPERTY_8
    {
      double delta_yaw = rtY.ncvdt_cmd_fcs_dps2 - prev_ncvdt_cmd_fcs_dps2;
      __ESBMC_assert(
        (fabs(delta_yaw) <= 50.0),
        "Requirement 8 violated: |ΔYaw accel| > 50 deg/sec^2/sec"
      );
    }
#endif

    /* (9) Axial acceleration rate-of-change <= 32 ft/sec^2/sec */
#ifdef VERIFY_PROPERTY_9
    {
      double delta_axial = rtY.xcvdt_cmd_fcs_fps2 - prev_xcvdt_cmd_fcs_fps2;
      __ESBMC_assert(
        (fabs(delta_axial) <= 32.0),
        "Requirement 9 violated: |ΔAxial accel| > 32 ft/sec^2/sec"
      );
    }
#endif

    /* (10) Height acceleration rate-of-change <= 32 ft/sec^2/sec */
#ifdef VERIFY_PROPERTY_10
    {
      double delta_height = rtY.hcvdt_cmd_fcs_fps2 - prev_hcvdt_cmd_fcs_fps2;
      __ESBMC_assert(
        (fabs(delta_height) <= 32.0),
        "Requirement 10 violated: |ΔHeight accel| > 32 ft/sec^2/sec"
      );
    }
#endif

    /*
     * Update "previous output" variables
     * AFTER we have done the checks above.
     */
    prev_lcvdt_cmd_fcs_dps2 = rtY.lcvdt_cmd_fcs_dps2;
    prev_mcvdt_cmd_fcs_dps2 = rtY.mcvdt_cmd_fcs_dps2;
    prev_ncvdt_cmd_fcs_dps2 = rtY.ncvdt_cmd_fcs_dps2;
    prev_xcvdt_cmd_fcs_fps2 = rtY.xcvdt_cmd_fcs_fps2;
    prev_hcvdt_cmd_fcs_fps2 = rtY.hcvdt_cmd_fcs_fps2;

    /*
     * Note on persistent states (rtDW.*):
     * They are updated at the end of regs_12B_step().
     * The next cycle uses the new rtDW.* values. 
     * We do not use static or global memory for these "prev" checks, 
     * just local variables as required.
     */

    i++;
  }

  /*
   * If we exit the loop due to i >= MAX_ITERATIONS, we stop normally;
   * if we exit because rtmGetErrorStatus(rtM) != NULL, the model
   * encountered an error or a user stop request.
   */
  return 0;
}

/*
 * File trailer for generated code + ESBMC property checks.
 *
 * [EOF]
 */
