/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: triplex_12B.c
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

#include "triplex_12B.h"
#include <math.h>
#include "rtwtypes.h"

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Model step function */
void triplex_12B_step(void)
{
  real_T rtb_Abs1;
  real_T rtb_Switch;
  int32_T rtb_Delay1_idx_0;
  int32_T rtb_Delay1_idx_1;
  int32_T rtb_Delay1_idx_2;
  boolean_T rtb_LogicalOperator6;
  boolean_T rtb_RelationalOperator1;
  boolean_T rtb_RelationalOperator2;
  boolean_T rtb_RelationalOperator3;
  boolean_T rtb_RelationalOperator4;
  boolean_T rtb_RelationalOperator4_tmp;
  boolean_T rtb_RelationalOperator4_tmp_0;
  boolean_T rtb_RelationalOperator4_tmp_1;
  boolean_T rtb_RelationalOperator4_tmp_2;
  boolean_T rtb_RelationalOperator_o;

  /* Delay: '<S1>/Delay1' */
  rtb_Delay1_idx_0 = rtDW.Delay1_DSTATE[0];
  rtb_Delay1_idx_1 = rtDW.Delay1_DSTATE[1];
  rtb_Delay1_idx_2 = rtDW.Delay1_DSTATE[2];

  /* RelationalOperator: '<S3>/Relational Operator3' */
  rtb_RelationalOperator3 = (rtb_Delay1_idx_0 > 0);

  /* RelationalOperator: '<S3>/Relational Operator' incorporates:
   *  Abs: '<S3>/Abs'
   *  Inport: '<Root>/Tlevel'
   *  Inport: '<Root>/ia'
   *  Inport: '<Root>/ib'
   *  Sum: '<S3>/Sum'
   */
  rtb_RelationalOperator_o = (fabs(rtU.ia - rtU.ib) > rtU.Tlevel);

  /* RelationalOperator: '<S3>/Relational Operator1' incorporates:
   *  Abs: '<S3>/Abs1'
   *  Inport: '<Root>/Tlevel'
   *  Inport: '<Root>/ib'
   *  Inport: '<Root>/ic'
   *  Sum: '<S3>/Sum1'
   */
  rtb_RelationalOperator1 = (fabs(rtU.ib - rtU.ic) > rtU.Tlevel);

  /* RelationalOperator: '<S3>/Relational Operator2' incorporates:
   *  Abs: '<S3>/Abs2'
   *  Inport: '<Root>/Tlevel'
   *  Inport: '<Root>/ia'
   *  Inport: '<Root>/ic'
   *  Sum: '<S3>/Sum2'
   */
  rtb_RelationalOperator2 = (fabs(rtU.ia - rtU.ic) > rtU.Tlevel);

  /* Logic: '<S16>/Logical Operator5' incorporates:
   *  Logic: '<S13>/Logical Operator12'
   *  Logic: '<S14>/Logical Operator24'
   */
  rtb_RelationalOperator4_tmp = !rtb_RelationalOperator2;

  /* Logic: '<S16>/Logical Operator2' incorporates:
   *  Logic: '<S13>/Logical Operator10'
   */
  rtb_RelationalOperator4_tmp_0 = !rtb_RelationalOperator1;

  /* Logic: '<S16>/Logical Operator1' incorporates:
   *  Logic: '<S13>/Logical Operator16'
   */
  rtb_RelationalOperator4_tmp_1 = !rtb_RelationalOperator_o;

  /* Logic: '<S16>/Logical Operator3' incorporates:
   *  Logic: '<S13>/Logical Operator22'
   *  Logic: '<S16>/Logical Operator1'
   *  Logic: '<S16>/Logical Operator2'
   */
  rtb_RelationalOperator4_tmp_2 = (rtb_RelationalOperator4_tmp_1 &&
    rtb_RelationalOperator4_tmp_0);

  /* Logic: '<S16>/Logical Operator4' incorporates:
   *  Logic: '<S16>/Logical Operator3'
   *  Logic: '<S16>/Logical Operator5'
   */
  rtb_RelationalOperator4 = (rtb_RelationalOperator4_tmp_2 &&
    rtb_RelationalOperator4_tmp);

  /* Logic: '<S16>/Logical Operator6' incorporates:
   *  Logic: '<S16>/Logical Operator7'
   */
  rtb_LogicalOperator6 = ((!rtb_RelationalOperator3) && rtb_RelationalOperator4);

  /* Logic: '<S16>/Logical Operator13' */
  rtb_RelationalOperator3 = (rtb_RelationalOperator4 && rtb_RelationalOperator3);

  /* Logic: '<S13>/Logical Operator11' incorporates:
   *  Logic: '<S14>/Logical Operator29'
   */
  rtb_RelationalOperator4_tmp_0 = (rtb_RelationalOperator_o &&
    rtb_RelationalOperator4_tmp_0);

  /* Logic: '<S13>/Logical Operator15' incorporates:
   *  Logic: '<S14>/Logical Operator35'
   */
  rtb_RelationalOperator4_tmp_1 = (rtb_RelationalOperator4_tmp_1 &&
    rtb_RelationalOperator1);

  /* RelationalOperator: '<S3>/Relational Operator4' incorporates:
   *  Inport: '<Root>/PClimit'
   */
  rtb_RelationalOperator4 = (rtb_Delay1_idx_0 > rtU.PClimit);

  /* If: '<S2>/If' incorporates:
   *  Logic: '<S13>/Logical Operator11'
   *  Logic: '<S13>/Logical Operator14'
   *  Logic: '<S13>/Logical Operator15'
   *  Logic: '<S13>/Logical Operator17'
   *  Logic: '<S13>/Logical Operator21'
   *  Logic: '<S13>/Logical Operator8'
   *  Logic: '<S13>/Logical Operator9'
   *  Logic: '<S14>/Logical Operator19'
   *  Logic: '<S14>/Logical Operator25'
   *  Logic: '<S14>/Logical Operator26'
   *  Logic: '<S14>/Logical Operator27'
   *  Logic: '<S14>/Logical Operator28'
   *  Logic: '<S14>/Logical Operator30'
   *  Logic: '<S14>/Logical Operator31'
   *  Logic: '<S14>/Logical Operator34'
   *  Logic: '<S14>/Logical Operator36'
   *  Logic: '<S15>/Logical Operator4'
   *  Logic: '<S17>/Logical Operator1'
   *  Logic: '<S17>/Logical Operator19'
   *  Logic: '<S17>/Logical Operator28'
   */
  if (rtb_LogicalOperator6) {
    /* Outputs for IfAction SubSystem: '<S2>/Act1' incorporates:
     *  ActionPort: '<S5>/Action Port'
     */
    /* Merge: '<S2>/Merge' incorporates:
     *  Constant: '<S5>/Constant1'
     *  SignalConversion: '<S5>/Signal Conversion'
     */
    rtDW.Merge_e[0] = 0;
    rtDW.Merge_e[1] = rtb_Delay1_idx_1;
    rtDW.Merge_e[2] = rtb_Delay1_idx_2;

    /* End of Outputs for SubSystem: '<S2>/Act1' */
  } else if (rtb_RelationalOperator3) {
    /* Outputs for IfAction SubSystem: '<S2>/Act2' incorporates:
     *  ActionPort: '<S6>/Action Port'
     */
    /* Merge: '<S2>/Merge' incorporates:
     *  Constant: '<S6>/Constant1'
     *  SignalConversion: '<S6>/Signal Conversion'
     *  Sum: '<S6>/Sum'
     */
    rtDW.Merge_e[0] = rtb_Delay1_idx_0 - 1;
    rtDW.Merge_e[1] = rtb_Delay1_idx_1;
    rtDW.Merge_e[2] = rtb_Delay1_idx_2;

    /* End of Outputs for SubSystem: '<S2>/Act2' */
  } else if ((rtb_RelationalOperator4_tmp_0 && rtb_RelationalOperator4_tmp) ||
             (rtb_RelationalOperator4_tmp && rtb_RelationalOperator4_tmp_1) ||
             (rtb_RelationalOperator2 && rtb_RelationalOperator4_tmp_2)) {
    /* Outputs for IfAction SubSystem: '<S2>/Act3' incorporates:
     *  ActionPort: '<S7>/Action Port'
     */
    /* Merge: '<S2>/Merge' incorporates:
     *  SignalConversion generated from: '<S7>/state'
     */
    rtDW.Merge_e[0] = rtb_Delay1_idx_0;
    rtDW.Merge_e[1] = rtb_Delay1_idx_1;
    rtDW.Merge_e[2] = rtb_Delay1_idx_2;

    /* End of Outputs for SubSystem: '<S2>/Act3' */
  } else {
    /* Logic: '<S14>/Logical Operator26' incorporates:
     *  Logic: '<S14>/Logical Operator32'
     *  Logic: '<S14>/Logical Operator37'
     */
    rtb_RelationalOperator3 = !rtb_RelationalOperator4;

    /* Logic: '<S14>/Logical Operator20' incorporates:
     *  Logic: '<S15>/Logical Operator3'
     */
    rtb_RelationalOperator_o = (rtb_RelationalOperator_o &&
      rtb_RelationalOperator1);

    /* Logic: '<S14>/Logical Operator25' incorporates:
     *  Logic: '<S14>/Logical Operator20'
     *  Logic: '<S17>/Logical Operator25'
     */
    rtb_RelationalOperator4_tmp = (rtb_RelationalOperator_o &&
      rtb_RelationalOperator4_tmp);

    /* Logic: '<S14>/Logical Operator31' incorporates:
     *  Logic: '<S17>/Logical Operator31'
     */
    rtb_RelationalOperator4_tmp_0 = (rtb_RelationalOperator4_tmp_0 &&
      rtb_RelationalOperator2);

    /* Logic: '<S14>/Logical Operator36' incorporates:
     *  Logic: '<S17>/Logical Operator3'
     */
    rtb_RelationalOperator4_tmp_1 = (rtb_RelationalOperator4_tmp_1 &&
      rtb_RelationalOperator2);
    if ((rtb_RelationalOperator4_tmp && rtb_RelationalOperator3) ||
        (rtb_RelationalOperator4_tmp_0 && rtb_RelationalOperator3) ||
        (rtb_RelationalOperator4_tmp_1 && rtb_RelationalOperator3)) {
      /* Outputs for IfAction SubSystem: '<S2>/Act4' incorporates:
       *  ActionPort: '<S8>/Action Port'
       */
      /* Merge: '<S2>/Merge' incorporates:
       *  Constant: '<S8>/Constant1'
       *  SignalConversion: '<S8>/Signal Conversion'
       *  Sum: '<S8>/Sum'
       *  Sum: '<S8>/Sum1'
       */
      rtDW.Merge_e[0] = rtb_Delay1_idx_0 + 1;
      rtDW.Merge_e[1] = rtb_Delay1_idx_1 + 1;
      rtDW.Merge_e[2] = rtb_Delay1_idx_2;

      /* End of Outputs for SubSystem: '<S2>/Act4' */
    } else if (rtb_RelationalOperator4_tmp && rtb_RelationalOperator4) {
      /* Outputs for IfAction SubSystem: '<S2>/Act5' incorporates:
       *  ActionPort: '<S9>/Action Port'
       */
      /* Merge: '<S2>/Merge' incorporates:
       *  Constant: '<S9>/Constant'
       *  Constant: '<S9>/Constant1'
       *  SignalConversion: '<S9>/Signal Conversion'
       */
      rtDW.Merge_e[0] = 0;
      rtDW.Merge_e[1] = rtb_Delay1_idx_1;
      rtDW.Merge_e[2] = 2;

      /* End of Outputs for SubSystem: '<S2>/Act5' */
    } else if (rtb_RelationalOperator4_tmp_0 && rtb_RelationalOperator4) {
      /* Outputs for IfAction SubSystem: '<S2>/Act6' incorporates:
       *  ActionPort: '<S10>/Action Port'
       */
      /* Merge: '<S2>/Merge' incorporates:
       *  Constant: '<S10>/Constant'
       *  Constant: '<S10>/Constant1'
       *  SignalConversion: '<S10>/Signal Conversion'
       */
      rtDW.Merge_e[0] = 0;
      rtDW.Merge_e[1] = rtb_Delay1_idx_1;
      rtDW.Merge_e[2] = 4;

      /* End of Outputs for SubSystem: '<S2>/Act6' */
    } else if (rtb_RelationalOperator4_tmp_1 && rtb_RelationalOperator4) {
      /* Outputs for IfAction SubSystem: '<S2>/Act7' incorporates:
       *  ActionPort: '<S11>/Action Port'
       */
      /* Merge: '<S2>/Merge' incorporates:
       *  Constant: '<S11>/Constant'
       *  Constant: '<S11>/Constant1'
       *  SignalConversion: '<S11>/Signal Conversion'
       */
      rtDW.Merge_e[0] = 0;
      rtDW.Merge_e[1] = rtb_Delay1_idx_1;
      rtDW.Merge_e[2] = 1;

      /* End of Outputs for SubSystem: '<S2>/Act7' */
    } else if (rtb_RelationalOperator_o && rtb_RelationalOperator2) {
      /* Outputs for IfAction SubSystem: '<S2>/Act8' incorporates:
       *  ActionPort: '<S12>/Action Port'
       */
      /* Merge: '<S2>/Merge' incorporates:
       *  Constant: '<S12>/Constant1'
       *  SignalConversion: '<S12>/Signal Conversion'
       *  Sum: '<S12>/Sum1'
       */
      rtDW.Merge_e[0] = rtb_Delay1_idx_0;
      rtDW.Merge_e[1] = rtb_Delay1_idx_1 + 1;
      rtDW.Merge_e[2] = rtb_Delay1_idx_2;

      /* End of Outputs for SubSystem: '<S2>/Act8' */
    }
  }

  /* End of If: '<S2>/If' */

  /* Outport: '<Root>/PC' */
  rtY.PC = rtDW.Merge_e[0];

  /* Outport: '<Root>/TC' */
  rtY.TC = rtDW.Merge_e[1];

  /* Outport: '<Root>/FC' */
  rtY.FC = rtDW.Merge_e[2];

  /* If: '<S4>/If' */
  if (rtDW.Merge_e[2] == 0) {
    /* Outputs for IfAction SubSystem: '<S4>/No-Fail' incorporates:
     *  ActionPort: '<S18>/Action Port'
     */
    /* Product: '<S22>/Divide' incorporates:
     *  Constant: '<S22>/Constant'
     *  Inport: '<Root>/ia'
     *  Inport: '<Root>/ib'
     *  Inport: '<Root>/ic'
     *  Sum: '<S22>/Sum'
     *  Sum: '<S22>/Sum1'
     */
    rtb_Abs1 = ((rtU.ia + rtU.ib) + rtU.ic) / 3.0;

    /* Switch: '<S23>/Switch' incorporates:
     *  Abs: '<S23>/Abs'
     *  Abs: '<S23>/Abs1'
     *  Inport: '<Root>/ia'
     *  Inport: '<Root>/ib'
     *  RelationalOperator: '<S23>/Relational Operator'
     *  Sum: '<S23>/Sum'
     *  Sum: '<S23>/Sum1'
     */
    if (fabs(rtU.ia - rtb_Abs1) > fabs(rtU.ib - rtb_Abs1)) {
      rtb_Switch = rtU.ib;
    } else {
      rtb_Switch = rtU.ia;
    }

    /* End of Switch: '<S23>/Switch' */

    /* Switch: '<S24>/Switch' incorporates:
     *  Abs: '<S24>/Abs'
     *  Abs: '<S24>/Abs1'
     *  Inport: '<Root>/ic'
     *  RelationalOperator: '<S24>/Relational Operator'
     *  Sum: '<S24>/Sum'
     *  Sum: '<S24>/Sum1'
     */
    if (fabs(rtb_Switch - rtb_Abs1) > fabs(rtU.ic - rtb_Abs1)) {
      /* Merge: '<S4>/Merge' */
      rtDW.Merge = rtU.ic;
    } else {
      /* Merge: '<S4>/Merge' */
      rtDW.Merge = rtb_Switch;
    }

    /* End of Switch: '<S24>/Switch' */
    /* End of Outputs for SubSystem: '<S4>/No-Fail' */
  } else if (rtDW.Merge_e[2] == 1) {
    /* Outputs for IfAction SubSystem: '<S4>/Single-BranchC-Fail' incorporates:
     *  ActionPort: '<S21>/Action Port'
     */
    /* Merge: '<S4>/Merge' incorporates:
     *  Constant: '<S27>/Constant'
     *  Inport: '<Root>/ia'
     *  Inport: '<Root>/ib'
     *  Product: '<S27>/Divide'
     *  Sum: '<S27>/Sum'
     */
    rtDW.Merge = (rtU.ia + rtU.ib) / 2.0;

    /* End of Outputs for SubSystem: '<S4>/Single-BranchC-Fail' */
  } else if (rtDW.Merge_e[2] == 2) {
    /* Outputs for IfAction SubSystem: '<S4>/Single-BranchB-Fail' incorporates:
     *  ActionPort: '<S20>/Action Port'
     */
    /* Merge: '<S4>/Merge' incorporates:
     *  Constant: '<S26>/Constant'
     *  Inport: '<Root>/ia'
     *  Inport: '<Root>/ic'
     *  Product: '<S26>/Divide'
     *  Sum: '<S26>/Sum'
     */
    rtDW.Merge = (rtU.ia + rtU.ic) / 2.0;

    /* End of Outputs for SubSystem: '<S4>/Single-BranchB-Fail' */
  } else if (rtDW.Merge_e[2] == 4) {
    /* Outputs for IfAction SubSystem: '<S4>/Single-BranchA-Fail' incorporates:
     *  ActionPort: '<S19>/Action Port'
     */
    /* Merge: '<S4>/Merge' incorporates:
     *  Constant: '<S25>/Constant'
     *  Inport: '<Root>/ib'
     *  Inport: '<Root>/ic'
     *  Product: '<S25>/Divide'
     *  Sum: '<S25>/Sum'
     */
    rtDW.Merge = (rtU.ib + rtU.ic) / 2.0;

    /* End of Outputs for SubSystem: '<S4>/Single-BranchA-Fail' */
  }

  /* End of If: '<S4>/If' */

  /* Outport: '<Root>/sel_val' */
  rtY.sel_val = rtDW.Merge;

  /* Update for Delay: '<S1>/Delay1' */
  rtDW.Delay1_DSTATE[0] = rtDW.Merge_e[0];
  rtDW.Delay1_DSTATE[1] = rtDW.Merge_e[1];
  rtDW.Delay1_DSTATE[2] = rtDW.Merge_e[2];
}

/* Model initialize function */
void triplex_12B_initialize(void)
{
  /* (no initialization code required) */
  
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
