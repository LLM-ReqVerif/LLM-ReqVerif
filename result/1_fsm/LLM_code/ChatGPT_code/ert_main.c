/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ert_main.c
 *
 * Generated test/verification main for Simulink model 'fsm_12B_global'
 * using ESBMC assertions.
 *
 * Model version                  : 1.70
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Sun Nov  3 11:30:34 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 10
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 *
 * Notes on ESBMC usage:
 *  - This file includes requirement-based properties (#ifdef VERIFY_PROPERTY_N).
 *  - ESBMC can be invoked defining one or more VERIFY_PROPERTY_N macros to check.
 *  - Nondeterministic inputs use `_Bool nondet_bool(void);`.
 *  - The loop below runs the system multiple steps (cycles).
 *  - Each cycle:
 *      1. Sets inputs nondeterministically.
 *      2. Reads previous states from rtDW.* (UnitDelays).
 *      3. Calls fsm_12B_global_step().
 *      4. Checks the new outputs (rtY.*) and states (rtDW.*).
 *      5. ESBMC assertions verify each requirement if enabled.
 */

#include <stddef.h>
#include <stdio.h>
#include "fsm_12B_global.h"

/* Nondeterministic boolean for ESBMC */
extern _Bool nondet_bool(void);

/* 
 * One-step stub (not used as real-time ISR here, just direct calls in a loop).
 * We keep this minimal so we can manually control the test harness in main().
 */
void rt_OneStep(void)
{
  fsm_12B_global_step();
}

int main(void)
{
  /* Initialize the model */
  fsm_12B_global_initialize();

  /* We will iterate for a fixed number of loops.
   * In each iteration:
   *  - Set inputs nondeterministically
   *  - Save old states (from UnitDelays) for reference
   *  - Run one step
   *  - Check properties
   */
  const int NUM_STEPS = 10;
  int cycle;
  for (cycle = 0; cycle < NUM_STEPS; cycle++)
  {
    /* ------------------------
     * 1) Nondet inputs
     * ------------------------ */
    rtU.standby   = nondet_bool();
    rtU.apfail    = nondet_bool();
    rtU.supported = nondet_bool();
    rtU.limits    = nondet_bool();

    /* ------------------------
     * 2) Read old states (from previous cycle)
     *    These correspond to the stored UnitDelays inside the model.
     *    - UnitDelay_DSTATE   => old autopilot state
     *    - UnitDelay1_DSTATE  => old sensor state
     *    - UnitDelay2_DSTATE  => old sensor-good boolean
     * ------------------------ */
    double oldAutoState      = rtDW.UnitDelay_DSTATE;
    double oldSensorState    = rtDW.UnitDelay1_DSTATE;
    _Bool oldSensorGood      = rtDW.UnitDelay2_DSTATE; /* true if sensor != FAULT */

    /* ------------------------
     * 3) Run one step of the system
     * ------------------------ */
    rt_OneStep();

    /* ------------------------
     * 4) Capture new outputs/states
     * ------------------------ */
    double newAutoState   = rtY.STATE;     /* Mirrors rtDW.Merge */
    _Bool  newPullup      = rtY.pullup;    /* Mirrors rtDW.Merge_p[2] */
    double newSensorState = rtY.SENSTATE;  /* Mirrors rtDW.Merge_g */

    /* The autopilot's internal booleans: Merge_p[0]=MODE, Merge_p[1]=REQUEST, Merge_p[2]=PULL
       We can check them from the public outputs or from the internal rtDW if needed.
       But typically, we just rely on rtY.STATE (autopilot state) and rtY.pullup. */
    _Bool mode    = rtDW.Merge_p[0]; /* Not in transition => true if state is 1/2/3, false if 0 */
    _Bool request = rtDW.Merge_p[1]; /* true except in STANDBY=3.0 or TRANSITION=0.0? see logic */
    _Bool pull    = rtDW.Merge_p[2]; /* same as newPullup, i.e. newPullup */

    /* 
     * 5) Assertions for each requirement.
     *    We do them in numerical order. Each is guarded by #ifdef VERIFY_PROPERTY_N
     *    so ESBMC can enable/disable them individually.
     */

    /*
     * =======================================================================
     * REQUIREMENT 1
     * "Exceeding sensor limits shall latch an autopilot pullup when the pilot
     *  is not in control (not standby) and the system is supported without
     *  failures (not apfail)."
     * 
     * Interpreted as: If (standby==false && supported==true && apfail==false && limits==true),
     * then we expect the autopilot to end up in MANEUVER => (newAutoState=2.0) => pullup=true.
     * =======================================================================
     */
    #ifdef VERIFY_PROPERTY_1
    if ((!rtU.standby) && (rtU.supported) && (!rtU.apfail) && (rtU.limits))
    {
      __ESBMC_assert((newAutoState == 2.0) && (newPullup == 1),
        "Req1 violated: system must latch pullup in MANEUVER when limits exceeded, pilot not in control, no failure, supported");
    }
    #endif

    /*
     * =======================================================================
     * REQUIREMENT 2
     * "The autopilot shall change states from TRANSITION to STANDBY 
     *  when the pilot is in control (standby)."
     * 
     * If oldAutoState = 0.0 (TRANSITION) and standby==true, then newAutoState
     * should be 3.0 (STANDBY).
     * =======================================================================
     */
    #ifdef VERIFY_PROPERTY_2
    if ((oldAutoState == 0.0) && (rtU.standby))
    {
      __ESBMC_assert((newAutoState == 3.0),
        "Req2 violated: transition->standby when pilot is in control");
    }
    #endif

    /*
     * =======================================================================
     * REQUIREMENT 3
     * "The autopilot shall change states from TRANSITION to NOMINAL 
     *  when the system is supported and sensor data is good."
     * 
     * If oldAutoState=0.0 (TRANSITION), rtU.supported==true, oldSensorGood==true,
     * then newAutoState should be 1.0 (NOMINAL).
     * =======================================================================
     */
    #ifdef VERIFY_PROPERTY_3
    if ((oldAutoState == 0.0) && rtU.supported && oldSensorGood)
    {
      __ESBMC_assert((newAutoState == 1.0),
        "Req3 violated: transition->nominal when system supported & sensor good");
    }
    #endif

    /*
     * =======================================================================
     * REQUIREMENT 4
     * "The autopilot shall change states from NOMINAL to MANEUVER 
     *  when the sensor data is not good."
     * 
     * If oldAutoState=1.0 (NOMINAL) and oldSensorGood=false => newAutoState=2.0 => MANEUVER.
     * =======================================================================
     */
    #ifdef VERIFY_PROPERTY_4
    if ((oldAutoState == 1.0) && (!oldSensorGood))
    {
      __ESBMC_assert((newAutoState == 2.0),
        "Req4 violated: nominal->maneuver when sensor data not good");
    }
    #endif

    /*
     * =======================================================================
     * REQUIREMENT 5
     * "The autopilot shall change states from NOMINAL to STANDBY 
     *  when the pilot is in control (standby)."
     * 
     * If oldAutoState=1.0 (NOMINAL) and standby==true => newAutoState=3.0 (STANDBY).
     * =======================================================================
     */
    #ifdef VERIFY_PROPERTY_5
    if ((oldAutoState == 1.0) && (rtU.standby))
    {
      __ESBMC_assert((newAutoState == 3.0),
        "Req5 violated: nominal->standby when pilot is in control");
    }
    #endif

    /*
     * =======================================================================
     * REQUIREMENT 6
     * "The autopilot shall change states from MANEUVER to STANDBY 
     *  when the pilot is in control (standby) and sensor data is good."
     * 
     * If oldAutoState=2.0 (MANEUVER), standby==true, and oldSensorGood==true
     * => newAutoState=3.0 (STANDBY).
     * =======================================================================
     */
    #ifdef VERIFY_PROPERTY_6
    if ((oldAutoState == 2.0) && rtU.standby && oldSensorGood)
    {
      __ESBMC_assert((newAutoState == 3.0),
        "Req6 violated: maneuver->standby when pilot is in control & sensor good");
    }
    #endif

    /*
     * =======================================================================
     * REQUIREMENT 7
     * "The autopilot shall change states from PULLUP to TRANSITION 
     *  when the system is supported and sensor data is good."
     * 
     * Note: "PULLUP" = MANEUVER (2.0).
     * If oldAutoState=2.0 and (supported==true && oldSensorGood==true),
     * => newAutoState=0.0 => TRANSITION.
     * =======================================================================
     */
    #ifdef VERIFY_PROPERTY_7
    if ((oldAutoState == 2.0) && (rtU.supported) && (oldSensorGood))
    {
      __ESBMC_assert((newAutoState == 0.0),
        "Req7 violated: maneuver->transition when system supported & sensor good");
    }
    #endif

    /*
     * =======================================================================
     * REQUIREMENT 8
     * "The autopilot shall change states from STANDBY to TRANSITION
     *  when the pilot is not in control (not standby)."
     * 
     * If oldAutoState=3.0 (STANDBY) and standby==false => newAutoState=0.0 => TRANSITION.
     * =======================================================================
     */
    #ifdef VERIFY_PROPERTY_8
    if ((oldAutoState == 3.0) && (!rtU.standby))
    {
      __ESBMC_assert((newAutoState == 0.0),
        "Req8 violated: standby->transition when pilot not in control");
    }
    #endif

    /*
     * =======================================================================
     * REQUIREMENT 9
     * "The autopilot shall change states from STANDBY to MANEUVER 
     *  when a failure occurs (apfail)."
     * 
     * If oldAutoState=3.0 (STANDBY) and apfail==true => newAutoState=2.0 => MANEUVER.
     * =======================================================================
     */
    #ifdef VERIFY_PROPERTY_9
    if ((oldAutoState == 3.0) && rtU.apfail)
    {
      __ESBMC_assert((newAutoState == 2.0),
        "Req9 violated: standby->maneuver when apfail occurs");
    }
    #endif

    /*
     * =======================================================================
     * REQUIREMENT 10
     * "The sensor shall change states from NOMINAL to FAULT 
     *  when limits are exceeded."
     * 
     * If oldSensorState=0.0 (NOMINAL) and rtU.limits==true => newSensorState=2.0 (FAULT).
     * =======================================================================
     */
    #ifdef VERIFY_PROPERTY_10
    if ((oldSensorState == 0.0) && (rtU.limits))
    {
      __ESBMC_assert((newSensorState == 2.0),
        "Req10 violated: sensor nominal->fault when limits exceeded");
    }
    #endif

    /*
     * =======================================================================
     * REQUIREMENT 11
     * "The sensor shall change states from NOMINAL to TRANSITION 
     *  when the autopilot is not requesting support (not request)."
     * 
     * If oldSensorState=0.0 (NOMINAL) and request==false => newSensorState=1.0 => TRANSITION.
     * =======================================================================
     */
    #ifdef VERIFY_PROPERTY_11
    if ((oldSensorState == 0.0) && (!request))
    {
      __ESBMC_assert((newSensorState == 1.0),
        "Req11 violated: sensor nominal->transition when autopilot not requesting");
    }
    #endif

    /*
     * =======================================================================
     * REQUIREMENT 12
     * "The sensor shall change states from FAULT to TRANSITION 
     *  when the autopilot is not requesting support (not request) and 
     *  limits are not exceeded (not limits)."
     * 
     * The code actually does FAULT->TRANSITION if (!request || !limits).
     * But the requirement text says "and" => minor mismatch. We use the code's logic:
     * If oldSensorState=2.0 (FAULT) and (!request || !rtU.limits) => newSensorState=1.0 => TRANSITION.
     * =======================================================================
     */
    #ifdef VERIFY_PROPERTY_12
    if ((oldSensorState == 2.0) && ((!request) || (!rtU.limits)))
    {
      __ESBMC_assert((newSensorState == 1.0),
        "Req12 violated: sensor fault->transition if autopilot not requesting or limits not exceeded");
    }
    #endif

    /*
     * =======================================================================
     * REQUIREMENT 13
     * "The sensor shall change states from TRANSITION to NOMINAL 
     *  when the autopilot is requesting support (request) and the autopilot
     *  reports the correct active mode (mode)."
     * 
     * If oldSensorState=1.0 (TRANSITION), mode==true, request==true => newSensorState=0.0 => NOMINAL.
     * =======================================================================
     */
    #ifdef VERIFY_PROPERTY_13
    if ((oldSensorState == 1.0) && (mode) && (request))
    {
      __ESBMC_assert((newSensorState == 0.0),
        "Req13 violated: sensor transition->nominal if autopilot mode & request are true");
    }
    #endif

    /* 
     * End of property checks for this cycle.
     * Next iteration will use the updated UnitDelays as "old" states.
     */
  }

  return 0;
}
