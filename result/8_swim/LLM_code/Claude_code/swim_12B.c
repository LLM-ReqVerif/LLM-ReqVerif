/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: swim_12B.c
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

#include "swim_12B.h"
#include <math.h>
#include "rtwtypes.h"

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Model step function */
void swim_12B_step(void)
{
  real_T rtb_Gain1;
  real_T rtb_Merge1;
  real_T rtb_Merge_d;
  real_T rtb_Sum_p;

  /* If: '<S5>/If' incorporates:
   *  Inport: '<Root>/diGet_S_CatSwitchPosition'
   *  RelationalOperator: '<S5>/Relational Operator'
   */
  if (rtU.diGet_S_CatSwitchPosition == 0) {
    /* Outputs for IfAction SubSystem: '<S5>/If Action Subsystem' incorporates:
     *  ActionPort: '<S12>/Action Port'
     */
    /* Sum: '<S12>/Sum' incorporates:
     *  Constant: '<S12>/Constant'
     *  Gain: '<S12>/Gain'
     *  Inport: '<Root>/muxGet_T_Mux_AircraftGrossWeight_lbs'
     *  Sqrt: '<S12>/Sqrt'
     */
    double b = rtU.muxGet_T_Mux_AircraftGrossWeigh;
    rtb_Merge_d = 1.25921 * sqrt(rtU.muxGet_T_Mux_AircraftGrossWeigh) + 10.0;

    /* End of Outputs for SubSystem: '<S5>/If Action Subsystem' */
  } else {
    /* Outputs for IfAction SubSystem: '<S5>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S13>/Action Port'
     */
    /* Sum: '<S13>/Sum' incorporates:
     *  Constant: '<S13>/Constant'
     *  Gain: '<S13>/Gain'
     *  Inport: '<Root>/muxGet_T_Mux_AircraftGrossWeight_lbs'
     *  Sqrt: '<S13>/Sqrt'
     */
    rtb_Merge_d = 1.33694 * sqrt(rtU.muxGet_T_Mux_AircraftGrossWeigh) + 10.0;

    /* End of Outputs for SubSystem: '<S5>/If Action Subsystem1' */
  }

  /* End of If: '<S5>/If' */

  /* Gain: '<S4>/Gain1' incorporates:
   *  Constant: '<S4>/Constant1'
   *  Gain: '<S4>/Gain'
   *  Sum: '<S4>/Sum'
   *  Sum: '<S4>/Sum1'
   */
  rtb_Gain1 = ((0.020306 * rtb_Merge_d - 2.0906) + 0.1) * 70.7184;

  /* Outport: '<Root>/swimGet_QcMinDisable_lbspft2' incorporates:
   *  Sum: '<S3>/Sum'
   */
  rtY.swimGet_QcMinDisable_lbspft2 = rtb_Gain1 - 28.72;

  /* If: '<S2>/If1' incorporates:
   *  Constant: '<S10>/Constant'
   *  If: '<S2>/If'
   *  Inport: '<Root>/E_AI_IMPACT_PRESSURE'
   *  Inport: '<Root>/diGet_S_LandingGearAltFlap'
   *  Logic: '<S2>/Logical Operator'
   *  RelationalOperator: '<S2>/Relational Operator'
   *  RelationalOperator: '<S2>/Relational Operator3'
   */
  if (!rtU.diGet_S_LandingGearAltFlap) {
    /* Outputs for IfAction SubSystem: '<S2>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S10>/Action Port'
     */
    rtb_Merge1 = 0.0;

    /* End of Outputs for SubSystem: '<S2>/If Action Subsystem2' */
  } else if (rtU.diGet_S_LandingGearAltFlap && (rtU.E_AI_IMPACT_PRESSURE >
              rtb_Gain1)) {
    /* Outputs for IfAction SubSystem: '<S2>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S11>/Action Port'
     */
    /* Outputs for IfAction SubSystem: '<S2>/If Action Subsystem' incorporates:
     *  ActionPort: '<S8>/Action Port'
     */
    /* If: '<S2>/If' incorporates:
     *  Constant: '<S8>/Constant'
     *  SignalConversion generated from: '<S11>/In1'
     */
    rtb_Merge1 = 1.0;

    /* End of Outputs for SubSystem: '<S2>/If Action Subsystem' */
    /* End of Outputs for SubSystem: '<S2>/If Action Subsystem3' */
  } else {
    /* Outputs for IfAction SubSystem: '<S2>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S11>/Action Port'
     */
    /* SignalConversion generated from: '<S11>/In1' incorporates:
     *  UnitDelay: '<S2>/Unit Delay'
     */
    rtb_Merge1 = rtDW.UnitDelay_DSTATE;

    /* End of Outputs for SubSystem: '<S2>/If Action Subsystem3' */
  }

  /* End of If: '<S2>/If1' */

  /* If: '<S7>/If' incorporates:
   *  Constant: '<S7>/Constant4'
   *  Inport: '<Root>/cvGet_V_AgcasLowSpeedWarn'
   *  Inport: '<Root>/muxGet_T_Mux_AirspeedMonitorEnable'
   *  Inport: '<Root>/olcGet_AgcasInterlocks'
   *  Logic: '<S7>/Logical Operator1'
   *  Logic: '<S7>/Logical Operator2'
   *  RelationalOperator: '<S7>/Relational Operator3'
   *  RelationalOperator: '<S7>/Relational Operator4'
   */
  if ((rtU.muxGet_T_Mux_AirspeedMonitorEna || rtU.cvGet_V_AgcasLowSpeedWarn) &&
      (!rtU.olcGet_AgcasInterlocks) && (rtb_Merge1 == 1.0)) {
    /* Outputs for IfAction SubSystem: '<S7>/If Action Subsystem' incorporates:
     *  ActionPort: '<S14>/Action Port'
     */
    /* Outputs for IfAction SubSystem: '<S14>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S17>/Action Port'
     */
    /* Outputs for IfAction SubSystem: '<S14>/If Action Subsystem' incorporates:
     *  ActionPort: '<S16>/Action Port'
     */
    /* If: '<S14>/If' incorporates:
     *  Constant: '<S16>/Constant'
     *  Constant: '<S17>/Constant'
     *  Inport: '<Root>/E_AI_IMPACT_PRESSURE'
     *  RelationalOperator: '<S14>/Relational Operator'
     *  Sum: '<S3>/Sum'
     */
    rtb_Sum_p = (rtU.E_AI_IMPACT_PRESSURE < rtb_Gain1 - 28.72);

    /* End of Outputs for SubSystem: '<S14>/If Action Subsystem' */
    /* End of Outputs for SubSystem: '<S14>/If Action Subsystem1' */
    /* End of Outputs for SubSystem: '<S7>/If Action Subsystem' */
  } else {
    /* Outputs for IfAction SubSystem: '<S7>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S15>/Action Port'
     */
    /* SignalConversion generated from: '<S15>/In1' incorporates:
     *  UnitDelay: '<S7>/Unit Delay'
     */
    rtb_Sum_p = rtDW.UnitDelay_DSTATE_d;

    /* End of Outputs for SubSystem: '<S7>/If Action Subsystem1' */
  }

  /* End of If: '<S7>/If' */

  /* Outport: '<Root>/SWIM_Qcmin_lbspft2' */
  rtY.SWIM_Qcmin_lbspft2 = rtb_Gain1;

  /* Outport: '<Root>/swimGet_AgcasLowSpeedWarn' */
  rtY.swimGet_AgcasLowSpeedWarn = rtb_Sum_p;

  /* Outport: '<Root>/SWIM_ASWarningAllowed' */
  rtY.SWIM_ASWarningAllowed = rtb_Merge1;

  /* Outport: '<Root>/SWIM_CalAirspeedmin_kts' */
  rtY.SWIM_CalAirspeedmin_kts = rtb_Merge_d;

  /* Update for UnitDelay: '<S2>/Unit Delay' */
  rtDW.UnitDelay_DSTATE = rtb_Merge1;

  /* Update for UnitDelay: '<S7>/Unit Delay' */
  rtDW.UnitDelay_DSTATE_d = rtb_Sum_p;
}

/* Model initialize function */
void swim_12B_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
