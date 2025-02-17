/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: triplex_12B.h
 *
 * Code generated for Simulink model 'triplex_12B'.
 *
 * Model version                  : 1.60
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Fri Nov  1 12:49:54 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 10
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef triplex_12B_h_
#define triplex_12B_h_
#ifndef triplex_12B_COMMON_INCLUDES_
#define triplex_12B_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* triplex_12B_COMMON_INCLUDES_ */

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T Merge;                        /* '<S4>/Merge' */
  int32_T Merge_e[3];                  /* '<S2>/Merge' */
  int32_T Delay1_DSTATE[3];            /* '<S1>/Delay1' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T ia;                           /* '<Root>/ia' */
  real_T ib;                           /* '<Root>/ib' */
  real_T ic;                           /* '<Root>/ic' */
  real_T Tlevel;                       /* '<Root>/Tlevel' */
  int32_T PClimit;                     /* '<Root>/PClimit' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  int32_T PC;                          /* '<Root>/PC' */
  int32_T TC;                          /* '<Root>/TC' */
  int32_T FC;                          /* '<Root>/FC' */
  real_T sel_val;                      /* '<Root>/sel_val' */
} ExtY;

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/* Model entry point functions */
extern void triplex_12B_initialize(void);
extern void triplex_12B_step(void);

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
 * '<Root>' : 'triplex_12B'
 * '<S1>'   : 'triplex_12B/TriplexMonitorNoFail'
 * '<S2>'   : 'triplex_12B/TriplexMonitorNoFail/Actions'
 * '<S3>'   : 'triplex_12B/TriplexMonitorNoFail/Conditions'
 * '<S4>'   : 'triplex_12B/TriplexMonitorNoFail/Output'
 * '<S5>'   : 'triplex_12B/TriplexMonitorNoFail/Actions/Act1'
 * '<S6>'   : 'triplex_12B/TriplexMonitorNoFail/Actions/Act2'
 * '<S7>'   : 'triplex_12B/TriplexMonitorNoFail/Actions/Act3'
 * '<S8>'   : 'triplex_12B/TriplexMonitorNoFail/Actions/Act4'
 * '<S9>'   : 'triplex_12B/TriplexMonitorNoFail/Actions/Act5'
 * '<S10>'  : 'triplex_12B/TriplexMonitorNoFail/Actions/Act6'
 * '<S11>'  : 'triplex_12B/TriplexMonitorNoFail/Actions/Act7'
 * '<S12>'  : 'triplex_12B/TriplexMonitorNoFail/Actions/Act8'
 * '<S13>'  : 'triplex_12B/TriplexMonitorNoFail/Actions/Action3'
 * '<S14>'  : 'triplex_12B/TriplexMonitorNoFail/Actions/Action4'
 * '<S15>'  : 'triplex_12B/TriplexMonitorNoFail/Actions/Action8'
 * '<S16>'  : 'triplex_12B/TriplexMonitorNoFail/Actions/Actions1_2'
 * '<S17>'  : 'triplex_12B/TriplexMonitorNoFail/Actions/Actions5_6_7'
 * '<S18>'  : 'triplex_12B/TriplexMonitorNoFail/Output/No-Fail'
 * '<S19>'  : 'triplex_12B/TriplexMonitorNoFail/Output/Single-BranchA-Fail'
 * '<S20>'  : 'triplex_12B/TriplexMonitorNoFail/Output/Single-BranchB-Fail'
 * '<S21>'  : 'triplex_12B/TriplexMonitorNoFail/Output/Single-BranchC-Fail'
 * '<S22>'  : 'triplex_12B/TriplexMonitorNoFail/Output/No-Fail/Avg3'
 * '<S23>'  : 'triplex_12B/TriplexMonitorNoFail/Output/No-Fail/choose'
 * '<S24>'  : 'triplex_12B/TriplexMonitorNoFail/Output/No-Fail/choose1'
 * '<S25>'  : 'triplex_12B/TriplexMonitorNoFail/Output/Single-BranchA-Fail/Avg2'
 * '<S26>'  : 'triplex_12B/TriplexMonitorNoFail/Output/Single-BranchB-Fail/Avg2'
 * '<S27>'  : 'triplex_12B/TriplexMonitorNoFail/Output/Single-BranchC-Fail/Avg2'
 */
#endif                                 /* triplex_12B_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
