/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: nn_12B.c
 *
 * Code generated for Simulink model 'nn_12B'.
 *
 * Model version                  : 1.17
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Sun Nov  3 13:02:47 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 10
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "nn_12B.h"
#include "rtwtypes.h"

/* External inputs (root inport signals with default storage) */
ExternalInputs rtU;

/* External outputs (root outports fed by signals with default storage) */
ExternalOutputs rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
static void IfActionSubsystem(real_T rtu_In1, real_T *rty_Out1);
static void IfActionSubsystem1(real_T rtu_In1, real_T *rty_Out1);
static void IfActionSubsystem2(real_T rtu_In1, real_T *rty_Out1);
static void IfActionSubsystem3(real_T rtu_In1, real_T *rty_Out1);

/*
 * Output and update for action system:
 *    '<S4>/If Action Subsystem'
 *    '<S5>/If Action Subsystem'
 *    '<S6>/If Action Subsystem'
 *    '<S7>/If Action Subsystem'
 *    '<S8>/If Action Subsystem'
 *    '<S9>/If Action Subsystem'
 *    '<S10>/If Action Subsystem'
 *    '<S11>/If Action Subsystem'
 *    '<S12>/If Action Subsystem'
 *    '<S13>/If Action Subsystem'
 *    ...
 */
static void IfActionSubsystem(real_T rtu_In1, real_T *rty_Out1)
{
  /* Sum: '<S14>/Sum' incorporates:
   *  Constant: '<S14>/bias1'
   *  Gain: '<S14>/weight1'
   */
  *rty_Out1 = 0.01 * rtu_In1 - 0.990025;
}

/*
 * Output and update for action system:
 *    '<S4>/If Action Subsystem1'
 *    '<S5>/If Action Subsystem1'
 *    '<S6>/If Action Subsystem1'
 *    '<S7>/If Action Subsystem1'
 *    '<S8>/If Action Subsystem1'
 *    '<S9>/If Action Subsystem1'
 *    '<S10>/If Action Subsystem1'
 *    '<S11>/If Action Subsystem1'
 *    '<S12>/If Action Subsystem1'
 *    '<S13>/If Action Subsystem1'
 *    ...
 */
static void IfActionSubsystem1(real_T rtu_In1, real_T *rty_Out1)
{
  /* Product: '<S15>/Product1' incorporates:
   *  Constant: '<S15>/bias4'
   *  Sum: '<S15>/Sum3'
   */
  *rty_Out1 = (rtu_In1 + 2.0) * rtu_In1;
}

/*
 * Output and update for action system:
 *    '<S4>/If Action Subsystem2'
 *    '<S5>/If Action Subsystem2'
 *    '<S6>/If Action Subsystem2'
 *    '<S7>/If Action Subsystem2'
 *    '<S8>/If Action Subsystem2'
 *    '<S9>/If Action Subsystem2'
 *    '<S10>/If Action Subsystem2'
 *    '<S11>/If Action Subsystem2'
 *    '<S12>/If Action Subsystem2'
 *    '<S13>/If Action Subsystem2'
 *    ...
 */
static void IfActionSubsystem2(real_T rtu_In1, real_T *rty_Out1)
{
  /* Product: '<S16>/Product1' incorporates:
   *  Constant: '<S16>/bias4'
   *  Sum: '<S16>/Sum3'
   */
  *rty_Out1 = (2.0 - rtu_In1) * rtu_In1;
}

/*
 * Output and update for action system:
 *    '<S4>/If Action Subsystem3'
 *    '<S5>/If Action Subsystem3'
 *    '<S6>/If Action Subsystem3'
 *    '<S7>/If Action Subsystem3'
 *    '<S8>/If Action Subsystem3'
 *    '<S9>/If Action Subsystem3'
 *    '<S10>/If Action Subsystem3'
 *    '<S11>/If Action Subsystem3'
 *    '<S12>/If Action Subsystem3'
 *    '<S13>/If Action Subsystem3'
 *    ...
 */
static void IfActionSubsystem3(real_T rtu_In1, real_T *rty_Out1)
{
  /* Sum: '<S17>/Sum' incorporates:
   *  Constant: '<S17>/bias1'
   *  Gain: '<S17>/weight1'
   */
  *rty_Out1 = 0.01 * rtu_In1 + 0.990025;
}

/* Model step function */
void nn_12B_step(void)
{
  real_T rtb_Merge_0[10];
  real_T rtb_Product2_0[10];
  real_T rtb_Sum[10];
  real_T tmp;
  real_T tmp_0;
  int32_T i;
  int32_T i_0;

  /* Saturate: '<S1>/Saturation2' incorporates:
   *  Inport: '<Root>/x'
   */
  if (rtU.x > 1.885733) {
    tmp_0 = 1.885733;
  } else if (rtU.x < -1.969179) {
    tmp_0 = -1.969179;
  } else {
    tmp_0 = rtU.x;
  }

  /* Gain: '<S1>/Gain' incorporates:
   *  Constant: '<S1>/input mean'
   *  Saturate: '<S1>/Saturation2'
   *  Sum: '<S1>/Sum1'
   */
  tmp = (tmp_0 - -0.014928) * 0.918012;

  /* Saturate: '<S1>/Saturation2' incorporates:
   *  Inport: '<Root>/y'
   */
  if (rtU.y > 1.974943) {
    tmp_0 = 1.974943;
  } else if (rtU.y < -1.999644) {
    tmp_0 = -1.999644;
  } else {
    tmp_0 = rtU.y;
  }

  /* Gain: '<S1>/Gain' incorporates:
   *  Constant: '<S1>/input mean'
   *  Saturate: '<S1>/Saturation2'
   *  Sum: '<S1>/Sum1'
   */
  tmp_0 = (tmp_0 - -0.08076) * 0.847388;

  /* Sum: '<S2>/Sum' incorporates:
   *  Constant: '<S1>/Weights to Layer1'
   *  Constant: '<S1>/b1'
   *  Product: '<S1>/Product'
   */
  for (i = 0; i < 10; i++) {
    rtb_Sum[i] = (rtConstP.WeightstoLayer1_Value[i + 10] * tmp_0 +
                  rtConstP.WeightstoLayer1_Value[i] * tmp) + rtConstP.b1_Value[i];
  }

  /* End of Sum: '<S2>/Sum' */

  /* If: '<S4>/If' */
  if (rtb_Sum[0] < -0.995) {
    /* Outputs for IfAction SubSystem: '<S4>/If Action Subsystem' incorporates:
     *  ActionPort: '<S14>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem(rtb_Sum[0], &rtb_Merge_0[0]);

    /* End of Outputs for SubSystem: '<S4>/If Action Subsystem' */
  } else if (rtb_Sum[0] < 0.0) {
    /* Outputs for IfAction SubSystem: '<S4>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S15>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem1(rtb_Sum[0], &rtb_Merge_0[0]);

    /* End of Outputs for SubSystem: '<S4>/If Action Subsystem1' */
  } else if (rtb_Sum[0] < 0.995) {
    /* Outputs for IfAction SubSystem: '<S4>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S16>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem2(rtb_Sum[0], &rtb_Merge_0[0]);

    /* End of Outputs for SubSystem: '<S4>/If Action Subsystem2' */
  } else {
    /* Outputs for IfAction SubSystem: '<S4>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S17>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem3(rtb_Sum[0], &rtb_Merge_0[0]);

    /* End of Outputs for SubSystem: '<S4>/If Action Subsystem3' */
  }

  /* End of If: '<S4>/If' */

  /* If: '<S6>/If' */
  if (rtb_Sum[1] < -0.995) {
    /* Outputs for IfAction SubSystem: '<S6>/If Action Subsystem' incorporates:
     *  ActionPort: '<S22>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem(rtb_Sum[1], &rtb_Merge_0[1]);

    /* End of Outputs for SubSystem: '<S6>/If Action Subsystem' */
  } else if (rtb_Sum[1] < 0.0) {
    /* Outputs for IfAction SubSystem: '<S6>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S23>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem1(rtb_Sum[1], &rtb_Merge_0[1]);

    /* End of Outputs for SubSystem: '<S6>/If Action Subsystem1' */
  } else if (rtb_Sum[1] < 0.995) {
    /* Outputs for IfAction SubSystem: '<S6>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S24>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem2(rtb_Sum[1], &rtb_Merge_0[1]);

    /* End of Outputs for SubSystem: '<S6>/If Action Subsystem2' */
  } else {
    /* Outputs for IfAction SubSystem: '<S6>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S25>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem3(rtb_Sum[1], &rtb_Merge_0[1]);

    /* End of Outputs for SubSystem: '<S6>/If Action Subsystem3' */
  }

  /* End of If: '<S6>/If' */

  /* If: '<S7>/If' */
  if (rtb_Sum[2] < -0.995) {
    /* Outputs for IfAction SubSystem: '<S7>/If Action Subsystem' incorporates:
     *  ActionPort: '<S26>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem(rtb_Sum[2], &rtb_Merge_0[2]);

    /* End of Outputs for SubSystem: '<S7>/If Action Subsystem' */
  } else if (rtb_Sum[2] < 0.0) {
    /* Outputs for IfAction SubSystem: '<S7>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S27>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem1(rtb_Sum[2], &rtb_Merge_0[2]);

    /* End of Outputs for SubSystem: '<S7>/If Action Subsystem1' */
  } else if (rtb_Sum[2] < 0.995) {
    /* Outputs for IfAction SubSystem: '<S7>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S28>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem2(rtb_Sum[2], &rtb_Merge_0[2]);

    /* End of Outputs for SubSystem: '<S7>/If Action Subsystem2' */
  } else {
    /* Outputs for IfAction SubSystem: '<S7>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S29>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem3(rtb_Sum[2], &rtb_Merge_0[2]);

    /* End of Outputs for SubSystem: '<S7>/If Action Subsystem3' */
  }

  /* End of If: '<S7>/If' */

  /* If: '<S8>/If' */
  if (rtb_Sum[3] < -0.995) {
    /* Outputs for IfAction SubSystem: '<S8>/If Action Subsystem' incorporates:
     *  ActionPort: '<S30>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem(rtb_Sum[3], &rtb_Merge_0[3]);

    /* End of Outputs for SubSystem: '<S8>/If Action Subsystem' */
  } else if (rtb_Sum[3] < 0.0) {
    /* Outputs for IfAction SubSystem: '<S8>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S31>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem1(rtb_Sum[3], &rtb_Merge_0[3]);

    /* End of Outputs for SubSystem: '<S8>/If Action Subsystem1' */
  } else if (rtb_Sum[3] < 0.995) {
    /* Outputs for IfAction SubSystem: '<S8>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S32>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem2(rtb_Sum[3], &rtb_Merge_0[3]);

    /* End of Outputs for SubSystem: '<S8>/If Action Subsystem2' */
  } else {
    /* Outputs for IfAction SubSystem: '<S8>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S33>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem3(rtb_Sum[3], &rtb_Merge_0[3]);

    /* End of Outputs for SubSystem: '<S8>/If Action Subsystem3' */
  }

  /* End of If: '<S8>/If' */

  /* If: '<S9>/If' */
  if (rtb_Sum[4] < -0.995) {
    /* Outputs for IfAction SubSystem: '<S9>/If Action Subsystem' incorporates:
     *  ActionPort: '<S34>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem(rtb_Sum[4], &rtb_Merge_0[4]);

    /* End of Outputs for SubSystem: '<S9>/If Action Subsystem' */
  } else if (rtb_Sum[4] < 0.0) {
    /* Outputs for IfAction SubSystem: '<S9>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S35>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem1(rtb_Sum[4], &rtb_Merge_0[4]);

    /* End of Outputs for SubSystem: '<S9>/If Action Subsystem1' */
  } else if (rtb_Sum[4] < 0.995) {
    /* Outputs for IfAction SubSystem: '<S9>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S36>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem2(rtb_Sum[4], &rtb_Merge_0[4]);

    /* End of Outputs for SubSystem: '<S9>/If Action Subsystem2' */
  } else {
    /* Outputs for IfAction SubSystem: '<S9>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S37>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem3(rtb_Sum[4], &rtb_Merge_0[4]);

    /* End of Outputs for SubSystem: '<S9>/If Action Subsystem3' */
  }

  /* End of If: '<S9>/If' */

  /* If: '<S10>/If' */
  if (rtb_Sum[5] < -0.995) {
    /* Outputs for IfAction SubSystem: '<S10>/If Action Subsystem' incorporates:
     *  ActionPort: '<S38>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem(rtb_Sum[5], &rtb_Merge_0[5]);

    /* End of Outputs for SubSystem: '<S10>/If Action Subsystem' */
  } else if (rtb_Sum[5] < 0.0) {
    /* Outputs for IfAction SubSystem: '<S10>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S39>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem1(rtb_Sum[5], &rtb_Merge_0[5]);

    /* End of Outputs for SubSystem: '<S10>/If Action Subsystem1' */
  } else if (rtb_Sum[5] < 0.995) {
    /* Outputs for IfAction SubSystem: '<S10>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S40>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem2(rtb_Sum[5], &rtb_Merge_0[5]);

    /* End of Outputs for SubSystem: '<S10>/If Action Subsystem2' */
  } else {
    /* Outputs for IfAction SubSystem: '<S10>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S41>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem3(rtb_Sum[5], &rtb_Merge_0[5]);

    /* End of Outputs for SubSystem: '<S10>/If Action Subsystem3' */
  }

  /* End of If: '<S10>/If' */

  /* If: '<S11>/If' */
  if (rtb_Sum[6] < -0.995) {
    /* Outputs for IfAction SubSystem: '<S11>/If Action Subsystem' incorporates:
     *  ActionPort: '<S42>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem(rtb_Sum[6], &rtb_Merge_0[6]);

    /* End of Outputs for SubSystem: '<S11>/If Action Subsystem' */
  } else if (rtb_Sum[6] < 0.0) {
    /* Outputs for IfAction SubSystem: '<S11>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S43>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem1(rtb_Sum[6], &rtb_Merge_0[6]);

    /* End of Outputs for SubSystem: '<S11>/If Action Subsystem1' */
  } else if (rtb_Sum[6] < 0.995) {
    /* Outputs for IfAction SubSystem: '<S11>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S44>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem2(rtb_Sum[6], &rtb_Merge_0[6]);

    /* End of Outputs for SubSystem: '<S11>/If Action Subsystem2' */
  } else {
    /* Outputs for IfAction SubSystem: '<S11>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S45>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem3(rtb_Sum[6], &rtb_Merge_0[6]);

    /* End of Outputs for SubSystem: '<S11>/If Action Subsystem3' */
  }

  /* End of If: '<S11>/If' */

  /* If: '<S12>/If' */
  if (rtb_Sum[7] < -0.995) {
    /* Outputs for IfAction SubSystem: '<S12>/If Action Subsystem' incorporates:
     *  ActionPort: '<S46>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem(rtb_Sum[7], &rtb_Merge_0[7]);

    /* End of Outputs for SubSystem: '<S12>/If Action Subsystem' */
  } else if (rtb_Sum[7] < 0.0) {
    /* Outputs for IfAction SubSystem: '<S12>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S47>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem1(rtb_Sum[7], &rtb_Merge_0[7]);

    /* End of Outputs for SubSystem: '<S12>/If Action Subsystem1' */
  } else if (rtb_Sum[7] < 0.995) {
    /* Outputs for IfAction SubSystem: '<S12>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S48>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem2(rtb_Sum[7], &rtb_Merge_0[7]);

    /* End of Outputs for SubSystem: '<S12>/If Action Subsystem2' */
  } else {
    /* Outputs for IfAction SubSystem: '<S12>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S49>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem3(rtb_Sum[7], &rtb_Merge_0[7]);

    /* End of Outputs for SubSystem: '<S12>/If Action Subsystem3' */
  }

  /* End of If: '<S12>/If' */

  /* If: '<S13>/If' */
  if (rtb_Sum[8] < -0.995) {
    /* Outputs for IfAction SubSystem: '<S13>/If Action Subsystem' incorporates:
     *  ActionPort: '<S50>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem(rtb_Sum[8], &rtb_Merge_0[8]);

    /* End of Outputs for SubSystem: '<S13>/If Action Subsystem' */
  } else if (rtb_Sum[8] < 0.0) {
    /* Outputs for IfAction SubSystem: '<S13>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S51>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem1(rtb_Sum[8], &rtb_Merge_0[8]);

    /* End of Outputs for SubSystem: '<S13>/If Action Subsystem1' */
  } else if (rtb_Sum[8] < 0.995) {
    /* Outputs for IfAction SubSystem: '<S13>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S52>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem2(rtb_Sum[8], &rtb_Merge_0[8]);

    /* End of Outputs for SubSystem: '<S13>/If Action Subsystem2' */
  } else {
    /* Outputs for IfAction SubSystem: '<S13>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S53>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem3(rtb_Sum[8], &rtb_Merge_0[8]);

    /* End of Outputs for SubSystem: '<S13>/If Action Subsystem3' */
  }

  /* End of If: '<S13>/If' */

  /* If: '<S5>/If' */
  if (rtb_Sum[9] < -0.995) {
    /* Outputs for IfAction SubSystem: '<S5>/If Action Subsystem' incorporates:
     *  ActionPort: '<S18>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem(rtb_Sum[9], &rtb_Merge_0[9]);

    /* End of Outputs for SubSystem: '<S5>/If Action Subsystem' */
  } else if (rtb_Sum[9] < 0.0) {
    /* Outputs for IfAction SubSystem: '<S5>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S19>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem1(rtb_Sum[9], &rtb_Merge_0[9]);

    /* End of Outputs for SubSystem: '<S5>/If Action Subsystem1' */
  } else if (rtb_Sum[9] < 0.995) {
    /* Outputs for IfAction SubSystem: '<S5>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S20>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem2(rtb_Sum[9], &rtb_Merge_0[9]);

    /* End of Outputs for SubSystem: '<S5>/If Action Subsystem2' */
  } else {
    /* Outputs for IfAction SubSystem: '<S5>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S21>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product1' */
    IfActionSubsystem3(rtb_Sum[9], &rtb_Merge_0[9]);

    /* End of Outputs for SubSystem: '<S5>/If Action Subsystem3' */
  }

  /* End of If: '<S5>/If' */

  /* Sum: '<S3>/Sum' incorporates:
   *  Constant: '<S1>/Weights to Layer2'
   *  Constant: '<S1>/b2'
   *  Product: '<S1>/Product1'
   */
  for (i = 0; i < 10; i++) {
    tmp_0 = 0.0;
    for (i_0 = 0; i_0 < 10; i_0++) {
      tmp_0 += rtConstP.WeightstoLayer2_Value[10 * i_0 + i] * rtb_Merge_0[i_0];
    }

    rtb_Sum[i] = tmp_0 + rtConstP.b2_Value[i];
  }

  /* End of Sum: '<S3>/Sum' */

  /* If: '<S54>/If' */
  if (rtb_Sum[0] < -0.995) {
    /* Outputs for IfAction SubSystem: '<S54>/If Action Subsystem' incorporates:
     *  ActionPort: '<S64>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem(rtb_Sum[0], &rtb_Product2_0[0]);

    /* End of Outputs for SubSystem: '<S54>/If Action Subsystem' */
  } else if (rtb_Sum[0] < 0.0) {
    /* Outputs for IfAction SubSystem: '<S54>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S65>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem1(rtb_Sum[0], &rtb_Product2_0[0]);

    /* End of Outputs for SubSystem: '<S54>/If Action Subsystem1' */
  } else if (rtb_Sum[0] < 0.995) {
    /* Outputs for IfAction SubSystem: '<S54>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S66>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem2(rtb_Sum[0], &rtb_Product2_0[0]);

    /* End of Outputs for SubSystem: '<S54>/If Action Subsystem2' */
  } else {
    /* Outputs for IfAction SubSystem: '<S54>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S67>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem3(rtb_Sum[0], &rtb_Product2_0[0]);

    /* End of Outputs for SubSystem: '<S54>/If Action Subsystem3' */
  }

  /* End of If: '<S54>/If' */

  /* If: '<S56>/If' */
  if (rtb_Sum[1] < -0.995) {
    /* Outputs for IfAction SubSystem: '<S56>/If Action Subsystem' incorporates:
     *  ActionPort: '<S72>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem(rtb_Sum[1], &rtb_Product2_0[1]);

    /* End of Outputs for SubSystem: '<S56>/If Action Subsystem' */
  } else if (rtb_Sum[1] < 0.0) {
    /* Outputs for IfAction SubSystem: '<S56>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S73>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem1(rtb_Sum[1], &rtb_Product2_0[1]);

    /* End of Outputs for SubSystem: '<S56>/If Action Subsystem1' */
  } else if (rtb_Sum[1] < 0.995) {
    /* Outputs for IfAction SubSystem: '<S56>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S74>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem2(rtb_Sum[1], &rtb_Product2_0[1]);

    /* End of Outputs for SubSystem: '<S56>/If Action Subsystem2' */
  } else {
    /* Outputs for IfAction SubSystem: '<S56>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S75>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem3(rtb_Sum[1], &rtb_Product2_0[1]);

    /* End of Outputs for SubSystem: '<S56>/If Action Subsystem3' */
  }

  /* End of If: '<S56>/If' */

  /* If: '<S57>/If' */
  if (rtb_Sum[2] < -0.995) {
    /* Outputs for IfAction SubSystem: '<S57>/If Action Subsystem' incorporates:
     *  ActionPort: '<S76>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem(rtb_Sum[2], &rtb_Product2_0[2]);

    /* End of Outputs for SubSystem: '<S57>/If Action Subsystem' */
  } else if (rtb_Sum[2] < 0.0) {
    /* Outputs for IfAction SubSystem: '<S57>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S77>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem1(rtb_Sum[2], &rtb_Product2_0[2]);

    /* End of Outputs for SubSystem: '<S57>/If Action Subsystem1' */
  } else if (rtb_Sum[2] < 0.995) {
    /* Outputs for IfAction SubSystem: '<S57>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S78>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem2(rtb_Sum[2], &rtb_Product2_0[2]);

    /* End of Outputs for SubSystem: '<S57>/If Action Subsystem2' */
  } else {
    /* Outputs for IfAction SubSystem: '<S57>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S79>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem3(rtb_Sum[2], &rtb_Product2_0[2]);

    /* End of Outputs for SubSystem: '<S57>/If Action Subsystem3' */
  }

  /* End of If: '<S57>/If' */

  /* If: '<S58>/If' */
  if (rtb_Sum[3] < -0.995) {
    /* Outputs for IfAction SubSystem: '<S58>/If Action Subsystem' incorporates:
     *  ActionPort: '<S80>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem(rtb_Sum[3], &rtb_Product2_0[3]);

    /* End of Outputs for SubSystem: '<S58>/If Action Subsystem' */
  } else if (rtb_Sum[3] < 0.0) {
    /* Outputs for IfAction SubSystem: '<S58>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S81>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem1(rtb_Sum[3], &rtb_Product2_0[3]);

    /* End of Outputs for SubSystem: '<S58>/If Action Subsystem1' */
  } else if (rtb_Sum[3] < 0.995) {
    /* Outputs for IfAction SubSystem: '<S58>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S82>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem2(rtb_Sum[3], &rtb_Product2_0[3]);

    /* End of Outputs for SubSystem: '<S58>/If Action Subsystem2' */
  } else {
    /* Outputs for IfAction SubSystem: '<S58>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S83>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem3(rtb_Sum[3], &rtb_Product2_0[3]);

    /* End of Outputs for SubSystem: '<S58>/If Action Subsystem3' */
  }

  /* End of If: '<S58>/If' */

  /* If: '<S59>/If' */
  if (rtb_Sum[4] < -0.995) {
    /* Outputs for IfAction SubSystem: '<S59>/If Action Subsystem' incorporates:
     *  ActionPort: '<S84>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem(rtb_Sum[4], &rtb_Product2_0[4]);

    /* End of Outputs for SubSystem: '<S59>/If Action Subsystem' */
  } else if (rtb_Sum[4] < 0.0) {
    /* Outputs for IfAction SubSystem: '<S59>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S85>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem1(rtb_Sum[4], &rtb_Product2_0[4]);

    /* End of Outputs for SubSystem: '<S59>/If Action Subsystem1' */
  } else if (rtb_Sum[4] < 0.995) {
    /* Outputs for IfAction SubSystem: '<S59>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S86>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem2(rtb_Sum[4], &rtb_Product2_0[4]);

    /* End of Outputs for SubSystem: '<S59>/If Action Subsystem2' */
  } else {
    /* Outputs for IfAction SubSystem: '<S59>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S87>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem3(rtb_Sum[4], &rtb_Product2_0[4]);

    /* End of Outputs for SubSystem: '<S59>/If Action Subsystem3' */
  }

  /* End of If: '<S59>/If' */

  /* If: '<S60>/If' */
  if (rtb_Sum[5] < -0.995) {
    /* Outputs for IfAction SubSystem: '<S60>/If Action Subsystem' incorporates:
     *  ActionPort: '<S88>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem(rtb_Sum[5], &rtb_Product2_0[5]);

    /* End of Outputs for SubSystem: '<S60>/If Action Subsystem' */
  } else if (rtb_Sum[5] < 0.0) {
    /* Outputs for IfAction SubSystem: '<S60>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S89>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem1(rtb_Sum[5], &rtb_Product2_0[5]);

    /* End of Outputs for SubSystem: '<S60>/If Action Subsystem1' */
  } else if (rtb_Sum[5] < 0.995) {
    /* Outputs for IfAction SubSystem: '<S60>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S90>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem2(rtb_Sum[5], &rtb_Product2_0[5]);

    /* End of Outputs for SubSystem: '<S60>/If Action Subsystem2' */
  } else {
    /* Outputs for IfAction SubSystem: '<S60>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S91>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem3(rtb_Sum[5], &rtb_Product2_0[5]);

    /* End of Outputs for SubSystem: '<S60>/If Action Subsystem3' */
  }

  /* End of If: '<S60>/If' */

  /* If: '<S61>/If' */
  if (rtb_Sum[6] < -0.995) {
    /* Outputs for IfAction SubSystem: '<S61>/If Action Subsystem' incorporates:
     *  ActionPort: '<S92>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem(rtb_Sum[6], &rtb_Product2_0[6]);

    /* End of Outputs for SubSystem: '<S61>/If Action Subsystem' */
  } else if (rtb_Sum[6] < 0.0) {
    /* Outputs for IfAction SubSystem: '<S61>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S93>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem1(rtb_Sum[6], &rtb_Product2_0[6]);

    /* End of Outputs for SubSystem: '<S61>/If Action Subsystem1' */
  } else if (rtb_Sum[6] < 0.995) {
    /* Outputs for IfAction SubSystem: '<S61>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S94>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem2(rtb_Sum[6], &rtb_Product2_0[6]);

    /* End of Outputs for SubSystem: '<S61>/If Action Subsystem2' */
  } else {
    /* Outputs for IfAction SubSystem: '<S61>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S95>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem3(rtb_Sum[6], &rtb_Product2_0[6]);

    /* End of Outputs for SubSystem: '<S61>/If Action Subsystem3' */
  }

  /* End of If: '<S61>/If' */

  /* If: '<S62>/If' */
  if (rtb_Sum[7] < -0.995) {
    /* Outputs for IfAction SubSystem: '<S62>/If Action Subsystem' incorporates:
     *  ActionPort: '<S96>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem(rtb_Sum[7], &rtb_Product2_0[7]);

    /* End of Outputs for SubSystem: '<S62>/If Action Subsystem' */
  } else if (rtb_Sum[7] < 0.0) {
    /* Outputs for IfAction SubSystem: '<S62>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S97>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem1(rtb_Sum[7], &rtb_Product2_0[7]);

    /* End of Outputs for SubSystem: '<S62>/If Action Subsystem1' */
  } else if (rtb_Sum[7] < 0.995) {
    /* Outputs for IfAction SubSystem: '<S62>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S98>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem2(rtb_Sum[7], &rtb_Product2_0[7]);

    /* End of Outputs for SubSystem: '<S62>/If Action Subsystem2' */
  } else {
    /* Outputs for IfAction SubSystem: '<S62>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S99>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem3(rtb_Sum[7], &rtb_Product2_0[7]);

    /* End of Outputs for SubSystem: '<S62>/If Action Subsystem3' */
  }

  /* End of If: '<S62>/If' */

  /* If: '<S63>/If' */
  if (rtb_Sum[8] < -0.995) {
    /* Outputs for IfAction SubSystem: '<S63>/If Action Subsystem' incorporates:
     *  ActionPort: '<S100>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem(rtb_Sum[8], &rtb_Product2_0[8]);

    /* End of Outputs for SubSystem: '<S63>/If Action Subsystem' */
  } else if (rtb_Sum[8] < 0.0) {
    /* Outputs for IfAction SubSystem: '<S63>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S101>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem1(rtb_Sum[8], &rtb_Product2_0[8]);

    /* End of Outputs for SubSystem: '<S63>/If Action Subsystem1' */
  } else if (rtb_Sum[8] < 0.995) {
    /* Outputs for IfAction SubSystem: '<S63>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S102>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem2(rtb_Sum[8], &rtb_Product2_0[8]);

    /* End of Outputs for SubSystem: '<S63>/If Action Subsystem2' */
  } else {
    /* Outputs for IfAction SubSystem: '<S63>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S103>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem3(rtb_Sum[8], &rtb_Product2_0[8]);

    /* End of Outputs for SubSystem: '<S63>/If Action Subsystem3' */
  }

  /* End of If: '<S63>/If' */

  /* If: '<S55>/If' */
  if (rtb_Sum[9] < -0.995) {
    /* Outputs for IfAction SubSystem: '<S55>/If Action Subsystem' incorporates:
     *  ActionPort: '<S68>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem(rtb_Sum[9], &rtb_Product2_0[9]);

    /* End of Outputs for SubSystem: '<S55>/If Action Subsystem' */
  } else if (rtb_Sum[9] < 0.0) {
    /* Outputs for IfAction SubSystem: '<S55>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S69>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem1(rtb_Sum[9], &rtb_Product2_0[9]);

    /* End of Outputs for SubSystem: '<S55>/If Action Subsystem1' */
  } else if (rtb_Sum[9] < 0.995) {
    /* Outputs for IfAction SubSystem: '<S55>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S70>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem2(rtb_Sum[9], &rtb_Product2_0[9]);

    /* End of Outputs for SubSystem: '<S55>/If Action Subsystem2' */
  } else {
    /* Outputs for IfAction SubSystem: '<S55>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S71>/Action Port'
     */
    /* SignalConversion generated from: '<S1>/Product2' */
    IfActionSubsystem3(rtb_Sum[9], &rtb_Product2_0[9]);

    /* End of Outputs for SubSystem: '<S55>/If Action Subsystem3' */
  }

  /* End of If: '<S55>/If' */

  /* Product: '<S1>/Product2' incorporates:
   *  Constant: '<S1>/Weights to Output Layer'
   */
  tmp_0 = 0.0;
  for (i = 0; i < 10; i++) {
    tmp_0 += rtConstP.WeightstoOutputLayer_Value[i] * rtb_Product2_0[i];
  }

  /* Outport: '<Root>/z' incorporates:
   *  Gain: '<S1>/Gain1'
   *  Product: '<S1>/Product2'
   *  Sum: '<S1>/Sum'
   *  Sum: '<S1>/Sum2'
   */
  rtY.z = (tmp_0 - 0.01575) * 0.183766 - 0.01416;
}

/* Model initialize function */
void nn_12B_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
