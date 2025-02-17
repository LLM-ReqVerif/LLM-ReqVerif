/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: NLGuidance_12B.c
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

#include "NLGuidance_12B.h"
#include <math.h>
#include "rtwtypes.h"

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Model step function */
void NLGuidance_12B_step(void)
{
  real_T rtb_MathFunction1;
  real_T rtb_MathFunction_idx_0;
  real_T rtb_MathFunction_idx_1;
  real_T rtb_MathFunction_idx_2;
  real_T rtb_Product1;
  real_T rtb_Sum2;
  real_T rtb_Sum2_tmp;
  real_T rtb_Sum_c_idx_0;
  real_T rtb_Sum_c_idx_1;
  real_T rtb_Sum_c_idx_2;
  real_T rtb_XrDotVv;
  real_T rtb_Xr_idx_0;
  real_T rtb_Xr_idx_1;

  /* Sum: '<S1>/Sum' incorporates:
   *  Inport: '<Root>/Xtarg'
   *  Inport: '<Root>/Xv'
   */
  rtb_Product1 = rtU.Xtarg[0] - rtU.Xv[0];
  rtb_Xr_idx_0 = rtb_Product1;

  /* Math: '<S4>/Math Function' */
  rtb_MathFunction_idx_0 = rtb_Product1 * rtb_Product1;

  /* Sum: '<S1>/Sum' incorporates:
   *  Inport: '<Root>/Xtarg'
   *  Inport: '<Root>/Xv'
   */
  rtb_Product1 = rtU.Xtarg[1] - rtU.Xv[1];
  rtb_Xr_idx_1 = rtb_Product1;

  /* Math: '<S4>/Math Function' */
  rtb_MathFunction_idx_1 = rtb_Product1 * rtb_Product1;

  /* Sum: '<S1>/Sum' incorporates:
   *  Inport: '<Root>/Xtarg'
   *  Inport: '<Root>/Xv'
   */
  rtb_Product1 = rtU.Xtarg[2] - rtU.Xv[2];

  /* Sum: '<S4>/Sum of Elements' incorporates:
   *  Math: '<S4>/Math Function'
   */
  rtb_MathFunction_idx_0 = (rtb_MathFunction_idx_0 + rtb_MathFunction_idx_1) +
    rtb_Product1 * rtb_Product1;

  /* DotProduct: '<S1>/Dot Product' incorporates:
   *  Inport: '<Root>/Vv'
   *  Sum: '<S1>/Sum'
   */
  rtb_XrDotVv = (rtb_Xr_idx_0 * rtU.Vv[0] + rtb_Xr_idx_1 * rtU.Vv[1]) +
    rtb_Product1 * rtU.Vv[2];

  /* Math: '<S4>/Math Function1'
   *
   * About '<S4>/Math Function1':
   *  Operator: sqrt
   */
  if (rtb_MathFunction_idx_0 < 0.0) {
    rtb_MathFunction1 = -sqrt(fabs(rtb_MathFunction_idx_0));
  } else {
    rtb_MathFunction1 = sqrt(rtb_MathFunction_idx_0);
  }

  /* End of Math: '<S4>/Math Function1' */

  /* Outputs for IfAction SubSystem: '<S1>/Outer' incorporates:
   *  ActionPort: '<S3>/Action Port'
   */
  /* If: '<S1>/If' incorporates:
   *  Math: '<S15>/Math Function2'
   *  Math: '<S1>/Math Function1'
   *  Math: '<S1>/Math Function3'
   */
  rtb_Sum2_tmp = rtb_MathFunction1 * rtb_MathFunction1;

  /* End of Outputs for SubSystem: '<S1>/Outer' */

  /* Sum: '<S1>/Sum2' incorporates:
   *  Inport: '<Root>/r'
   *  Math: '<S1>/Math Function3'
   *  Math: '<S1>/Math Function4'
   */
  rtb_Sum2 = rtb_Sum2_tmp - rtU.r * rtU.r;

  /* Sum: '<S5>/Sum of Elements' incorporates:
   *  Inport: '<Root>/Vv'
   *  Math: '<S5>/Math Function'
   */
  rtb_MathFunction_idx_0 = (rtU.Vv[0] * rtU.Vv[0] + rtU.Vv[1] * rtU.Vv[1]) +
    rtU.Vv[2] * rtU.Vv[2];

  /* Math: '<S5>/Math Function1'
   *
   * About '<S5>/Math Function1':
   *  Operator: sqrt
   */
  if (rtb_MathFunction_idx_0 < 0.0) {
    rtb_MathFunction_idx_0 = -sqrt(fabs(rtb_MathFunction_idx_0));
  } else {
    rtb_MathFunction_idx_0 = sqrt(rtb_MathFunction_idx_0);
  }

  /* End of Math: '<S5>/Math Function1' */

  /* Sum: '<S1>/Sum1' incorporates:
   *  DotProduct: '<S1>/Dot Product'
   *  Math: '<S1>/Math Function'
   *  Math: '<S1>/Math Function2'
   *  Product: '<S1>/Product'
   */
  rtb_MathFunction_idx_0 = rtb_MathFunction_idx_0 * rtb_MathFunction_idx_0 *
    rtb_Sum2_tmp - rtb_XrDotVv * rtb_XrDotVv;

  /* If: '<S1>/If' incorporates:
   *  Constant: '<S1>/Constant1'
   *  Constant: '<S1>/Constant2'
   *  Logic: '<S1>/Logical Operator'
   *  RelationalOperator: '<S1>/Relational Operator'
   *  RelationalOperator: '<S1>/Relational Operator1'
   */
  if ((rtb_Sum2 <= 0.0) || (rtb_MathFunction_idx_0 <= 0.0)) {
    /* Outputs for IfAction SubSystem: '<S1>/Inner' incorporates:
     *  ActionPort: '<S2>/Action Port'
     */
    /* Product: '<S2>/Divide' incorporates:
     *  Inport: '<Root>/r'
     */
    rtb_Product1 = rtU.r / rtb_MathFunction1;

    /* Sum: '<S8>/Sum' incorporates:
     *  Inport: '<Root>/Xtarg'
     *  Product: '<S8>/Product'
     */
    rtb_XrDotVv = rtb_Product1 * rtb_Xr_idx_0 + rtU.Xtarg[0];

    /* Sum: '<S8>/Sum1' incorporates:
     *  Inport: '<Root>/Xtarg'
     *  Product: '<S8>/Product1'
     */
    rtb_Sum2 = rtb_Xr_idx_1 * rtb_Product1 + rtU.Xtarg[1];

    /* Sum: '<S8>/Sum2' incorporates:
     *  Inport: '<Root>/Xv'
     */
    rtb_MathFunction_idx_0 = rtb_XrDotVv - rtU.Xv[0];
    rtb_MathFunction_idx_1 = rtb_Sum2 - rtU.Xv[1];

    /* Math: '<S10>/Math Function' incorporates:
     *  Constant: '<S8>/Constant1'
     *  Inport: '<Root>/Xv'
     *  Math: '<S11>/Math Function'
     *  Sum: '<S8>/Sum2'
     */
    rtb_Sum2_tmp = (0.0 - rtU.Xv[2]) * (0.0 - rtU.Xv[2]);

    /* Sum: '<S10>/Sum of Elements' incorporates:
     *  Math: '<S10>/Math Function'
     */
    rtb_MathFunction1 = (rtb_MathFunction_idx_0 * rtb_MathFunction_idx_0 +
                         rtb_MathFunction_idx_1 * rtb_MathFunction_idx_1) +
      rtb_Sum2_tmp;

    /* Sum: '<S9>/Sum' incorporates:
     *  Gain: '<S2>/Gain'
     *  Inport: '<Root>/Xtarg'
     *  Product: '<S9>/Product'
     */
    rtb_Xr_idx_0 = -rtb_Product1 * rtb_Xr_idx_0 + rtU.Xtarg[0];

    /* Sum: '<S9>/Sum1' incorporates:
     *  Gain: '<S2>/Gain'
     *  Inport: '<Root>/Xtarg'
     *  Product: '<S9>/Product1'
     */
    rtb_Product1 = rtb_Xr_idx_1 * -rtb_Product1 + rtU.Xtarg[1];

    /* Sum: '<S9>/Sum2' incorporates:
     *  Inport: '<Root>/Xv'
     */
    rtb_MathFunction_idx_0 = rtb_Xr_idx_0 - rtU.Xv[0];
    rtb_MathFunction_idx_1 = rtb_Product1 - rtU.Xv[1];

    /* Sum: '<S11>/Sum of Elements' incorporates:
     *  Math: '<S11>/Math Function'
     */
    rtb_MathFunction_idx_0 = (rtb_MathFunction_idx_0 * rtb_MathFunction_idx_0 +
      rtb_MathFunction_idx_1 * rtb_MathFunction_idx_1) + rtb_Sum2_tmp;

    /* Math: '<S10>/Math Function1'
     *
     * About '<S10>/Math Function1':
     *  Operator: sqrt
     */
    if (rtb_MathFunction1 < 0.0) {
      rtb_Sum2_tmp = -sqrt(fabs(rtb_MathFunction1));
    } else {
      rtb_Sum2_tmp = sqrt(rtb_MathFunction1);
    }

    /* Math: '<S11>/Math Function1'
     *
     * About '<S11>/Math Function1':
     *  Operator: sqrt
     */
    if (rtb_MathFunction_idx_0 < 0.0) {
      rtb_Xr_idx_1 = -sqrt(fabs(rtb_MathFunction_idx_0));
    } else {
      rtb_Xr_idx_1 = sqrt(rtb_MathFunction_idx_0);
    }

    /* If: '<S2>/If' incorporates:
     *  Constant: '<S8>/Constant1'
     *  Math: '<S10>/Math Function1'
     *  Math: '<S11>/Math Function1'
     *  Outport: '<Root>/yout'
     *  RelationalOperator: '<S2>/Relational Operator1'
     *  SignalConversion generated from: '<S6>/cmd1'
     *  SignalConversion generated from: '<S7>/cmd2'
     *
     * About '<S10>/Math Function1':
     *  Operator: sqrt
     *
     * About '<S11>/Math Function1':
     *  Operator: sqrt
     */
    if (rtb_Sum2_tmp < rtb_Xr_idx_1) {
      /* Outputs for IfAction SubSystem: '<S2>/Act1' incorporates:
       *  ActionPort: '<S6>/Action Port'
       */
      rtY.yout[0] = rtb_XrDotVv;
      rtY.yout[1] = rtb_Sum2;

      /* End of Outputs for SubSystem: '<S2>/Act1' */
    } else {
      /* Outputs for IfAction SubSystem: '<S2>/Act2' incorporates:
       *  ActionPort: '<S7>/Action Port'
       */
      rtY.yout[0] = rtb_Xr_idx_0;
      rtY.yout[1] = rtb_Product1;

      /* End of Outputs for SubSystem: '<S2>/Act2' */
    }

    /* Outputs for IfAction SubSystem: '<S2>/Act2' incorporates:
     *  ActionPort: '<S7>/Action Port'
     */
    /* Outputs for IfAction SubSystem: '<S2>/Act1' incorporates:
     *  ActionPort: '<S6>/Action Port'
     */
    rtY.yout[2] = 0.0;

    /* End of If: '<S2>/If' */
    /* End of Outputs for SubSystem: '<S2>/Act1' */
    /* End of Outputs for SubSystem: '<S2>/Act2' */
    /* End of Outputs for SubSystem: '<S1>/Inner' */
  } else {
    /* Outputs for IfAction SubSystem: '<S1>/Outer' incorporates:
     *  ActionPort: '<S3>/Action Port'
     */
    /* Sqrt: '<S3>/Sqrt' incorporates:
     *  Product: '<S3>/Divide1'
     */
    rtb_Sum2 = sqrt(rtb_Sum2 / rtb_MathFunction_idx_0);

    /* Product: '<S15>/Product7' incorporates:
     *  Inport: '<Root>/Vv'
     */
    rtb_MathFunction_idx_0 = rtb_Sum2 * rtU.Vv[0];
    rtb_MathFunction_idx_1 = rtb_Sum2 * rtU.Vv[1];
    rtb_MathFunction_idx_2 = rtb_Sum2 * rtU.Vv[2];

    /* Product: '<S15>/Divide4' */
    rtb_MathFunction1 = 1.0 / rtb_Sum2_tmp;

    /* Product: '<S15>/Product2' incorporates:
     *  DotProduct: '<S1>/Dot Product'
     */
    rtb_Sum2 *= rtb_XrDotVv;

    /* Sum: '<S15>/Sum4' incorporates:
     *  Inport: '<Root>/r'
     */
    rtb_XrDotVv = rtU.r + rtb_Sum2;

    /* Sum: '<S15>/Sum7' incorporates:
     *  Gain: '<S15>/Gain2'
     *  Inport: '<Root>/r'
     *  Product: '<S15>/Product3'
     *  Product: '<S15>/Product5'
     *  Product: '<S15>/Product8'
     *  Sum: '<S15>/Sum'
     *  Sum: '<S1>/Sum'
     */
    rtb_Sum_c_idx_0 = (rtb_XrDotVv * rtb_Xr_idx_0 * -rtb_MathFunction1 +
                       rtb_MathFunction_idx_0) * rtU.r + rtb_Xr_idx_0;
    rtb_Sum_c_idx_1 = (rtb_XrDotVv * rtb_Xr_idx_1 * -rtb_MathFunction1 +
                       rtb_MathFunction_idx_1) * rtU.r + rtb_Xr_idx_1;
    rtb_Sum_c_idx_2 = (rtb_XrDotVv * rtb_Product1 * -rtb_MathFunction1 +
                       rtb_MathFunction_idx_2) * rtU.r + rtb_Product1;

    /* Sum: '<S15>/Sum5' incorporates:
     *  Inport: '<Root>/r'
     */
    rtb_XrDotVv = rtb_Sum2 - rtU.r;

    /* Sum: '<S14>/Sum' incorporates:
     *  Product: '<S16>/i x j'
     *  Product: '<S17>/i x j'
     */
    rtb_Sum2_tmp = rtb_Xr_idx_0 * rtb_Sum_c_idx_1;

    /* If: '<S3>/If' incorporates:
     *  Constant: '<S3>/Constant1'
     *  Product: '<S17>/i x j'
     *  RelationalOperator: '<S3>/Relational Operator'
     *  Sum: '<S14>/Sum'
     */
    if (rtb_Sum2_tmp - rtb_Sum2_tmp < 0.0) {
      /* Outputs for IfAction SubSystem: '<S3>/CW' incorporates:
       *  ActionPort: '<S13>/Action Port'
       */
      /* Outport: '<Root>/yout' incorporates:
       *  Inport: '<Root>/Xv'
       *  SignalConversion generated from: '<S13>/Xap1'
       *  Sum: '<S3>/Sum8'
       */
      rtY.yout[0] = rtU.Xv[0] + rtb_Sum_c_idx_0;
      rtY.yout[1] = rtU.Xv[1] + rtb_Sum_c_idx_1;
      rtY.yout[2] = rtU.Xv[2] + rtb_Sum_c_idx_2;

      /* End of Outputs for SubSystem: '<S3>/CW' */
    } else {
      /* Outputs for IfAction SubSystem: '<S3>/CCW' incorporates:
       *  ActionPort: '<S12>/Action Port'
       */
      /* Outport: '<Root>/yout' incorporates:
       *  Inport: '<Root>/Xv'
       *  Inport: '<Root>/r'
       *  Product: '<S15>/Product4'
       *  Product: '<S15>/Product6'
       *  Product: '<S15>/Product9'
       *  SignalConversion generated from: '<S12>/Xap1'
       *  Sum: '<S15>/Sum1'
       *  Sum: '<S15>/Sum6'
       *  Sum: '<S1>/Sum'
       *  Sum: '<S3>/Sum4'
       */
      rtY.yout[0] = ((rtb_XrDotVv * rtb_Xr_idx_0 * rtb_MathFunction1 -
                      rtb_MathFunction_idx_0) * rtU.r + rtb_Xr_idx_0) + rtU.Xv[0];
      rtY.yout[1] = ((rtb_XrDotVv * rtb_Xr_idx_1 * rtb_MathFunction1 -
                      rtb_MathFunction_idx_1) * rtU.r + rtb_Xr_idx_1) + rtU.Xv[1];
      rtY.yout[2] = ((rtb_XrDotVv * rtb_Product1 * rtb_MathFunction1 -
                      rtb_MathFunction_idx_2) * rtU.r + rtb_Product1) + rtU.Xv[2];

      /* End of Outputs for SubSystem: '<S3>/CCW' */
    }

    /* End of If: '<S3>/If' */
    /* End of Outputs for SubSystem: '<S1>/Outer' */
  }
}

/* Model initialize function */
void NLGuidance_12B_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
