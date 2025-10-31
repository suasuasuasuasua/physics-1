#pragma once

/**
 * @file motion.h
 * @brief Kinematics equations for motion with constant acceleration
 * 
 * This module implements the fundamental equations of motion for
 * one-dimensional kinematics with constant acceleration.
 */

namespace physics {
namespace kinematics {

/**
 * Calculate position with constant acceleration
 * 
 * Equation: x = x0 + v0*t + 0.5*a*t^2
 * 
 * @param x0 Initial position (m)
 * @param v0 Initial velocity (m/s)
 * @param t Time elapsed (s)
 * @param a Acceleration (m/s^2)
 * @return Position at time t (m)
 */
double position(double x0, double v0, double t, double a);

/**
 * Calculate velocity at a given time with constant acceleration
 * 
 * Equation: v = v0 + a*t
 * 
 * @param v0 Initial velocity (m/s)
 * @param t Time elapsed (s)
 * @param a Acceleration (m/s^2)
 * @return Velocity at time t (m/s)
 */
double velocity_at_time(double v0, double t, double a);

/**
 * Calculate velocity from position using kinematics
 * 
 * Equation: v^2 = v0^2 + 2*a*(x - x0)
 * 
 * @param v0 Initial velocity (m/s)
 * @param x Final position (m)
 * @param x0 Initial position (m)
 * @param a Acceleration (m/s^2)
 * @return Velocity at position x (m/s)
 */
double velocity_from_position(double v0, double x, double x0, double a);

/**
 * Calculate time to reach a given position with constant acceleration
 * 
 * Solves: x = x0 + v0*t + 0.5*a*t^2 for t
 * 
 * @param x0 Initial position (m)
 * @param x Final position (m)
 * @param v0 Initial velocity (m/s)
 * @param a Acceleration (m/s^2)
 * @return Time to reach position x (s), returns positive root
 * @throws std::invalid_argument if no real solution exists
 */
double time_to_position(double x0, double x, double v0, double a);

} // namespace kinematics
} // namespace physics
