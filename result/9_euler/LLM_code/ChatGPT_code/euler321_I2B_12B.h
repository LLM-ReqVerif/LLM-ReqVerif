/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: euler321_I2B_12B.h
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

#ifndef euler321_I2B_12B_h_
#define euler321_I2B_12B_h_
#ifndef euler321_I2B_12B_COMMON_INCLUDES_
#define euler321_I2B_12B_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* euler321_I2B_12B_COMMON_INCLUDES_ */

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T phi;                          /* '<Root>/phi' */
  real_T theta;                        /* '<Root>/theta' */
  real_T psi;                          /* '<Root>/psi' */
  real_T Vi[3];                        /* '<Root>/Vi' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T DCM321[9];                    /* '<Root>/DCM321' */
  real_T Vb[3];                        /* '<Root>/Vb' */
} ExtY;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/* Model entry point functions */
extern void euler321_I2B_12B_initialize(void);
extern void euler321_I2B_12B_step(void);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S5>/Reshape (9) to [3x3] column-major' : Reshape block reduction
 * Block '<S6>/Reshape (9) to [3x3] column-major' : Reshape block reduction
 * Block '<S7>/Reshape (9) to [3x3] column-major' : Reshape block reduction
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
 * '<Root>' : 'euler321_I2B_12B'
 * '<S1>'   : 'euler321_I2B_12B/COORDINATE TRANSFORM EULER 321 (INERTIAL TO BODY)'
 * '<S2>'   : 'euler321_I2B_12B/COORDINATE TRANSFORM EULER 321 (INERTIAL TO BODY)/Euler 1 Rotation (Yaw)'
 * '<S3>'   : 'euler321_I2B_12B/COORDINATE TRANSFORM EULER 321 (INERTIAL TO BODY)/Euler 2 Rotation (Pitch)'
 * '<S4>'   : 'euler321_I2B_12B/COORDINATE TRANSFORM EULER 321 (INERTIAL TO BODY)/Euler 3 Rotation (Roll)'
 * '<S5>'   : 'euler321_I2B_12B/COORDINATE TRANSFORM EULER 321 (INERTIAL TO BODY)/Euler 1 Rotation (Yaw)/Create 3x3 Matrix'
 * '<S6>'   : 'euler321_I2B_12B/COORDINATE TRANSFORM EULER 321 (INERTIAL TO BODY)/Euler 2 Rotation (Pitch)/Create 3x3 Matrix'
 * '<S7>'   : 'euler321_I2B_12B/COORDINATE TRANSFORM EULER 321 (INERTIAL TO BODY)/Euler 3 Rotation (Roll)/Create 3x3 Matrix'
 */
#endif                                 /* euler321_I2B_12B_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
