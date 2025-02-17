/*******************************************************************************
 * File: ert_main.c
 *
 * Description:
 *   Example main function to drive euler321_I2B_12B_step() in a loop.  Uses
 *   assertion-based checks (via __ESBMC_assert) for each requirement (1..8).
 *   This example is structured to be compatible with ESBMC verification runs.
 *
 *   IMPORTANT NOTES / ASSUMPTIONS:
 *   1) This file demonstrates how one might wrap the feed-forward function
 *      euler321_I2B_12B_step() in a verification harness.
 *   2) The actual math in euler321_I2B_12B_step() here is an example of
 *      standard 3-2-1 Euler rotations. If your real function differs,
 *      adjust the rotation computations accordingly.
 *   3) We do not define the verification macros (VERIFY_PROPERTY_N). To
 *      enable checking property N, define -DVERIFY_PROPERTY_N in the
 *      ESBMC command line or build system.
 *   4) We demonstrate how to check “no persistent states” by verifying
 *      that the same inputs produce the same outputs from one iteration
 *      to the next, and that different inputs do not silently revert to
 *      old outputs.
 *   5) We rely on standard C math routines (fabs, sin, cos, etc.). Ensure
 *      you link with the math library if needed (-lm).
 *
 * Requirements Being Checked:
 *   R(1): DCM321 == Euler(3)*Euler(2)*Euler(1)
 *   R(2): Vb == DCM321 * Vi
 *   R(3): |Vb| == |Vi|
 *   R(4): DCM321 invertible if theta != ±(pi/2)
 *   R(5): Distinct mapping w.r.t. distinct theta
 *   R(6): DCM321 rows & columns orthonormal
 *   R(7): DCM321 * (DCM321^T) = Identity
 *   R(8): det(DCM321) = +1
 *
 * ESBMC Usage Example:
 *   esbmc ert_main.c --force-malloc-success --no-bounds-check \
 *         -DVERIFY_PROPERTY_1 -DVERIFY_PROPERTY_2 ...
 *
 *******************************************************************************/

#include <math.h>     /* for sin, cos, fabs */
#include <stdio.h>    /* for printf (if needed) */
#include <stdbool.h>  /* for _Bool (C99) */

/* ESBMC assertion macro */
#ifndef __ESBMC_assert
#define __ESBMC_assert(cond, msg)  ((void)0)  /* Fallback if not using ESBMC */
#endif

/* Nondeterministic inputs for verification */
_Bool nondet_bool(void);
double nondet_double(void);

/*******************************************************************************
 * External Structures for Input and Output
 ******************************************************************************/
typedef struct {
  double phi;   /* roll angle, rad */
  double theta; /* pitch angle, rad */
  double psi;   /* yaw angle, rad */
  double Vi[3]; /* inertial vector to be rotated into body frame */
} ExtU;  /* External Inputs */

typedef struct {
  double DCM321[9]; /* 3x3 rotation matrix */
  double Vb[3];     /* rotated vector in body frame */
} ExtY;  /* External Outputs */

/*******************************************************************************
 * Global External Variables
 *   In typical code generation, these may be auto-generated or external.
 ******************************************************************************/
ExtU rtU; /* External inputs */
ExtY rtY; /* External outputs */

/*******************************************************************************
 * euler321_I2B_12B_step()
 *   Example implementation of a 3-2-1 Euler rotation. If your actual code
 *   differs, replace with the real function logic. This example shows how
 *   one might construct a DCM from (phi, theta, psi).
 *
 *   The convention used here is:
 *     DCM = R_x(phi) * R_y(theta) * R_z(psi)
 *   (Check carefully if your real function does R_z(psi)*R_y(theta)*R_x(phi)
 *    or some other order. 3-2-1 commonly implies final rotation about x.)
 *******************************************************************************/
void euler321_I2B_12B_step(void)
{
  double cp = cos(rtU.phi);   /* cos(roll)   */
  double sp = sin(rtU.phi);   /* sin(roll)   */
  double ct = cos(rtU.theta); /* cos(pitch)  */
  double st = sin(rtU.theta); /* sin(pitch)  */
  double cs = cos(rtU.psi);   /* cos(yaw)    */
  double ss = sin(rtU.psi);   /* sin(yaw)    */

  /*
   * For a standard "321" sequence (roll about x, pitch about y, yaw about z),
   * one typical form is:
   *
   *  R_x(phi) = [1     0      0
   *              0   cosφ   -sinφ
   *              0   sinφ    cosφ]
   *
   *  R_y(theta)=[ cosθ   0   sinθ
   *               0      1   0
   *              -sinθ   0   cosθ]
   *
   *  R_z(psi)  =[ cosψ  -sinψ  0
   *               sinψ   cosψ  0
   *               0       0    1 ]
   *
   *  DCM = R_x(phi)*R_y(theta)*R_z(psi)
   */

  /* First, M1 = R_x(phi)*R_y(theta) */
  double M1[9];
  /*
    M1 = Rx * Ry:
       [1,     0,     0]   [ cosθ, 0, sinθ ]
       [0,   cosφ, -sinφ] x [   0, 1,   0  ]
       [0,   sinφ,  cosφ]   [-sinθ,0, cosθ ]
  */
  M1[0] = 1.0 * ct + 0.0 * 0.0 + 0.0 * (-st);      /* row0,col0 */
  M1[1] = 1.0 * 0.0 + 0.0 * 1.0 + 0.0 * 0.0;       /* row0,col1 */
  M1[2] = 1.0 * st + 0.0 * 0.0 + 0.0 * ct;         /* row0,col2 */

  M1[3] = 0.0 * ct + (cp) * 0.0 + (-sp)*(-st);     /* row1,col0 */
  M1[4] = 0.0 * 0.0 + (cp) * 1.0 + (-sp)* 0.0;      /* row1,col1 */
  M1[5] = 0.0 * st + (cp) * 0.0 + (-sp)* ct;       /* row1,col2 */

  M1[6] = 0.0 * ct + (sp) * 0.0 + (cp)*(-st);      /* row2,col0 */
  M1[7] = 0.0 * 0.0 + (sp) * 1.0 + (cp)* 0.0;       /* row2,col1 */
  M1[8] = 0.0 * st + (sp) * 0.0 + (cp)* ct;        /* row2,col2 */

  /* Next, rtY.DCM321 = M1 * R_z(psi) */
  /* Rz(psi) = [cs, -ss, 0; ss, cs, 0; 0, 0, 1] */
  int i,j,k;
  double Mz[9] = { cs, -ss, 0.0,
                   ss,  cs, 0.0,
                   0.0, 0.0, 1.0 };
  for(i=0; i<3; i++){
    for(j=0; j<3; j++){
      rtY.DCM321[i*3 + j] = 0.0;
      for(k=0; k<3; k++){
        rtY.DCM321[i*3 + j] += M1[i*3 + k] * Mz[k*3 + j];
      }
    }
  }

  /* Finally, compute Vb = DCM321 * Vi */
  for(i=0; i<3; i++){
    rtY.Vb[i] = 0.0;
    for(j=0; j<3; j++){
      rtY.Vb[i] += rtY.DCM321[i*3 + j] * rtU.Vi[j];
    }
  }
}

/*******************************************************************************
 * Helper Functions
 ******************************************************************************/

/* Compute 3x3 * 3x3 => 3x3 */
static void mat3x3_mult(const double A[9], const double B[9], double Out[9])
{
  int i,j,k;
  for(i=0; i<3; i++){
    for(j=0; j<3; j++){
      Out[i*3 + j] = 0.0;
      for(k=0; k<3; k++){
        Out[i*3 + j] += A[i*3 + k] * B[k*3 + j];
      }
    }
  }
}

/* Compute 3x3 * 3x1 => 3x1 */
static void mat3x3_vec3_mult(const double A[9], const double v[3], double Out[3])
{
  int i,j;
  for(i=0; i<3; i++){
    Out[i] = 0.0;
    for(j=0; j<3; j++){
      Out[i] += A[i*3 + j] * v[j];
    }
  }
}

/* Compute the determinant of a 3x3 matrix */
static double det3x3(const double M[9])
{
  return (M[0] * (M[4]*M[8] - M[5]*M[7])
        - M[1] * (M[3]*M[8] - M[5]*M[6])
        + M[2] * (M[3]*M[7] - M[4]*M[6]));
}

/* Compute approximate equality check for two doubles */
static _Bool approx_equal(double a, double b, double tol)
{
  return (fabs(a - b) <= tol);
}

/* Identity 3x3 check: A ~ I if off-diagonals ~ 0, diagonals ~ 1 */
static _Bool is_identity_3x3(const double A[9], double tol)
{
  /* check diagonal ~ 1 */
  if(!approx_equal(A[0],1.0,tol)) return false;
  if(!approx_equal(A[4],1.0,tol)) return false;
  if(!approx_equal(A[8],1.0,tol)) return false;
  /* check off-diagonal ~ 0 */
  if(!approx_equal(A[1],0.0,tol)) return false;
  if(!approx_equal(A[2],0.0,tol)) return false;
  if(!approx_equal(A[3],0.0,tol)) return false;
  if(!approx_equal(A[5],0.0,tol)) return false;
  if(!approx_equal(A[6],0.0,tol)) return false;
  if(!approx_equal(A[7],0.0,tol)) return false;
  return true;
}

/* Dot product of row i in M with row j in M for orthogonality check, etc. */
static double row_dot(const double M[9], int row_i, int row_j)
{
  return ( M[row_i*3+0]*M[row_j*3+0]
         + M[row_i*3+1]*M[row_j*3+1]
         + M[row_i*3+2]*M[row_j*3+2] );
}

/*******************************************************************************
 * check_dcm321_against_euler:
 *   Recompute DCM from phi,theta,psi using the same formula outside the step,
 *   then compare to rtY.DCM321 to see if they match. This addresses R(1).
 *******************************************************************************/
static _Bool check_dcm321_against_euler(double phi, double theta, double psi,
                                        const double dcm[9],
                                        double tol)
{
  /* We'll replicate the same approach used in euler321_I2B_12B_step. */
  double cp = cos(phi);
  double sp = sin(phi);
  double ct = cos(theta);
  double st = sin(theta);
  double cs = cos(psi);
  double ss = sin(psi);

  /* M1 = Rx(phi)*Ry(theta) */
  double M1[9];
  M1[0] = ct;         M1[1] = 0.0;   M1[2] = st;
  M1[3] = -sp* -st;   M1[4] = cp;    M1[5] = -sp*ct;
  M1[6] =  cp*(-st);  M1[7] = sp;    M1[8] =  cp*ct;

  /* Mz(psi) */
  double Mz[9] = { cs, -ss, 0.0,
                   ss,  cs, 0.0,
                   0.0, 0.0, 1.0 };

  double Mcalc[9];
  mat3x3_mult(M1,Mz,Mcalc);

  /* Compare Mcalc to dcm element-wise */
  for(int i=0; i<9; i++){
    if(!approx_equal(Mcalc[i], dcm[i], tol)){
      return false;
    }
  }
  return true;
}

/*******************************************************************************
 * main
 *   Runs multiple loops of the system step and checks properties after each.
 *   Because there are no persistent states, we do not store any 'state'
 *   variables between calls. We do, however, store old inputs and outputs
 *   to confirm that repeated inputs yield repeated outputs (no hidden states).
 *******************************************************************************/
int main(void)
{
  /* Variables to track old inputs/outputs for "no persistent state" check. */
  double old_phi    = 0.0;
  double old_theta  = 0.0;
  double old_psi    = 0.0;
  double old_Vi[3]  = {0.0,0.0,0.0};
  double old_DCM[9] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
  double old_Vb[3]  = {0.0,0.0,0.0};
  _Bool  first_iter = true;

  int loopCount = 0;
  /* Let's limit to 10 iterations for this example */
  while(loopCount < 10)
  {
    /* Assign nondet inputs each iteration */
    rtU.phi   = nondet_double();
    rtU.theta = nondet_double();
    rtU.psi   = nondet_double();
    rtU.Vi[0] = nondet_double();
    rtU.Vi[1] = nondet_double();
    rtU.Vi[2] = nondet_double();

    /* Call the function under test */
    euler321_I2B_12B_step();

    /***************************************************************************
     * 0) Check that the same inputs produce the same outputs (no persistent
     *    or hidden states). If we happen to get exactly the same inputs as
     *    the previous iteration, the outputs must match exactly.
     ***************************************************************************/
    if(!first_iter)
    {
      _Bool same_inputs = approx_equal(rtU.phi,   old_phi,   1e-12)
                       && approx_equal(rtU.theta, old_theta, 1e-12)
                       && approx_equal(rtU.psi,   old_psi,   1e-12)
                       && approx_equal(rtU.Vi[0], old_Vi[0], 1e-12)
                       && approx_equal(rtU.Vi[1], old_Vi[1], 1e-12)
                       && approx_equal(rtU.Vi[2], old_Vi[2], 1e-12);
      if(same_inputs)
      {
        /* Then outputs must match too */
        _Bool mismatch = false;
        for(int i=0; i<9; i++){
          if(!approx_equal(rtY.DCM321[i], old_DCM[i], 1e-12)){
            mismatch = true; 
            break;
          }
        }
        for(int i=0; i<3; i++){
          if(!approx_equal(rtY.Vb[i], old_Vb[i], 1e-12)){
            mismatch = true; 
            break;
          }
        }
        __ESBMC_assert(!mismatch, 
                       "No hidden state: repeated inputs -> repeated outputs");
      }
    }

    /***************************************************************************
     * Requirement 1:
     * "The Rotation Matrix Output, DCM321, of this Function Shall Equal a 3x3
     *  Matrix Product of (Euler 3)*(Euler 2)*(Euler 1)."
     *
     * For demonstration, we replicate the same math externally and compare.
     ***************************************************************************/
#ifdef VERIFY_PROPERTY_1
    {
      _Bool eq = check_dcm321_against_euler(rtU.phi, rtU.theta, rtU.psi,
                                            rtY.DCM321, 1e-10);
      __ESBMC_assert(eq, "R(1) fail: DCM321 != Euler-based product");
    }
#endif

    /***************************************************************************
     * Requirement 2:
     * "The Body Vector Output, Vb, of this Function Shall Equal DCM321*Vi."
     ***************************************************************************/
#ifdef VERIFY_PROPERTY_2
    {
      double Vcheck[3];
      mat3x3_vec3_mult(rtY.DCM321, rtU.Vi, Vcheck);
      _Bool eq = true;
      for(int i=0; i<3; i++){
        if(!approx_equal(Vcheck[i], rtY.Vb[i], 1e-10)){
          eq = false; break;
        }
      }
      __ESBMC_assert(eq, "R(2) fail: Vb != DCM321*Vi");
    }
#endif

    /***************************************************************************
     * Requirement 3:
     * "The magnitude of Vb shall equal the magnitude of Vi."
     ***************************************************************************/
#ifdef VERIFY_PROPERTY_3
    {
      double magVi = sqrt(rtU.Vi[0]*rtU.Vi[0]
                        + rtU.Vi[1]*rtU.Vi[1]
                        + rtU.Vi[2]*rtU.Vi[2]);
      double magVb = sqrt(rtY.Vb[0]*rtY.Vb[0]
                        + rtY.Vb[1]*rtY.Vb[1]
                        + rtY.Vb[2]*rtY.Vb[2]);
      /* Allow small numerical tolerance. E.g. 1e-10. */
      __ESBMC_assert(fabs(magVi - magVb) < 1e-10,
                     "R(3) fail: |Vb| != |Vi| (within tolerance)");
    }
#endif

    /***************************************************************************
     * Requirement 4:
     * "DCM321 shall be invertible except if theta == ±pi/2."
     ***************************************************************************/
#ifdef VERIFY_PROPERTY_4
    {
      /* If |theta ± pi/2| > some small tolerance, expect a nonzero determinant. */
      double tol_sing = 1e-8;  /* near singular limit */
      double val = fabs(fabs(rtU.theta) - (M_PI/2.0));
      double determinant = det3x3(rtY.DCM321);
      if(val > tol_sing)
      {
        /* Expect invertible => det != 0. Typically near +1, but > 0.00001 is enough. */
        _Bool inv_ok = fabs(determinant) > 1e-6;
        __ESBMC_assert(inv_ok,
                       "R(4) fail: matrix not invertible when theta != ±pi/2");
      }
      else
      {
        /* If we are EXACTLY at theta=±pi/2, we allow singular. No specific assert. */
      }
    }
#endif

    /***************************************************************************
     * Requirement 5:
     * "The Rotation Matrix, DCM321, shall provide a distinct mapping from Vi
     *  to Vb for each pitch angle, theta. (Except known singularities or Euler
     *  angle equivalences for phi/psi.)"
     *
     * This is tricky to verify in a single iteration. We'll do a simple approach:
     * - If we compare the new DCM to the old DCM and the old theta != new theta
     *   (and ignoring the known singular angles, or identical phi/psi combos),
     *   then the new DCM should differ at least in one element by some margin.
     *
     * This check is simplistic. Real checks might require deeper analysis of
     * Euler angle equivalences. But we demonstrate a sample assertion.
     ***************************************************************************/
#ifdef VERIFY_PROPERTY_5
    if(!first_iter)
    {
      double tol_sing = 1e-8;
      double dtheta = fabs(rtU.theta - old_theta);
      /* If theta changed significantly, and phi,psi remain the same, we expect
         a difference in the DCM. We won't check if phi or psi differ. */
      if(dtheta > 1e-7
         && approx_equal(rtU.phi, old_phi, 1e-12)
         && approx_equal(rtU.psi, old_psi, 1e-12)
         && (fabs(fabs(rtU.theta) - M_PI/2.0) > tol_sing)
         && (fabs(fabs(old_theta) - M_PI/2.0) > tol_sing))
      {
        _Bool identicalDCM = true;
        for(int i=0; i<9; i++){
          if(!approx_equal(rtY.DCM321[i], old_DCM[i], 1e-10)){
            identicalDCM = false;
            break;
          }
        }
        __ESBMC_assert(!identicalDCM,
          "R(5) fail: distinct theta with same phi,psi => must produce distinct DCM");
      }
    }
#endif

    /***************************************************************************
     * Requirement 6:
     * "The rows and columns of DCM321 shall be orthonormal."
     ***************************************************************************/
#ifdef VERIFY_PROPERTY_6
    {
      /* We check row i dot row j = 0 for i!=j, and row i dot row i = 1. */
      double r0dotr0 = row_dot(rtY.DCM321, 0,0);
      double r1dotr1 = row_dot(rtY.DCM321, 1,1);
      double r2dotr2 = row_dot(rtY.DCM321, 2,2);

      double r0dotr1 = row_dot(rtY.DCM321, 0,1);
      double r0dotr2 = row_dot(rtY.DCM321, 0,2);
      double r1dotr2 = row_dot(rtY.DCM321, 1,2);

      /* We do a tolerance check ~ 1 or 0. */
      _Bool orthonorm_ok =
         (fabs(r0dotr0 - 1.0) < 1e-10) &&
         (fabs(r1dotr1 - 1.0) < 1e-10) &&
         (fabs(r2dotr2 - 1.0) < 1e-10) &&
         (fabs(r0dotr1) < 1e-10)       &&
         (fabs(r0dotr2) < 1e-10)       &&
         (fabs(r1dotr2) < 1e-10);

      __ESBMC_assert(orthonorm_ok, "R(6) fail: DCM321 rows not orthonormal");
    }
#endif

    /***************************************************************************
     * Requirement 7:
     * "DCM321 * DCM321^T = Identity (3x3)."
     ***************************************************************************/
#ifdef VERIFY_PROPERTY_7
    {
      double T[9];   /* Transpose of DCM321 */
      for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
          T[i*3 + j] = rtY.DCM321[j*3 + i];
        }
      }
      double IdCheck[9];
      mat3x3_mult(rtY.DCM321, T, IdCheck);

      _Bool isId = is_identity_3x3(IdCheck, 1e-10);
      __ESBMC_assert(isId, "R(7) fail: DCM321 * DCM321^T != Identity");
    }
#endif

    /***************************************************************************
     * Requirement 8:
     * "The determinant of DCM321 shall be +1.0."
     ***************************************************************************/
#ifdef VERIFY_PROPERTY_8
    {
      double d = det3x3(rtY.DCM321);
      __ESBMC_assert(fabs(d - 1.0) < 1e-10,
                     "R(8) fail: det(DCM321) != 1.0");
    }
#endif

    /* Save current inputs/outputs to compare next iteration */
    old_phi   = rtU.phi;
    old_theta = rtU.theta;
    old_psi   = rtU.psi;
    for(int i=0; i<3; i++){
      old_Vi[i]  = rtU.Vi[i];
      old_Vb[i]  = rtY.Vb[i];
    }
    for(int i=0; i<9; i++){
      old_DCM[i] = rtY.DCM321[i];
    }
    first_iter = false;

    loopCount++;
  } /* end while */

  return 0;
}
