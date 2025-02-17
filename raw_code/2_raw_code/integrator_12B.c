/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: integrator_12B.c
 *
 * Code generated for Simulink model 'integrator_12B'.
 *
 * Model version                  : 1.30
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Sun Nov  3 11:37:02 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 10
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "integrator_12B.h"
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
void integrator_12B_step(void)
{
  real_T rtb_Switch;
  real_T rtb_Switch1;
  boolean_T rtb_RelationalOperator;

  /* RelationalOperator: '<S3>/Relational Operator' incorporates:
   *  Inport: '<Root>/BL'
   *  Inport: '<Root>/TL'
   */
  rtb_RelationalOperator = (rtU.TL < rtU.BL);

  /* Switch: '<S3>/Switch1' incorporates:
   *  Inport: '<Root>/BL'
   *  Inport: '<Root>/TL'
   */
  if (rtb_RelationalOperator) {
    rtb_Switch1 = rtU.BL;
  } else {
    rtb_Switch1 = rtU.TL;
  }

  /* End of Switch: '<S3>/Switch1' */

  /* Switch: '<S1>/Switch' incorporates:
   *  Gain: '<S1>/Gain'
   *  Inport: '<Root>/T'
   *  Inport: '<Root>/ic'
   *  Inport: '<Root>/reset'
   *  Inport: '<Root>/xin'
   *  Product: '<S1>/Product'
   *  Sum: '<S1>/Sum'
   *  Sum: '<S1>/Sum1'
   *  UnitDelay: '<S1>/Unit Delay'
   *  UnitDelay: '<S1>/Unit Delay1'
   */
  if (rtU.reset) {
    rtb_Switch = rtU.ic;
  } else {
    rtb_Switch = (rtU.cmd + rtDW.UnitDelay_DSTATE) * 0.5 * rtU.T +
      rtDW.UnitDelay1_DSTATE;
  }

  /* End of Switch: '<S1>/Switch' */

  /* Switch: '<S2>/Switch2' incorporates:
   *  RelationalOperator: '<S2>/LowerRelop1'
   */
  if (!(rtb_Switch > rtb_Switch1)) {
    /* Switch: '<S3>/Switch2' incorporates:
     *  Inport: '<Root>/BL'
     *  Inport: '<Root>/TL'
     */
    if (rtb_RelationalOperator) {
      rtb_Switch1 = rtU.TL;
    } else {
      rtb_Switch1 = rtU.BL;
    }

    /* End of Switch: '<S3>/Switch2' */

    /* Switch: '<S2>/Switch' incorporates:
     *  RelationalOperator: '<S2>/UpperRelop'
     */
    if (!(rtb_Switch < rtb_Switch1)) {
      rtb_Switch1 = rtb_Switch;
    }

    /* End of Switch: '<S2>/Switch' */
  }

  /* End of Switch: '<S2>/Switch2' */

  /* Outport: '<Root>/yout' */
  rtY.yout = rtb_Switch1;

  /* Update for UnitDelay: '<S1>/Unit Delay1' */
  rtDW.UnitDelay1_DSTATE = rtb_Switch1;

  /* Update for UnitDelay: '<S1>/Unit Delay' incorporates:
   *  Inport: '<Root>/xin'
   */
  rtDW.UnitDelay_DSTATE = rtU.cmd;
}

/* Model initialize function */
void integrator_12B_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
