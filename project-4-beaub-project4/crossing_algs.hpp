///////////////////////////////////////////////////////////////////////////////
// crossing_algs.hpp
//
// Algorithms that solve the marsh crossing problem.
//
// All of the TODO sections for this project reside in this file.
//
// This file builds on crossing_types.hpp, so you should familiarize yourself
// with that file before working on this file.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cassert>
#include <iostream>

#include "crossing_types.hpp"

namespace crossing {
// Solve the marsh crossing problem for the given grid, using an exhaustive
// optimization algorithm.
//
// This algorithm is expected to run in exponential time, so the grid's
// width+height must be small enough to fit in a 64-bit int; this is enforced
// with an assertion.
//
// The grid must be non-empty.
unsigned int marsh_crossing_exhaustive(const grid& setting) {

  // grid must be non-empty.
  assert(setting.rows() > 0);
  assert(setting.columns() > 0);

  // Compute the path length, and check that it is legal.
  const size_t steps = setting.rows() + setting.columns() - 2;
  assert(steps < 64);

  unsigned int count_paths = 0;

  for (size_t bits = 0; bits < pow(2,steps); bits++) {
    path candidate(setting);
    bool valid_path = true;
    for (size_t k = 0; k < steps; k++) {
      int bit = (bits >> k) & 1;
      if (bit == 1) {
        if (candidate.is_step_valid(STEP_DIRECTION_RIGHT)) {
          candidate.add_step(STEP_DIRECTION_RIGHT);
        }
        else {
          valid_path = false;
          break;
        }
      }
      else {
        if (candidate.is_step_valid(STEP_DIRECTION_DOWN)) {
            candidate.add_step(STEP_DIRECTION_DOWN);
        }
        else {
          valid_path = false;
          break;
        }
      }
    }
    if (valid_path) {
      count_paths++;
    }
  }

  return count_paths;
}

// Solve the marsh crossing problem for the given grid, using a dynamic
// programming algorithm.
//
// The grid must be non-empty.
unsigned int marsh_crossing_dyn_prog(const grid& setting) {

  // grid must be non-empty.
  assert(setting.rows() > 0);
  assert(setting.columns() > 0);

  unsigned int A[100][100];
  A[0][0] = 1;

  for (size_t i = 0; i <= setting.rows()-1;i++) {
    for (size_t j = 0; j <= setting.columns()-1; j++) {
      if (i == 0 && j == 0) { continue; }
      if (setting.get(i,j) == CELL_THICKET) {
        A[i][j] = 0;
        continue;
      }
      int from_above = 0, from_left = 0;
      if (i > 0 && A[i-1][j] != 0) {
        from_above = A[i-1][j];
      }
      if (j > 0 && A[i][j-1] != 0) {
        from_left = A[i][j-1];
      }
      A[i][j] = from_above + from_left;
    }
  }

  return A[setting.rows()-1][setting.columns()-1];
}

}
