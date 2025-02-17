/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: integrator_12B.h
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

#ifndef integrator_12B_h_
#define integrator_12B_h_
#ifndef integrator_12B_COMMON_INCLUDES_
#define integrator_12B_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* integrator_12B_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T UnitDelay1_DSTATE;            /* '<S1>/Unit Delay1' */
  real_T UnitDelay_DSTATE;             /* '<S1>/Unit Delay' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T cmd;                          /* '<Root>/xin' */
  boolean_T reset;                     /* '<Root>/reset' */
  real_T T;                            /* '<Root>/T' */
  real_T ic;                           /* '<Root>/ic' */
  real_T TL;                           /* '<Root>/TL' */
  real_T BL;                           /* '<Root>/BL' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T yout;                         /* '<Root>/yout' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/* Model entry point functions */
extern void integrator_12B_initialize(void);
extern void integrator_12B_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/Data Type Duplicate' : Unused code path elimination
 * Block '<S2>/Data Type Propagation' : Unused code path elimination
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
 * '<Root>' : 'integrator_12B'
 * '<S1>'   : 'integrator_12B/Tustin Integrator (Limited, Resettable, States)'
 * '<S2>'   : 'integrator_12B/Tustin Integrator (Limited, Resettable, States)/Saturation Dynamic'
 * '<S3>'   : 'integrator_12B/Tustin Integrator (Limited, Resettable, States)/bounds'
 */
#endif                                 /* integrator_12B_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
