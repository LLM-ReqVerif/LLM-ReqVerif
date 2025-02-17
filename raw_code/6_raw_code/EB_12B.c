/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: EB_12B.c
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
 */

#include "EB_12B.h"
#include <string.h>
#include "rtwtypes.h"
#include <math.h>

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;
extern void rt_invd3x3_snf(const real_T u[9], real_T y[9]);
void rt_invd3x3_snf(const real_T u[9], real_T y[9])
{
  real_T x[9];
  real_T absx11;
  real_T absx21;
  real_T absx31;
  int32_T itmp;
  int32_T p1;
  int32_T p2;
  int32_T p3;
  memcpy(&x[0], &u[0], 9U * sizeof(real_T));
  p1 = 1;
  p2 = 3;
  p3 = 6;
  absx11 = fabs(u[0]);
  absx21 = fabs(u[1]);
  absx31 = fabs(u[2]);
  if ((absx21 > absx11) && (absx21 > absx31)) {
    p1 = 4;
    p2 = 0;
    x[0] = u[1];
    x[1] = u[0];
    x[3] = u[4];
    x[4] = u[3];
    x[6] = u[7];
    x[7] = u[6];
  } else if (absx31 > absx11) {
    p1 = 7;
    p3 = 0;
    x[2] = x[0];
    x[0] = u[2];
    x[5] = x[3];
    x[3] = u[5];
    x[8] = x[6];
    x[6] = u[8];
  }

  absx31 = x[1] / x[0];
  x[1] = absx31;
  absx11 = x[2] / x[0];
  x[2] = absx11;
  x[4] -= absx31 * x[3];
  x[5] -= absx11 * x[3];
  x[7] -= absx31 * x[6];
  x[8] -= absx11 * x[6];
  if (fabs(x[5]) > fabs(x[4])) {
    itmp = p2;
    p2 = p3;
    p3 = itmp;
    x[1] = absx11;
    x[2] = absx31;
    absx11 = x[4];
    x[4] = x[5];
    x[5] = absx11;
    absx11 = x[7];
    x[7] = x[8];
    x[8] = absx11;
  }

  absx31 = x[5] / x[4];
  x[8] -= absx31 * x[7];
  absx11 = (x[1] * absx31 - x[2]) / x[8];
  absx21 = -(x[7] * absx11 + x[1]) / x[4];
  y[p1 - 1] = ((1.0 - x[3] * absx21) - x[6] * absx11) / x[0];
  y[p1] = absx21;
  y[p1 + 1] = absx11;
  absx11 = -absx31 / x[8];
  absx21 = (1.0 - x[7] * absx11) / x[4];
  y[p2] = -(x[3] * absx21 + x[6] * absx11) / x[0];
  y[p2 + 1] = absx21;
  y[p2 + 2] = absx11;
  absx11 = 1.0 / x[8];
  absx21 = -x[7] * absx11 / x[4];
  y[p3] = -(x[3] * absx21 + x[6] * absx11) / x[0];
  y[p3 + 1] = absx21;
  y[p3 + 2] = absx11;
}

/* Model step function */
void EB_12B_step(void)
{
  real_T rtb_MathFunction2[15];
  real_T rtb_Product1_f[15];
  real_T rtb_Product7[15];
  real_T rtb_Divide1[9];
  real_T rtb_Product1_a[9];
  real_T rtb_Product3_a[5];
  real_T rtb_Divide1_0;
  real_T rtb_Divide1_1;
  real_T rtb_Product7_0;
  int32_T i;
  int32_T i_0;
  int32_T i_1;
  boolean_T rtb_RelationalOperator;

  /* Product: '<S1>/Product5' incorporates:
   *  Inport: '<Root>/B'
   *  Math: '<S1>/Math Function1'
   *  Product: '<S1>/Divide'
   *  Product: '<S1>/Product7'
   */
  for (i = 0; i < 5; i++) {
    for (i_0 = 0; i_0 < 3; i_0++) {
      rtb_Product7_0 = 0.0;
      for (i_1 = 0; i_1 < 5; i_1++) {
        rtb_Product7_0 += rtConstB.Divide[5 * i_1 + i] * rtU.B_j[3 * i_1 + i_0];
      }

      rtb_Product7[i + 5 * i_0] = rtb_Product7_0;
    }
  }

  /* End of Product: '<S1>/Product5' */

  /* Product: '<S1>/Product1' incorporates:
   *  Inport: '<Root>/B'
   *  Product: '<S1>/Product7'
   */
  for (i = 0; i < 3; i++) {
    for (i_0 = 0; i_0 < 3; i_0++) {
      rtb_Product7_0 = 0.0;
      for (i_1 = 0; i_1 < 5; i_1++) {
        rtb_Product7_0 += rtU.B_j[3 * i_1 + i_0] * rtb_Product7[5 * i + i_1];
      }

      rtb_Product1_a[i_0 + 3 * i] = rtb_Product7_0;
    }
  }

  memcpy(&rtb_Product1_f[0], &rtb_Product1_a[0], 9U * sizeof(real_T));

  /* End of Product: '<S1>/Product1' */

  /* RelationalOperator: '<S2>/Relational Operator' incorporates:
   *  Constant: '<S2>/Constant1'
   *  Product: '<S3>/Product'
   *  Product: '<S3>/Product1'
   *  Product: '<S3>/Product2'
   *  Product: '<S3>/Product3'
   *  Product: '<S3>/Product4'
   *  Product: '<S3>/Product5'
   *  Sum: '<S3>/Sum'
   */
  rtb_RelationalOperator = (((((rtb_Product1_f[0] * rtb_Product1_f[4] *
    rtb_Product1_f[8] - rtb_Product1_f[0] * rtb_Product1_f[5] * rtb_Product1_f[7])
    - rtb_Product1_f[1] * rtb_Product1_f[3] * rtb_Product1_f[8]) +
    rtb_Product1_f[2] * rtb_Product1_f[3] * rtb_Product1_f[7]) + rtb_Product1_f
    [1] * rtb_Product1_f[5] * rtb_Product1_f[6]) - rtb_Product1_f[2] *
    rtb_Product1_f[4] * rtb_Product1_f[6] <= 1.0E-12);

  /* Sum: '<S2>/Sum4' incorporates:
   *  Switch: '<S2>/Switch'
   */
  for (i = 0; i < 9; i++) {
    /* Switch: '<S2>/Switch' incorporates:
     *  Constant: '<S2>/Constant4'
     */
    if (rtb_RelationalOperator) {
      rtb_Product7_0 = rtConstP.Constant4_Value[i];
    } else {
      rtb_Product7_0 = 0.0;
    }

    rtb_Product1_a[i] = rtb_Product1_f[i] + rtb_Product7_0;
  }

  /* End of Sum: '<S2>/Sum4' */

  /* Product: '<S1>/Divide1' */
  rt_invd3x3_snf(rtb_Product1_a, rtb_Divide1);

  /* Product: '<S1>/Product2' incorporates:
   *  Math: '<S1>/Math Function2'
   *  Product: '<S1>/Divide1'
   *  Product: '<S1>/Product7'
   */
  for (i = 0; i < 3; i++) {
    rtb_Product7_0 = rtb_Divide1[3 * i + 1];
    rtb_Divide1_0 = rtb_Divide1[3 * i];
    rtb_Divide1_1 = rtb_Divide1[3 * i + 2];
    for (i_0 = 0; i_0 < 5; i_0++) {
      rtb_MathFunction2[i_0 + 5 * i] = (rtb_Product7[i_0 + 5] * rtb_Product7_0 +
        rtb_Divide1_0 * rtb_Product7[i_0]) + rtb_Product7[i_0 + 10] *
        rtb_Divide1_1;
    }
  }

  /* End of Product: '<S1>/Product2' */

  /* Outport: '<Root>/P' incorporates:
   *  Math: '<S1>/Math Function2'
   */
  memcpy(&rtY.P_k[0], &rtb_MathFunction2[0], 15U * sizeof(real_T));

  /* Product: '<S1>/Product4' */
  memcpy(&rtb_Product1_a[0], &rtb_Product1_f[0], 9U * sizeof(real_T));

  /* Outport: '<Root>/check' */
  for (i = 0; i < 3; i++) {
    /* Product: '<S1>/Product4' incorporates:
     *  Product: '<S1>/Divide1'
     */
    rtb_Product7_0 = rtb_Divide1[3 * i + 1];
    rtb_Divide1_0 = rtb_Divide1[3 * i];
    rtb_Divide1_1 = rtb_Divide1[3 * i + 2];
    for (i_0 = 0; i_0 < 3; i_0++) {
      /* Product: '<S1>/Product4' */
      rtY.check[i_0 + 3 * i] = (rtb_Product1_a[i_0 + 3] * rtb_Product7_0 +
        rtb_Divide1_0 * rtb_Product1_a[i_0]) + rtb_Product1_a[i_0 + 6] *
        rtb_Divide1_1;
    }
  }

  /* End of Outport: '<Root>/check' */

  /* Outport: '<Root>/yinv' incorporates:
   *  Product: '<S1>/Divide1'
   */
  memcpy(&rtY.yinv[0], &rtb_Divide1[0], 9U * sizeof(real_T));
  for (i = 0; i < 5; i++) {
    /* Product: '<S1>/Product3' incorporates:
     *  Constant: '<Root>/Const2'
     *  Math: '<S1>/Math Function2'
     */
    rtb_Product7_0 = (rtb_MathFunction2[i] * 3.0 - rtb_MathFunction2[i + 5]) +
      rtb_MathFunction2[i + 10] * 2.0;
    rtb_Product3_a[i] = rtb_Product7_0;

    /* Outport: '<Root>/u' incorporates:
     *  Product: '<S1>/Product3'
     */
    rtY.u[i] = rtb_Product7_0;

    /* Sum: '<S1>/Sum1' incorporates:
     *  Product: '<S1>/Product3'
     */
    rtb_MathFunction2[i] = rtb_Product7_0;
  }

  /* Product: '<S1>/Product7' incorporates:
   *  Constant: '<Root>/Const'
   */
  for (i = 0; i < 5; i++) {
    rtb_Product7_0 = 0.0;
    for (i_0 = 0; i_0 < 5; i_0++) {
      rtb_Product7_0 += rtConstP.Const_Value[5 * i_0 + i] *
        rtb_MathFunction2[i_0];
    }

    rtb_Product7[i] = rtb_Product7_0;
  }

  /* End of Product: '<S1>/Product7' */

  /* Outport: '<Root>/Buminusd' incorporates:
   *  Constant: '<Root>/Const2'
   *  Inport: '<Root>/B'
   *  Product: '<S1>/Product6'
   *  Sum: '<S1>/Sum'
   */
  for (i = 0; i < 3; i++) {
    rtb_Product7_0 = 0.0;
    for (i_0 = 0; i_0 < 5; i_0++) {
      rtb_Product7_0 += rtU.B_j[3 * i_0 + i] * rtb_Product3_a[i_0];
    }

    rtY.Buminusd[i] = rtb_Product7_0 - rtConstP.Const2_Value[i];
  }

  /* End of Outport: '<Root>/Buminusd' */

  /* Product: '<S1>/Product8' */
  rtb_Product7_0 = 0.0;
  for (i = 0; i < 5; i++) {
    rtb_Product7_0 += rtb_MathFunction2[i] * rtb_Product7[i];
  }

  /* Outport: '<Root>/J' incorporates:
   *  Product: '<S1>/Product8'
   */
  rtY.J = rtb_Product7_0;

  /* Outport: '<Root>/ridge_on' */
  rtY.ridge_on = rtb_RelationalOperator;
}

/* Model initialize function */
void EB_12B_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
