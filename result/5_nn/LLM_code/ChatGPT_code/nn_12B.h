/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: nn_12B.h
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

#ifndef nn_12B_h_
#define nn_12B_h_
#ifndef nn_12B_COMMON_INCLUDES_
#define nn_12B_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* nn_12B_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: w1'
   * Referenced by: '<S1>/Weights to Layer1'
   */
  real_T WeightstoLayer1_Value[20];

  /* Expression: w2'
   * Referenced by: '<S1>/Weights to Layer2'
   */
  real_T WeightstoLayer2_Value[100];

  /* Expression: w3
   * Referenced by: '<S1>/Weights to Output Layer'
   */
  real_T WeightstoOutputLayer_Value[10];

  /* Expression: b1
   * Referenced by: '<S1>/b1'
   */
  real_T b1_Value[10];

  /* Expression: b2
   * Referenced by: '<S1>/b2'
   */
  real_T b2_Value[10];
} ConstParam;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T x;                            /* '<Root>/x' */
  real_T y;                            /* '<Root>/y' */
} ExternalInputs;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T z;                            /* '<Root>/z' */
} ExternalOutputs;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* External inputs (root inport signals with default storage) */
extern ExternalInputs rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExternalOutputs rtY;

/* Constant parameters (default storage) */
extern const ConstParam rtConstP;

/* Model entry point functions */
extern void nn_12B_initialize(void);
extern void nn_12B_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

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
 * '<Root>' : 'nn_12B'
 * '<S1>'   : 'nn_12B/nn_2x10x10x1'
 * '<S2>'   : 'nn_12B/nn_2x10x10x1/Neuron Layer 1'
 * '<S3>'   : 'nn_12B/nn_2x10x10x1/Neuron Layer 2'
 * '<S4>'   : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 1'
 * '<S5>'   : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 10'
 * '<S6>'   : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 2'
 * '<S7>'   : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 3'
 * '<S8>'   : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 4'
 * '<S9>'   : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 5'
 * '<S10>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 6'
 * '<S11>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 7'
 * '<S12>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 8'
 * '<S13>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 9'
 * '<S14>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 1/If Action Subsystem'
 * '<S15>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 1/If Action Subsystem1'
 * '<S16>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 1/If Action Subsystem2'
 * '<S17>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 1/If Action Subsystem3'
 * '<S18>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 10/If Action Subsystem'
 * '<S19>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 10/If Action Subsystem1'
 * '<S20>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 10/If Action Subsystem2'
 * '<S21>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 10/If Action Subsystem3'
 * '<S22>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 2/If Action Subsystem'
 * '<S23>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 2/If Action Subsystem1'
 * '<S24>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 2/If Action Subsystem2'
 * '<S25>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 2/If Action Subsystem3'
 * '<S26>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 3/If Action Subsystem'
 * '<S27>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 3/If Action Subsystem1'
 * '<S28>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 3/If Action Subsystem2'
 * '<S29>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 3/If Action Subsystem3'
 * '<S30>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 4/If Action Subsystem'
 * '<S31>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 4/If Action Subsystem1'
 * '<S32>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 4/If Action Subsystem2'
 * '<S33>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 4/If Action Subsystem3'
 * '<S34>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 5/If Action Subsystem'
 * '<S35>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 5/If Action Subsystem1'
 * '<S36>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 5/If Action Subsystem2'
 * '<S37>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 5/If Action Subsystem3'
 * '<S38>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 6/If Action Subsystem'
 * '<S39>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 6/If Action Subsystem1'
 * '<S40>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 6/If Action Subsystem2'
 * '<S41>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 6/If Action Subsystem3'
 * '<S42>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 7/If Action Subsystem'
 * '<S43>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 7/If Action Subsystem1'
 * '<S44>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 7/If Action Subsystem2'
 * '<S45>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 7/If Action Subsystem3'
 * '<S46>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 8/If Action Subsystem'
 * '<S47>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 8/If Action Subsystem1'
 * '<S48>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 8/If Action Subsystem2'
 * '<S49>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 8/If Action Subsystem3'
 * '<S50>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 9/If Action Subsystem'
 * '<S51>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 9/If Action Subsystem1'
 * '<S52>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 9/If Action Subsystem2'
 * '<S53>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 1/Neuron 9/If Action Subsystem3'
 * '<S54>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 1'
 * '<S55>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 10'
 * '<S56>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 2'
 * '<S57>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 3'
 * '<S58>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 4'
 * '<S59>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 5'
 * '<S60>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 6'
 * '<S61>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 7'
 * '<S62>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 8'
 * '<S63>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 9'
 * '<S64>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 1/If Action Subsystem'
 * '<S65>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 1/If Action Subsystem1'
 * '<S66>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 1/If Action Subsystem2'
 * '<S67>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 1/If Action Subsystem3'
 * '<S68>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 10/If Action Subsystem'
 * '<S69>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 10/If Action Subsystem1'
 * '<S70>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 10/If Action Subsystem2'
 * '<S71>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 10/If Action Subsystem3'
 * '<S72>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 2/If Action Subsystem'
 * '<S73>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 2/If Action Subsystem1'
 * '<S74>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 2/If Action Subsystem2'
 * '<S75>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 2/If Action Subsystem3'
 * '<S76>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 3/If Action Subsystem'
 * '<S77>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 3/If Action Subsystem1'
 * '<S78>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 3/If Action Subsystem2'
 * '<S79>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 3/If Action Subsystem3'
 * '<S80>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 4/If Action Subsystem'
 * '<S81>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 4/If Action Subsystem1'
 * '<S82>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 4/If Action Subsystem2'
 * '<S83>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 4/If Action Subsystem3'
 * '<S84>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 5/If Action Subsystem'
 * '<S85>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 5/If Action Subsystem1'
 * '<S86>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 5/If Action Subsystem2'
 * '<S87>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 5/If Action Subsystem3'
 * '<S88>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 6/If Action Subsystem'
 * '<S89>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 6/If Action Subsystem1'
 * '<S90>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 6/If Action Subsystem2'
 * '<S91>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 6/If Action Subsystem3'
 * '<S92>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 7/If Action Subsystem'
 * '<S93>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 7/If Action Subsystem1'
 * '<S94>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 7/If Action Subsystem2'
 * '<S95>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 7/If Action Subsystem3'
 * '<S96>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 8/If Action Subsystem'
 * '<S97>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 8/If Action Subsystem1'
 * '<S98>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 8/If Action Subsystem2'
 * '<S99>'  : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 8/If Action Subsystem3'
 * '<S100>' : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 9/If Action Subsystem'
 * '<S101>' : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 9/If Action Subsystem1'
 * '<S102>' : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 9/If Action Subsystem2'
 * '<S103>' : 'nn_12B/nn_2x10x10x1/Neuron Layer 2/Neuron 9/If Action Subsystem3'
 */
#endif                                 /* nn_12B_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
