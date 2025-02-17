/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: regs_12B.h
 *
 * Code generated for Simulink model 'regs_12B'.
 *
 * Model version                  : 1.20
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Sun Nov  3 11:51:39 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 10
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef regs_12B_h_
#define regs_12B_h_
#ifndef regs_12B_COMMON_INCLUDES_
#define regs_12B_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* regs_12B_COMMON_INCLUDES_ */

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
  real_T UnitDelay_DSTATE;             /* '<S13>/Unit Delay' */
  real_T UnitDelay1_DSTATE;            /* '<S13>/Unit Delay1' */
  real_T UnitDelay1_DSTATE_k;          /* '<S16>/Unit Delay1' */
  real_T UnitDelay_DSTATE_o;           /* '<S16>/Unit Delay' */
  real_T Memory_PreviousInput;         /* '<S9>/Memory' */
} DW;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: transition_v
   * Referenced by: '<S12>/transition1'
   */
  real_T transition1_XData[4];

  /* Expression: transition_y
   * Referenced by: '<S12>/transition1'
   */
  real_T transition1_YData[4];

  /* Expression: [120 185]
   * Referenced by: '<S10>/transition_bvr'
   */
  real_T transition_bvr_XData[2];

  /* Expression: [15 20]
   * Referenced by: '<S10>/transition_bvr'
   */
  real_T transition_bvr_YData[2];
} ConstP;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T beta_adc_deg;                 /* '<Root>/beta_adc_deg' */
  real_T vtas_adc_kts;                 /* '<Root>/vtas_adc_kts' */
  real_T lcv_cmd_fcs_dps;              /* '<Root>/lcv_cmd_fcs_dps ' */
  real_T hdg_des_deg;                  /* '<Root>/hdg_des_deg' */
  real_T mcv_cmd_fcs_dps;              /* '<Root>/mcv_cmd_fcs_dps' */
  real_T alt_des_ft;                   /* '<Root>/alt_des_ft' */
  real_T ncv_cmd_fcs_dps;              /* '<Root>/ncv_cmd_fcs_dps' */
  real_T xcv_cmd_fcs_fps;              /* '<Root>/xcv_cmd_fcs_fps' */
  real_T airspeed_des_fps;             /* '<Root>/airspeed_des_fps' */
  real_T hcv_cmd_fcs_fps;              /* '<Root>/hcv_cmd_fcs_fps' */
  real_T lcv_fps_dps;                  /* '<Root>/lcv_fps_dps' */
  real_T mcv_fcs_dps;                  /* '<Root>/mcv_fcs_dps' */
  real_T ncv_fcs_dps;                  /* '<Root>/ncv_fcs_dps' */
  real_T dcv_fcs_fps;                  /* '<Root>/dcv_fcs_fps' */
  real_T zcv_fcs_fps;                  /* '<Root>/zcv_fcs_fps' */
  real_T beta_dot;                     /* '<Root>/beta_dot' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T lcvdt_cmd_fcs_dps2;           /* '<Root>/lcvdt_cmd_fcs_dps2' */
  real_T mcvdt_cmd_fcs_dps2;           /* '<Root>/mcvdt_cmd_fcs_dps2' */
  real_T ncvdt_cmd_fcs_dps2;           /* '<Root>/ncvdt_cmd_fcs_dps2' */
  real_T xcvdt_cmd_fcs_fps2;           /* '<Root>/xcvdt_cmd_fcs_fps2' */
  real_T hcvdt_cmd_fcs_fps2;           /* '<Root>/hcvdt_cmd_fcs_fps2' */
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

/* Constant parameters (default storage) */
extern const ConstP rtConstP;

/* Model entry point functions */
extern void regs_12B_initialize(void);
extern void regs_12B_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S14>/Data Type Duplicate' : Unused code path elimination
 * Block '<S14>/Data Type Propagation' : Unused code path elimination
 * Block '<S17>/Data Type Duplicate' : Unused code path elimination
 * Block '<S17>/Data Type Propagation' : Unused code path elimination
 * Block '<S5>/Signal Conversion' : Eliminate redundant signal conversion block
 * Block '<S5>/Signal Conversion1' : Eliminate redundant signal conversion block
 * Block '<S9>/-8' : Eliminated nontunable gain of 1
 * Block '<S9>/Kp=1.0' : Eliminated nontunable gain of 1
 * Block '<S12>/Gain' : Eliminated nontunable gain of 1
 * Block '<S9>/Constant1' : Unused code path elimination
 * Block '<S9>/Constant5' : Unused code path elimination
 * Block '<S10>/Constant1' : Unused code path elimination
 * Block '<S10>/Constant5' : Unused code path elimination
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
 * '<Root>' : 'regs_12B'
 * '<S1>'   : 'regs_12B/Inputs'
 * '<S2>'   : 'regs_12B/Regulators'
 * '<S3>'   : 'regs_12B/Inputs/CVcmd'
 * '<S4>'   : 'regs_12B/Inputs/Input'
 * '<S5>'   : 'regs_12B/Inputs/Subsystem'
 * '<S6>'   : 'regs_12B/Inputs/betad'
 * '<S7>'   : 'regs_12B/Inputs/Input/egi_fcs_in'
 * '<S8>'   : 'regs_12B/Regulators/AirspeedRegulator'
 * '<S9>'   : 'regs_12B/Regulators/HeightRegulator'
 * '<S10>'  : 'regs_12B/Regulators/PitchRegulator'
 * '<S11>'  : 'regs_12B/Regulators/RollRegulator'
 * '<S12>'  : 'regs_12B/Regulators/YawRegulator'
 * '<S13>'  : 'regs_12B/Regulators/HeightRegulator/Tustin Integrator (Limited, Resettable, States)'
 * '<S14>'  : 'regs_12B/Regulators/HeightRegulator/Tustin Integrator (Limited, Resettable, States)/Saturation Dynamic'
 * '<S15>'  : 'regs_12B/Regulators/HeightRegulator/Tustin Integrator (Limited, Resettable, States)/bounds'
 * '<S16>'  : 'regs_12B/Regulators/PitchRegulator/Tustin Integrator (Limited, Resettable, States)'
 * '<S17>'  : 'regs_12B/Regulators/PitchRegulator/Tustin Integrator (Limited, Resettable, States)/Saturation Dynamic'
 * '<S18>'  : 'regs_12B/Regulators/PitchRegulator/Tustin Integrator (Limited, Resettable, States)/bounds'
 */
#endif                                 /* regs_12B_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
