/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: EB_12B.h
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

#ifndef EB_12B_h_
#define EB_12B_h_
#ifndef EB_12B_COMMON_INCLUDES_
#define EB_12B_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* EB_12B_COMMON_INCLUDES_ */

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T Divide_DWORK4[25];            /* '<S1>/Divide' */
  real_T Divide1_DWORK4[9];            /* '<S1>/Divide1' */
} DW;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T Divide[25];             /* '<S1>/Divide' */
} ConstB;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: Wp
   * Referenced by: '<Root>/Const'
   */
  real_T Const_Value[25];

  /* Expression: d
   * Referenced by: '<Root>/Const2'
   */
  real_T Const2_Value[3];

  /* Expression: I*1E-12
   * Referenced by: '<S2>/Constant4'
   */
  real_T Constant4_Value[9];
} ConstP;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T B_j[15];                      /* '<Root>/B' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T check[9];                     /* '<Root>/check' */
  real_T yinv[9];                      /* '<Root>/yinv' */
  real_T P_k[15];                      /* '<Root>/P' */
  real_T u[5];                         /* '<Root>/u' */
  real_T Buminusd[3];                  /* '<Root>/Buminusd' */
  real_T J;                            /* '<Root>/J' */
  boolean_T ridge_on;                  /* '<Root>/ridge_on' */
} ExtY;

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;
extern const ConstB rtConstB;          /* constant block i/o */

/* Constant parameters (default storage) */
extern const ConstP rtConstP;

/* Model entry point functions */
extern void EB_12B_initialize(void);
extern void EB_12B_step(void);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Check' : Unused code path elimination
 * Block '<S1>/Display2' : Unused code path elimination
 * Block '<S1>/Display3' : Unused code path elimination
 * Block '<S1>/Display4' : Unused code path elimination
 * Block '<S1>/Display5' : Unused code path elimination
 * Block '<S1>/Display6' : Unused code path elimination
 * Block '<S1>/Inverse' : Unused code path elimination
 * Block '<S2>/Display' : Unused code path elimination
 * Block '<S3>/Reshape' : Reshape block reduction
 * Block '<S2>/fix_on' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'EB_12B'
 * '<S1>'   : 'EB_12B/EB'
 * '<S2>'   : 'EB_12B/EB/ridge'
 * '<S3>'   : 'EB_12B/EB/ridge/det'
 */
#endif                                 /* EB_12B_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
