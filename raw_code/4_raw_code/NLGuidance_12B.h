/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: NLGuidance_12B.h
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

#ifndef NLGuidance_12B_h_
#define NLGuidance_12B_h_
#ifndef NLGuidance_12B_COMMON_INCLUDES_
#define NLGuidance_12B_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* NLGuidance_12B_COMMON_INCLUDES_ */

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T Xtarg[3];                     /* '<Root>/Xtarg' */
  real_T Xv[3];                        /* '<Root>/Xv' */
  real_T Vv[3];                        /* '<Root>/Vv' */
  real_T r;                            /* '<Root>/r' */
  real_T Vt[3];                        /* '<Root>/Vt' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T yout[3];                      /* '<Root>/yout' */
} ExtY;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/* Model entry point functions */
extern void NLGuidance_12B_initialize(void);
extern void NLGuidance_12B_step(void);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Display' : Unused code path elimination
 * Block '<S1>/Display1' : Unused code path elimination
 * Block '<S1>/Display2' : Unused code path elimination
 * Block '<S3>/Divide2' : Unused code path elimination
 * Block '<S3>/Divide3' : Unused code path elimination
 * Block '<S3>/Gain' : Unused code path elimination
 * Block '<S3>/Gain1' : Unused code path elimination
 * Block '<S3>/Math Function' : Unused code path elimination
 * Block '<S3>/Math Function1' : Unused code path elimination
 * Block '<S3>/Product1' : Unused code path elimination
 * Block '<S3>/Sum1' : Unused code path elimination
 * Block '<S3>/Sum2' : Unused code path elimination
 * Block '<S3>/Sum3' : Unused code path elimination
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
 * '<Root>' : 'NLGuidance_12B'
 * '<S1>'   : 'NLGuidance_12B/NLGuidance'
 * '<S2>'   : 'NLGuidance_12B/NLGuidance/Inner'
 * '<S3>'   : 'NLGuidance_12B/NLGuidance/Outer'
 * '<S4>'   : 'NLGuidance_12B/NLGuidance/norm1'
 * '<S5>'   : 'NLGuidance_12B/NLGuidance/norm2'
 * '<S6>'   : 'NLGuidance_12B/NLGuidance/Inner/Act1'
 * '<S7>'   : 'NLGuidance_12B/NLGuidance/Inner/Act2'
 * '<S8>'   : 'NLGuidance_12B/NLGuidance/Inner/Arg1'
 * '<S9>'   : 'NLGuidance_12B/NLGuidance/Inner/Arg2'
 * '<S10>'  : 'NLGuidance_12B/NLGuidance/Inner/norm'
 * '<S11>'  : 'NLGuidance_12B/NLGuidance/Inner/norm1'
 * '<S12>'  : 'NLGuidance_12B/NLGuidance/Outer/CCW'
 * '<S13>'  : 'NLGuidance_12B/NLGuidance/Outer/CW'
 * '<S14>'  : 'NLGuidance_12B/NLGuidance/Outer/cross'
 * '<S15>'  : 'NLGuidance_12B/NLGuidance/Outer/r_computation'
 * '<S16>'  : 'NLGuidance_12B/NLGuidance/Outer/cross/Subsystem1'
 * '<S17>'  : 'NLGuidance_12B/NLGuidance/Outer/cross/Subsystem2'
 */
#endif                                 /* NLGuidance_12B_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
