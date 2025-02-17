/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: swim_12B.h
 *
 * Code generated for Simulink model 'swim_12B'.
 *
 * Model version                  : 1.18
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Sun Nov  3 13:54:23 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef swim_12B_h_
#define swim_12B_h_
#ifndef swim_12B_COMMON_INCLUDES_
#define swim_12B_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* swim_12B_COMMON_INCLUDES_ */

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T UnitDelay_DSTATE;             /* '<S2>/Unit Delay' */
  real_T UnitDelay_DSTATE_d;           /* '<S7>/Unit Delay' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T muxGet_T_Mux_AircraftGrossWeigh;
                             /* '<Root>/muxGet_T_Mux_AircraftGrossWeight_lbs' */
  int32_T diGet_S_CatSwitchPosition;   /* '<Root>/diGet_S_CatSwitchPosition' */
  real_T E_AI_IMPACT_PRESSURE;         /* '<Root>/E_AI_IMPACT_PRESSURE' */
  boolean_T diGet_S_LandingGearAltFlap;/* '<Root>/diGet_S_LandingGearAltFlap' */
  boolean_T muxGet_T_Mux_AirspeedMonitorEna;
                               /* '<Root>/muxGet_T_Mux_AirspeedMonitorEnable' */
  boolean_T cvGet_V_AgcasLowSpeedWarn; /* '<Root>/cvGet_V_AgcasLowSpeedWarn' */
  boolean_T olcGet_AgcasInterlocks;    /* '<Root>/olcGet_AgcasInterlocks' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T swimGet_AgcasLowSpeedWarn;    /* '<Root>/swimGet_AgcasLowSpeedWarn' */
  real_T swimGet_QcMinDisable_lbspft2;
                                     /* '<Root>/swimGet_QcMinDisable_lbspft2' */
  real_T SWIM_Qcmin_lbspft2;           /* '<Root>/SWIM_Qcmin_lbspft2' */
  real_T SWIM_CalAirspeedmin_kts;      /* '<Root>/SWIM_CalAirspeedmin_kts' */
  real_T SWIM_ASWarningAllowed;        /* '<Root>/SWIM_ASWarningAllowed' */
} ExtY;

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/* Model entry point functions */
extern void swim_12B_initialize(void);
extern void swim_12B_step(void);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Display' : Unused code path elimination
 * Block '<S1>/Display1' : Unused code path elimination
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
 * '<Root>' : 'swim_12B'
 * '<S1>'   : 'swim_12B/swim_airspeed'
 * '<S2>'   : 'swim_12B/swim_airspeed/Airspeed Monitoring'
 * '<S3>'   : 'swim_12B/swim_airspeed/Calculate minimum impact pressure for AGCAS operation to be suspended and sent to standby'
 * '<S4>'   : 'swim_12B/swim_airspeed/Calculate minimum impact pressure for warning to pilot that AGCAS operation is degraded'
 * '<S5>'   : 'swim_12B/swim_airspeed/Calculate the minimum calibrated airspeed based on Cat Switch'
 * '<S6>'   : 'swim_12B/swim_airspeed/Get the aircraft weight'
 * '<S7>'   : 'swim_12B/swim_airspeed/IssueWarning'
 * '<S8>'   : 'swim_12B/swim_airspeed/Airspeed Monitoring/If Action Subsystem'
 * '<S9>'   : 'swim_12B/swim_airspeed/Airspeed Monitoring/If Action Subsystem1'
 * '<S10>'  : 'swim_12B/swim_airspeed/Airspeed Monitoring/If Action Subsystem2'
 * '<S11>'  : 'swim_12B/swim_airspeed/Airspeed Monitoring/If Action Subsystem3'
 * '<S12>'  : 'swim_12B/swim_airspeed/Calculate the minimum calibrated airspeed based on Cat Switch/If Action Subsystem'
 * '<S13>'  : 'swim_12B/swim_airspeed/Calculate the minimum calibrated airspeed based on Cat Switch/If Action Subsystem1'
 * '<S14>'  : 'swim_12B/swim_airspeed/IssueWarning/If Action Subsystem'
 * '<S15>'  : 'swim_12B/swim_airspeed/IssueWarning/If Action Subsystem1'
 * '<S16>'  : 'swim_12B/swim_airspeed/IssueWarning/If Action Subsystem/If Action Subsystem'
 * '<S17>'  : 'swim_12B/swim_airspeed/IssueWarning/If Action Subsystem/If Action Subsystem1'
 */
#endif                                 /* swim_12B_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
