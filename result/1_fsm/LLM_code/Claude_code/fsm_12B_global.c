/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: fsm_12B_global.c
 *
 * Code generated for Simulink model 'fsm_12B_global'.
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
 */

#include "fsm_12B_global.h"
#include "rtwtypes.h"

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;

/* Model step function */
void fsm_12B_global_step(void)
{
  real_T rtb_UnitDelay;

  /* UnitDelay: '<S1>/Unit Delay' */
  rtb_UnitDelay = rtDW.UnitDelay_DSTATE;

  /* If: '<S4>/If' */
  if (rtb_UnitDelay == 0.0) {
    /* Outputs for IfAction SubSystem: '<S4>/Transition' incorporates:
     *  ActionPort: '<S9>/Action Port'
     */
    /* Switch: '<S9>/Switch2' incorporates:
     *  Inport: '<Root>/standby'
     *  Inport: '<Root>/supported'
     *  Logic: '<S9>/Logical Operator12'
     *  Switch: '<S9>/Switch1'
     *  UnitDelay: '<S1>/Unit Delay2'
     */
    if (rtU.standby) {
      /* Merge: '<S4>/Merge' incorporates:
       *  Constant: '<S9>/Constant1'
       */
      rtDW.Merge = 3.0;
    } else if (rtU.supported && rtDW.UnitDelay2_DSTATE) {
      /* Switch: '<S9>/Switch1' incorporates:
       *  Constant: '<S9>/Constant7'
       *  Merge: '<S4>/Merge'
       */
      rtDW.Merge = 1.0;
    } else {
      /* Merge: '<S4>/Merge' incorporates:
       *  Switch: '<S9>/Switch1'
       */
      rtDW.Merge = rtb_UnitDelay;
    }

    /* End of Switch: '<S9>/Switch2' */
    /* End of Outputs for SubSystem: '<S4>/Transition' */
  } else if (rtb_UnitDelay == 1.0) {
    /* Outputs for IfAction SubSystem: '<S4>/Nominal' incorporates:
     *  ActionPort: '<S7>/Action Port'
     */
    /* Switch: '<S7>/Switch2' incorporates:
     *  Inport: '<Root>/standby'
     *  Logic: '<S7>/Logical Operator12'
     *  Switch: '<S7>/Switch1'
     *  UnitDelay: '<S1>/Unit Delay2'
     */
    if (rtU.standby) {
      /* Merge: '<S4>/Merge' incorporates:
       *  Constant: '<S7>/Constant1'
       */
      rtDW.Merge = 3.0;
    } else if (!rtDW.UnitDelay2_DSTATE) {
      /* Switch: '<S7>/Switch1' incorporates:
       *  Constant: '<S7>/Constant7'
       *  Merge: '<S4>/Merge'
       */
      rtDW.Merge = 2.0;
    } else {
      /* Merge: '<S4>/Merge' incorporates:
       *  Switch: '<S7>/Switch1'
       */
      rtDW.Merge = 1.0;
    }

    /* End of Switch: '<S7>/Switch2' */
    /* End of Outputs for SubSystem: '<S4>/Nominal' */
  } else if (rtb_UnitDelay == 2.0) {
    /* Outputs for IfAction SubSystem: '<S4>/Maneuver' incorporates:
     *  ActionPort: '<S6>/Action Port'
     */
    /* Switch: '<S6>/Switch2' incorporates:
     *  Inport: '<Root>/standby'
     *  Inport: '<Root>/supported'
     *  Logic: '<S6>/Logical Operator1'
     *  Logic: '<S6>/Logical Operator12'
     *  Switch: '<S6>/Switch1'
     *  UnitDelay: '<S1>/Unit Delay2'
     */
    if (rtU.standby && rtDW.UnitDelay2_DSTATE) {
      /* Merge: '<S4>/Merge' incorporates:
       *  Constant: '<S6>/Constant1'
       */
      rtDW.Merge = 3.0;
    } else if (rtU.supported && rtDW.UnitDelay2_DSTATE) {
      /* Switch: '<S6>/Switch1' incorporates:
       *  Constant: '<S6>/Constant7'
       *  Merge: '<S4>/Merge'
       */
      rtDW.Merge = 0.0;
    } else {
      /* Merge: '<S4>/Merge' incorporates:
       *  Switch: '<S6>/Switch1'
       */
      rtDW.Merge = 2.0;
    }

    /* End of Switch: '<S6>/Switch2' */
    /* End of Outputs for SubSystem: '<S4>/Maneuver' */
  } else if (rtb_UnitDelay == 3.0) {
    /* Outputs for IfAction SubSystem: '<S4>/Standby' incorporates:
     *  ActionPort: '<S8>/Action Port'
     */
    /* Switch: '<S8>/Switch2' incorporates:
     *  Inport: '<Root>/apfail'
     *  Inport: '<Root>/standby'
     *  Logic: '<S8>/Logical Operator12'
     *  Switch: '<S8>/Switch1'
     */
    if (rtU.apfail) {
      /* Merge: '<S4>/Merge' incorporates:
       *  Constant: '<S8>/Constant1'
       */
      rtDW.Merge = 2.0;
    } else if (!rtU.standby) {
      /* Switch: '<S8>/Switch1' incorporates:
       *  Constant: '<S8>/Constant7'
       *  Merge: '<S4>/Merge'
       */
      rtDW.Merge = 0.0;
    } else {
      /* Merge: '<S4>/Merge' incorporates:
       *  Switch: '<S8>/Switch1'
       */
      rtDW.Merge = 3.0;
    }

    /* End of Switch: '<S8>/Switch2' */
    /* End of Outputs for SubSystem: '<S4>/Standby' */
  }

  /* End of If: '<S4>/If' */

  /* UnitDelay: '<S1>/Unit Delay1' */
  rtb_UnitDelay = rtDW.UnitDelay1_DSTATE;

  /* If: '<S5>/If' incorporates:
   *  Constant: '<S10>/Constant10'
   *  Constant: '<S10>/Constant11'
   *  Constant: '<S10>/Constant9'
   *  Constant: '<S11>/Constant3'
   *  Constant: '<S11>/Constant4'
   *  Constant: '<S11>/Constant5'
   *  Constant: '<S12>/Constant1'
   *  Constant: '<S12>/Constant11'
   *  Constant: '<S12>/Constant9'
   *  Constant: '<S13>/Constant16'
   *  Constant: '<S13>/Constant17'
   *  Constant: '<S13>/Constant18'
   *  Merge: '<S5>/Merge'
   */
  if (rtDW.Merge == 0.0) {
    /* Outputs for IfAction SubSystem: '<S5>/Transition' incorporates:
     *  ActionPort: '<S13>/Action Port'
     */
    rtDW.Merge_p[0] = false;
    rtDW.Merge_p[1] = true;
    rtDW.Merge_p[2] = false;

    /* End of Outputs for SubSystem: '<S5>/Transition' */
  } else if (rtDW.Merge == 1.0) {
    /* Outputs for IfAction SubSystem: '<S5>/Nominal' incorporates:
     *  ActionPort: '<S11>/Action Port'
     */
    rtDW.Merge_p[0] = true;
    rtDW.Merge_p[1] = true;
    rtDW.Merge_p[2] = false;

    /* End of Outputs for SubSystem: '<S5>/Nominal' */
  } else if (rtDW.Merge == 2.0) {
    /* Outputs for IfAction SubSystem: '<S5>/Maneuver' incorporates:
     *  ActionPort: '<S10>/Action Port'
     */
    rtDW.Merge_p[1] = true;
    rtDW.Merge_p[2] = true;
    rtDW.Merge_p[0] = true;

    /* End of Outputs for SubSystem: '<S5>/Maneuver' */
  } else if (rtDW.Merge == 3.0) {
    /* Outputs for IfAction SubSystem: '<S5>/Standby' incorporates:
     *  ActionPort: '<S12>/Action Port'
     */
    rtDW.Merge_p[1] = false;
    rtDW.Merge_p[2] = false;
    rtDW.Merge_p[0] = true;

    /* End of Outputs for SubSystem: '<S5>/Standby' */
  }

  /* End of If: '<S5>/If' */

  /* If: '<S14>/If' */
  if (rtb_UnitDelay == 0.0) {
    /* Outputs for IfAction SubSystem: '<S14>/Nominal' incorporates:
     *  ActionPort: '<S17>/Action Port'
     */
    /* Switch: '<S17>/Switch2' incorporates:
     *  Inport: '<Root>/limits'
     *  Logic: '<S17>/Logical Operator12'
     *  Switch: '<S17>/Switch1'
     */
    if (rtU.limits) {
      /* Merge: '<S14>/Merge' incorporates:
       *  Constant: '<S17>/Constant1'
       */
      rtDW.Merge_g = 2.0;
    } else if (!rtDW.Merge_p[1]) {
      /* Switch: '<S17>/Switch1' incorporates:
       *  Constant: '<S17>/Constant7'
       *  Merge: '<S14>/Merge'
       */
      rtDW.Merge_g = 1.0;
    } else {
      /* Merge: '<S14>/Merge' incorporates:
       *  Switch: '<S17>/Switch1'
       */
      rtDW.Merge_g = rtb_UnitDelay;
    }

    /* End of Switch: '<S17>/Switch2' */
    /* End of Outputs for SubSystem: '<S14>/Nominal' */
  } else if (rtb_UnitDelay == 1.0) {
    /* Outputs for IfAction SubSystem: '<S14>/Transition' incorporates:
     *  ActionPort: '<S18>/Action Port'
     */
    /* Switch: '<S18>/Switch1' incorporates:
     *  Logic: '<S18>/Logical Operator12'
     */
    if (rtDW.Merge_p[0] && rtDW.Merge_p[1]) {
      /* Merge: '<S14>/Merge' incorporates:
       *  Constant: '<S18>/Constant7'
       *  SignalConversion: '<S18>/Signal Conversion'
       */
      rtDW.Merge_g = 0.0;
    } else {
      /* Merge: '<S14>/Merge' incorporates:
       *  SignalConversion: '<S18>/Signal Conversion'
       */
      rtDW.Merge_g = 1.0;
    }

    /* End of Switch: '<S18>/Switch1' */
    /* End of Outputs for SubSystem: '<S14>/Transition' */
  } else if (rtb_UnitDelay == 2.0) {
    /* Outputs for IfAction SubSystem: '<S14>/Fault' incorporates:
     *  ActionPort: '<S16>/Action Port'
     */
    /* Switch: '<S16>/Switch1' incorporates:
     *  Inport: '<Root>/limits'
     *  Logic: '<S16>/Logical Operator12'
     *  Logic: '<S16>/Logical Operator2'
     *  Logic: '<S16>/Logical Operator3'
     */
    if ((!rtDW.Merge_p[1]) || (!rtU.limits)) {
      /* Merge: '<S14>/Merge' incorporates:
       *  Constant: '<S16>/Constant7'
       *  SignalConversion: '<S16>/Signal Conversion'
       */
      rtDW.Merge_g = 1.0;
    } else {
      /* Merge: '<S14>/Merge' incorporates:
       *  SignalConversion: '<S16>/Signal Conversion'
       */
      rtDW.Merge_g = 2.0;
    }

    /* End of Switch: '<S16>/Switch1' */
    /* End of Outputs for SubSystem: '<S14>/Fault' */
  }

  /* End of If: '<S14>/If' */

  /* Outport: '<Root>/SENSTATE' */
  rtY.SENSTATE = rtDW.Merge_g;

  /* Outport: '<Root>/pullup' */
  rtY.pullup = rtDW.Merge_p[2];

  /* Outport: '<Root>/STATE' */
  rtY.STATE = rtDW.Merge;

  /* Update for UnitDelay: '<S1>/Unit Delay' */
  rtDW.UnitDelay_DSTATE = rtDW.Merge;

  /* Update for UnitDelay: '<S1>/Unit Delay2' incorporates:
   *  Constant: '<S15>/Constant6'
   *  RelationalOperator: '<S15>/Relational Operator5'
   */
  rtDW.UnitDelay2_DSTATE = !(rtDW.Merge_g == 2.0);

  /* Update for UnitDelay: '<S1>/Unit Delay1' */
  rtDW.UnitDelay1_DSTATE = rtDW.Merge_g;
}

/* Model initialize function */
void fsm_12B_global_initialize(void)
{
    rtDW.UnitDelay_DSTATE = 0.0;     
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
