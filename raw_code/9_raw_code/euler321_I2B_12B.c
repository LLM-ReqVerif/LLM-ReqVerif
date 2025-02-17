/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: euler321_I2B_12B.c
 *
 * Code generated for Simulink model 'euler321_I2B_12B'.
 *
 * Model version                  : 1.17
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Sun Nov  3 13:57:30 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 10
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "euler321_I2B_12B.h"
#include <math.h>
#include <string.h>
#include "rtwtypes.h"

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Model step function */
void euler321_I2B_12B_step(void)
{
  real_T rtb_Product[9];
  real_T rtb_VectorConcatenate[9];
  real_T rtb_VectorConcatenate_g[9];
  real_T rtb_VectorConcatenate_p;
  real_T rtb_sincos_o1;
  real_T rtb_sincos_o2;
  int32_T i;
  int32_T i_0;

  /* Trigonometry: '<S3>/sincos' incorporates:
   *  Inport: '<Root>/theta'
   */
  rtb_sincos_o2 = sin(rtU.theta);
  rtb_sincos_o1 = cos(rtU.theta);

  /* Fcn: '<S3>/Fcn11' */
  rtb_VectorConcatenate[0] = rtb_sincos_o1;

  /* Fcn: '<S3>/Fcn21' */
  rtb_VectorConcatenate[1] = 0.0;

  /* Fcn: '<S3>/Fcn31' */
  rtb_VectorConcatenate[2] = rtb_sincos_o2;

  /* Fcn: '<S3>/Fcn12' */
  rtb_VectorConcatenate[3] = 0.0;

  /* Fcn: '<S3>/Fcn22' */
  rtb_VectorConcatenate[4] = 1.0;

  /* Fcn: '<S3>/Fcn32' */
  rtb_VectorConcatenate[5] = 0.0;

  /* Fcn: '<S3>/Fcn13' */
  rtb_VectorConcatenate[6] = -rtb_sincos_o2;

  /* Fcn: '<S3>/Fcn23' */
  rtb_VectorConcatenate[7] = 0.0;

  /* Fcn: '<S3>/Fcn33' */
  rtb_VectorConcatenate[8] = rtb_sincos_o1;

  /* Trigonometry: '<S2>/sincos' incorporates:
   *  Inport: '<Root>/psi'
   */
  rtb_sincos_o1 = sin(rtU.psi);
  rtb_sincos_o2 = cos(rtU.psi);

  /* Fcn: '<S2>/Fcn11' */
  rtb_VectorConcatenate_g[0] = rtb_sincos_o2;

  /* Fcn: '<S2>/Fcn21' */
  rtb_VectorConcatenate_g[1] = -rtb_sincos_o1;

  /* Fcn: '<S2>/Fcn31' */
  rtb_VectorConcatenate_g[2] = 0.0;

  /* Fcn: '<S2>/Fcn12' */
  rtb_VectorConcatenate_g[3] = rtb_sincos_o1;

  /* Fcn: '<S2>/Fcn22' */
  rtb_VectorConcatenate_g[4] = rtb_sincos_o2;

  /* Fcn: '<S2>/Fcn32' */
  rtb_VectorConcatenate_g[5] = 0.0;

  /* Fcn: '<S2>/Fcn13' */
  rtb_VectorConcatenate_g[6] = 0.0;

  /* Fcn: '<S2>/Fcn23' */
  rtb_VectorConcatenate_g[7] = 0.0;

  /* Fcn: '<S2>/Fcn33' */
  rtb_VectorConcatenate_g[8] = 1.0;

  /* Product: '<S1>/Product' incorporates:
   *  Concatenate: '<S6>/Vector Concatenate'
   *  Concatenate: '<S7>/Vector Concatenate'
   */
  for (i = 0; i < 3; i++) {
    rtb_sincos_o2 = rtb_VectorConcatenate_g[3 * i + 1];
    rtb_sincos_o1 = rtb_VectorConcatenate_g[3 * i];
    rtb_VectorConcatenate_p = rtb_VectorConcatenate_g[3 * i + 2];
    for (i_0 = 0; i_0 < 3; i_0++) {
      rtb_Product[i_0 + 3 * i] = (rtb_VectorConcatenate[i_0 + 3] * rtb_sincos_o2
        + rtb_sincos_o1 * rtb_VectorConcatenate[i_0]) +
        rtb_VectorConcatenate[i_0 + 6] * rtb_VectorConcatenate_p;
    }
  }

  /* End of Product: '<S1>/Product' */

  /* Trigonometry: '<S4>/sincos' incorporates:
   *  Inport: '<Root>/phi'
   */
  rtb_sincos_o1 = sin(rtU.phi);
  rtb_sincos_o2 = cos(rtU.phi);

  /* Fcn: '<S4>/Fcn11' */
  rtb_VectorConcatenate_g[0] = 1.0;

  /* Fcn: '<S4>/Fcn21' */
  rtb_VectorConcatenate_g[1] = 0.0;

  /* Fcn: '<S4>/Fcn31' */
  rtb_VectorConcatenate_g[2] = 0.0;

  /* Fcn: '<S4>/Fcn12' */
  rtb_VectorConcatenate_g[3] = 0.0;

  /* Fcn: '<S4>/Fcn22' */
  rtb_VectorConcatenate_g[4] = rtb_sincos_o2;

  /* Fcn: '<S4>/Fcn32' */
  rtb_VectorConcatenate_g[5] = -rtb_sincos_o1;

  /* Fcn: '<S4>/Fcn13' */
  rtb_VectorConcatenate_g[6] = 0.0;

  /* Fcn: '<S4>/Fcn23' */
  rtb_VectorConcatenate_g[7] = rtb_sincos_o1;

  /* Fcn: '<S4>/Fcn33' */
  rtb_VectorConcatenate_g[8] = rtb_sincos_o2;

  /* Product: '<S1>/Product1' incorporates:
   *  Concatenate: '<S7>/Vector Concatenate'
   *  Product: '<S1>/Product'
   */
  for (i = 0; i < 3; i++) {
    rtb_sincos_o2 = rtb_Product[3 * i + 1];
    rtb_sincos_o1 = rtb_Product[3 * i];
    rtb_VectorConcatenate_p = rtb_Product[3 * i + 2];
    for (i_0 = 0; i_0 < 3; i_0++) {
      rtb_VectorConcatenate[i_0 + 3 * i] = (rtb_VectorConcatenate_g[i_0 + 3] *
        rtb_sincos_o2 + rtb_sincos_o1 * rtb_VectorConcatenate_g[i_0]) +
        rtb_VectorConcatenate_g[i_0 + 6] * rtb_VectorConcatenate_p;
    }
  }

  /* End of Product: '<S1>/Product1' */

  /* Outport: '<Root>/DCM321' incorporates:
   *  Product: '<S1>/Product1'
   */
  memcpy(&rtY.DCM321[0], &rtb_VectorConcatenate[0], 9U * sizeof(real_T));

  /* Product: '<S1>/Product2' incorporates:
   *  Inport: '<Root>/Vi'
   */
  rtb_sincos_o2 = rtU.Vi[1];
  rtb_sincos_o1 = rtU.Vi[0];
  rtb_VectorConcatenate_p = rtU.Vi[2];

  /* Outport: '<Root>/Vb' incorporates:
   *  Product: '<S1>/Product1'
   *  Product: '<S1>/Product2'
   */
  for (i = 0; i < 3; i++) {
    rtY.Vb[i] = (rtb_VectorConcatenate[i + 3] * rtb_sincos_o2 +
                 rtb_VectorConcatenate[i] * rtb_sincos_o1) +
      rtb_VectorConcatenate[i + 6] * rtb_VectorConcatenate_p;
  }

  /* End of Outport: '<Root>/Vb' */
}

/* Model initialize function */
void euler321_I2B_12B_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
