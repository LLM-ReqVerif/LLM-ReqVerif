/* ert_main.c - Example for ESBMC verification with assertion checks */

#include <stddef.h>
#include <stdio.h>
#include <math.h>          /* for fabs() */
#include "nn_12B.h"        /* Model header file */

/* ------------------ */
/* Nondeterministic stubs for ESBMC */
/* ------------------ */
_Bool nondet_bool(void);
double nondet_double(void);

/* ------------------ */
/* Main entry point with property checks */
/* ------------------ */
int_T main(int_T argc, const char *argv[])
{
  /* Unused arguments */
  (void)(argc);
  (void)(argv);

  /* Initialize the model */
  nn_12B_initialize();

  /* ------------------ */
  /* Variables to track previous loop values */
  /* ------------------ */
  double x_prev = 0.0;
  double y_prev = 0.0;
  double z_prev = 0.0;
  _Bool first_iteration = 1; /* indicates if we’re in the very first loop */

  /* ------------------ */
  /* Example: Run system for a fixed number of iterations */
  /* ------------------ */
  int loop_counter = 0;
  int max_loops = 10; /* Arbitrary loop count for demonstration */

  while (loop_counter < max_loops)
  {
    /* ------------------ */
    /* 1. Set or read nondeterministic inputs */
    /* ------------------ */
    rtU.x = nondet_double();
    rtU.y = nondet_double();

    /* ------------------ */
    /* 2. Run one step of the system */
    /* ------------------ */
    nn_12B_step();

    /* ------------------ */
    /* 3. Verify each requirement with ESBMC assertions */
    /* ------------------ */

    /* ------------------ */
    /* Requirement 1: z <= 1.1 */
    /* ------------------ */
#ifdef VERIFY_PROPERTY_1
    __ESBMC_assert(
      (rtY.z <= 1.1),
      "REQUIREMENT 1 VIOLATION: z is greater than 1.1"
    );
#endif

    /* ------------------ */
    /* Requirement 2: z >= -0.2 */
    /* ------------------ */
#ifdef VERIFY_PROPERTY_2
    __ESBMC_assert(
      (rtY.z >= -0.2),
      "REQUIREMENT 2 VIOLATION: z is less than -0.2"
    );
#endif

    /* ------------------ */
    /* Requirement 3: -35 <= Δz/Δx <= +10 and -35 <= Δz/Δy <= +10 */
    /*
       We store the previous x, y, and z from the last iteration
       to calculate partial derivatives on consecutive data points.
       Because the model does NOT store or update these, we do it externally.
    */
    /* ------------------ */
#ifdef VERIFY_PROPERTY_3
    if (!first_iteration)
    {
      double dx = (rtU.x - x_prev);
      double dy = (rtU.y - y_prev);
      double dz = (rtY.z - z_prev);

      /* partial derivative wrt x (if dx != 0) */
      if (dx != 0.0)
      {
        double deriv_x = dz / dx;
        __ESBMC_assert(
          (deriv_x >= -35.0) && (deriv_x <= 10.0),
          "REQUIREMENT 3 VIOLATION: partial derivative wrt x out of range"
        );
      }

      /* partial derivative wrt y (if dy != 0) */
      if (dy != 0.0)
      {
        double deriv_y = dz / dy;
        __ESBMC_assert(
          (deriv_y >= -35.0) && (deriv_y <= 10.0),
          "REQUIREMENT 3 VIOLATION: partial derivative wrt y out of range"
        );
      }
    }
#endif

    /* ------------------ */
    /* Requirement 4: | z - zt | <= 0.01 
       We'll read a nondeterministic "truth" value zt for demonstration.
       In real usage, you'd provide the known ground truth for the pair (x, y).
    */
    /* ------------------ */
#ifdef VERIFY_PROPERTY_4
    {
      double zt = nondet_double();
      double diff = rtY.z - zt;

      /* Using absolute difference check: -0.01 <= diff <= 0.01 */
      __ESBMC_assert(
        (diff <= 0.01) && (diff >= -0.01),
        "REQUIREMENT 4 VIOLATION: absolute error with ground truth > 0.01"
      );
    }
#endif

    /* ------------------ */
    /* 4. Update previous iteration data  */
    /* ------------------ */
    x_prev = rtU.x;
    y_prev = rtU.y;
    z_prev = rtY.z;
    first_iteration = 0; /* Next loop won't be the first */

    /* move to next iteration */
    loop_counter++;
  }

  /* If we exit the loop without an assertion failure, we’re good */
  return 0;
}
