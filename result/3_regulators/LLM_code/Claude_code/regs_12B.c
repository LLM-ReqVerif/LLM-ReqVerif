/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: regs_12B.c
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

#include "regs_12B.h"
#include "rtwtypes.h"
/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;

#ifndef INTERP
#define INTERP(x,x1,x2,y1,y2)          ( (y1)+(((y2) - (y1))/((x2) - (x1)))*((x)-(x1)) )
#endif

#ifndef ZEROTECHNIQUE
#define ZEROTECHNIQUE

typedef enum {
  NORMAL_INTERP,
  AVERAGE_VALUE,
  MIDDLE_VALUE
} ZeroTechnique;

#endif

static int_T rt_GetLookupIndex(const real_T *x, int_T xlen, real_T u) ;
static real_T rt_Lookup(const real_T *x, int_T xlen, real_T u, const real_T *y);

/*
 * Routine to get the index of the input from a table using binary or
 * interpolation search.
 *
 * Inputs:
 * *x   : Pointer to table, x[0] ....x[xlen-1]
 * xlen : Number of values in xtable
 * u    : input value to look up
 *
 * Output:
 * idx  : the index into the table such that:
 * if u is negative
 * x[idx] <= u < x[idx+1]
 * else
 * x[idx] < u <= x[idx+1]
 *
 * Interpolation Search: If the table contains a large number of nearly
 * uniformly spaced entries, i.e., x[n] vs n is linear then the index
 * corresponding to the input can be found in one shot using the linear
 * interpolation formula. Therefore if you have a look-up table block with
 * many data points, using interpolation search might speed up the code.
 * Compile the generated code with the following flag:
 *
 * make_rtw OPTS=-DDOINTERPSEARCH
 *
 * to enable interpolation search.
 */
static int_T rt_GetLookupIndex(const real_T *x, int_T xlen, real_T u)
{
  int_T idx = 0;
  int_T bottom = 0;
  int_T top = xlen-1;
  int_T retValue = 0;
  boolean_T returnStatus = 0U;

#ifdef DOINTERPSEARCH

  real_T offset = 0;

#endif

  /*
   * Deal with the extreme cases first:
   *   if u <= x[bottom] then return idx = bottom
   *   if u >= x[top]    then return idx = top-1
   */
  if (u <= x[bottom]) {
    retValue = bottom;
    returnStatus = 1U;
  } else if (u >= x[top]) {
    retValue = top-1;
    returnStatus = 1U;
  } else {
    /* else required to ensure safe programming, even *
     * if it's expected that it will never be reached */
  }

  if (returnStatus == 0U) {
    if (u < 0) {
      /* For negative input find index such that: x[idx] <= u < x[idx+1] */
      for (;;) {

#ifdef DOINTERPSEARCH

        offset = (u-x[bottom])/(x[top]-x[bottom]);
        idx = bottom + (int_T)((top-bottom)*(offset-DBL_EPSILON));

#else

        idx = (bottom + top)/2;

#endif

        if (u < x[idx]) {
          top = idx - 1;
        } else if (u >= x[idx+1]) {
          bottom = idx + 1;
        } else {
          /* we have x[idx] <= u < x[idx+1], return idx */
          retValue = idx;
          break;
        }
      }
    } else {
      /* For non-negative input find index such that: x[idx] < u <= x[idx+1] */
      for (;;) {

#ifdef DOINTERPSEARCH

        offset = (u-x[bottom])/(x[top]-x[bottom]);
        idx = bottom + (int_T)((top-bottom)*(offset-DBL_EPSILON));

#else

        idx = (bottom + top)/2;

#endif

        if (u <= x[idx]) {
          top = idx - 1;
        } else if (u > x[idx+1]) {
          bottom = idx + 1;
        } else {
          /* we have x[idx] < u <= x[idx+1], return idx */
          retValue = idx;
          break;
        }
      }
    }
  }

  return retValue;
}

/* 1D lookup routine for data type of real_T. */
static real_T rt_Lookup(const real_T *x, int_T xlen, real_T u, const real_T *y)
{
  int_T idx = rt_GetLookupIndex(x, xlen, u);
  real_T num = y[idx+1] - y[idx];
  real_T den = x[idx+1] - x[idx];

  /* Due to the way the binary search is implemented
     in rt_look.c (rt_GetLookupIndex), den cannot be
     0.  Equivalently, m cannot be inf or nan. */
  real_T m = num/den;
  return (y[idx] + (m * (u - x[idx])));
}

/* Model step function */
void regs_12B_step(void)
{
  real_T rtb_CVdt_cmd;
  real_T rtb_Sum1;
  real_T rtb_Sum1_h;
  real_T rtb_Sum3;

  /* Outport: '<Root>/lcvdt_cmd_fcs_dps2' incorporates:
   *  Constant: '<S11>/one_o_Tau'
   *  Inport: '<Root>/lcv_cmd_fcs_dps '
   *  Inport: '<Root>/lcv_fps_dps'
   *  Product: '<S11>/Product'
   *  Sum: '<S11>/Sum1'
   */
  rtY.lcvdt_cmd_fcs_dps2 = (rtU.lcv_cmd_fcs_dps - rtU.lcv_fps_dps) * 2.5;

  /* Lookup: '<S12>/transition1' incorporates:
   *  Inport: '<Root>/vtas_adc_kts'
   */
  rtb_CVdt_cmd = rt_Lookup(&rtConstP.transition1_XData[0], 4, rtU.vtas_adc_kts,
    &rtConstP.transition1_YData[0]);

  /* Outport: '<Root>/ncvdt_cmd_fcs_dps2' incorporates:
   *  Constant: '<S12>/Constant5'
   *  Inport: '<Root>/beta_adc_deg'
   *  Inport: '<Root>/beta_dot'
   *  Inport: '<Root>/ncv_cmd_fcs_dps'
   *  Inport: '<Root>/ncv_fcs_dps'
   *  Product: '<S12>/Product10'
   *  Product: '<S12>/Product5'
   *  Product: '<S12>/Product6'
   *  Product: '<S12>/Product7'
   *  Product: '<S12>/Product9'
   *  Sum: '<S12>/Sum11'
   *  Sum: '<S12>/Sum12'
   *  Sum: '<S12>/Sum4'
   *  Sum: '<S12>/Sum9'
   */
  rtY.ncvdt_cmd_fcs_dps2 = ((rtU.ncv_cmd_fcs_dps * 4.0 + 4.0 * rtU.beta_adc_deg)
    + 1.5 * rtU.beta_dot) * rtb_CVdt_cmd + (1.0 - rtb_CVdt_cmd) *
    (rtU.ncv_cmd_fcs_dps - rtU.ncv_fcs_dps);

  /* Sum: '<S9>/Sum1' incorporates:
   *  Gain: '<S5>/Gain1'
   *  Inport: '<Root>/hcv_cmd_fcs_fps'
   *  Inport: '<Root>/zcv_fcs_fps'
   */
  rtb_CVdt_cmd = rtU.hcv_cmd_fcs_fps - (-rtU.zcv_fcs_fps);

  /* Saturate: '<S9>/Saturation' */
  if (rtb_CVdt_cmd > 1.0) {
    rtb_CVdt_cmd = 1.0;
  } else if (rtb_CVdt_cmd < -1.0) {
    rtb_CVdt_cmd = -1.0;
  }

  /* Sum: '<S9>/Sum8' incorporates:
   *  Constant: '<S9>/Constant3'
   *  Gain: '<S9>/-0.2'
   *  Memory: '<S9>/Memory'
   *  Product: '<S9>/Product10'
   *  Saturate: '<S9>/Saturation'
   */
  rtb_CVdt_cmd += 0.0 * rtDW.Memory_PreviousInput * -0.2;

  /* Sum: '<S13>/Sum1' incorporates:
   *  Constant: '<S9>/Constant4'
   *  Gain: '<S13>/Gain'
   *  Product: '<S13>/Product'
   *  Sum: '<S13>/Sum'
   *  UnitDelay: '<S13>/Unit Delay'
   *  UnitDelay: '<S13>/Unit Delay1'
   */
  rtb_Sum1 = (rtb_CVdt_cmd + rtDW.UnitDelay_DSTATE) * 0.5 * 0.01 +
    rtDW.UnitDelay1_DSTATE;

  /* Switch: '<S14>/Switch2' incorporates:
   *  RelationalOperator: '<S14>/LowerRelop1'
   *  RelationalOperator: '<S14>/UpperRelop'
   *  Switch: '<S13>/Switch'
   *  Switch: '<S14>/Switch'
   */
  if (rtb_Sum1 > 9999.0) {
    rtb_Sum1 = 9999.0;
  } else if (rtb_Sum1 < -9999.0) {
    /* Switch: '<S14>/Switch' */
    rtb_Sum1 = -9999.0;
  }

  /* End of Switch: '<S14>/Switch2' */

  /* Outport: '<Root>/hcvdt_cmd_fcs_fps2' incorporates:
   *  Gain: '<S9>/Ki=0.25'
   *  Sum: '<S9>/Sum2'
   */
  rtY.hcvdt_cmd_fcs_fps2 = 0.25 * rtb_Sum1 + rtb_CVdt_cmd;

  /* Sum: '<S10>/Sum3' incorporates:
   *  Inport: '<Root>/mcv_cmd_fcs_dps'
   *  Inport: '<Root>/mcv_fcs_dps'
   */
  rtb_Sum3 = rtU.mcv_cmd_fcs_dps - rtU.mcv_fcs_dps;

  /* Sum: '<S16>/Sum1' incorporates:
   *  Constant: '<S10>/Constant4'
   *  Gain: '<S16>/Gain'
   *  Product: '<S16>/Product'
   *  Sum: '<S16>/Sum'
   *  UnitDelay: '<S16>/Unit Delay'
   *  UnitDelay: '<S16>/Unit Delay1'
   */
  rtb_Sum1_h = (rtb_Sum3 + rtDW.UnitDelay_DSTATE_o) * 0.5 * 0.01 +
    rtDW.UnitDelay1_DSTATE_k;

  /* Switch: '<S17>/Switch2' incorporates:
   *  RelationalOperator: '<S17>/LowerRelop1'
   *  RelationalOperator: '<S17>/UpperRelop'
   *  Switch: '<S16>/Switch'
   *  Switch: '<S17>/Switch'
   */
  if (rtb_Sum1_h > 9999.0) {
    rtb_Sum1_h = 9999.0;
  } else if (rtb_Sum1_h < -9999.0) {
    /* Switch: '<S17>/Switch' */
    rtb_Sum1_h = -9999.0;
  }

  /* End of Switch: '<S17>/Switch2' */

  /* Outport: '<Root>/mcvdt_cmd_fcs_dps2' incorporates:
   *  Gain: '<S10>/Ki=5.0'
   *  Inport: '<Root>/vtas_adc_kts'
   *  Lookup: '<S10>/transition_bvr'
   *  Product: '<S10>/Mult10'
   *  Sum: '<S10>/Sum9'
   */
  rtY.mcvdt_cmd_fcs_dps2 = rt_Lookup(&rtConstP.transition_bvr_XData[0], 2,
    rtU.vtas_adc_kts, &rtConstP.transition_bvr_YData[0]) * rtb_Sum3 + 5.0 *
    rtb_Sum1_h;

  /* Outport: '<Root>/xcvdt_cmd_fcs_fps2' incorporates:
   *  Gain: '<S5>/Gain'
   *  Gain: '<S8>/Gain'
   *  Inport: '<Root>/dcv_fcs_fps'
   *  Inport: '<Root>/xcv_cmd_fcs_fps'
   *  Sum: '<S8>/Sum1'
   */
  rtY.xcvdt_cmd_fcs_fps2 = (rtU.xcv_cmd_fcs_fps - (-rtU.dcv_fcs_fps)) * 0.5;

  /* Update for Memory: '<S9>/Memory' */
  rtDW.Memory_PreviousInput = rtb_Sum1;

  /* Update for UnitDelay: '<S13>/Unit Delay' */
  rtDW.UnitDelay_DSTATE = rtb_CVdt_cmd;

  /* Update for UnitDelay: '<S13>/Unit Delay1' */
  rtDW.UnitDelay1_DSTATE = rtb_Sum1;

  /* Update for UnitDelay: '<S16>/Unit Delay1' */
  rtDW.UnitDelay1_DSTATE_k = rtb_Sum1_h;

  /* Update for UnitDelay: '<S16>/Unit Delay' */
  rtDW.UnitDelay_DSTATE_o = rtb_Sum3;
}

/* Model initialize function */
void regs_12B_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
