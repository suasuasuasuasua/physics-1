#include "physics/kinematics/motion.h"
#include <cmath>
#include <stdexcept>

namespace physics {
namespace kinematics {

double position(double x0, double v0, double t, double a) {
    return x0 + v0 * t + 0.5 * a * t * t;
}

double velocity_at_time(double v0, double t, double a) {
    return v0 + a * t;
}

double velocity_from_position(double v0, double x, double x0, double a) {
    // v^2 = v0^2 + 2*a*(x - x0)
    double v_squared = v0 * v0 + 2.0 * a * (x - x0);
    
    if (v_squared < 0) {
        throw std::invalid_argument("No real velocity solution (negative v^2)");
    }
    
    // Return signed velocity (preserve direction)
    // Positive if moving in positive direction, negative otherwise
    return (v_squared >= 0) ? std::sqrt(v_squared) : -std::sqrt(-v_squared);
}

double time_to_position(double x0, double x, double v0, double a) {
    // Solve: x = x0 + v0*t + 0.5*a*t^2
    // Rearrange: 0.5*a*t^2 + v0*t + (x0 - x) = 0
    
    double displacement = x - x0;
    
    if (std::abs(a) < 1e-10) {
        // No acceleration, constant velocity
        if (std::abs(v0) < 1e-10) {
            throw std::invalid_argument("Cannot reach position with zero velocity and zero acceleration");
        }
        return displacement / v0;
    }
    
    // Quadratic formula: t = (-v0 ± sqrt(v0^2 - 2*a*(x0 - x))) / a
    double discriminant = v0 * v0 - 2.0 * a * (x0 - x);
    
    if (discriminant < 0) {
        throw std::invalid_argument("No real time solution (position unreachable)");
    }
    
    double sqrt_disc = std::sqrt(discriminant);
    double t1 = (-v0 + sqrt_disc) / a;
    double t2 = (-v0 - sqrt_disc) / a;
    
    // Return the positive time
    if (t1 >= 0 && t2 >= 0) {
        return std::min(t1, t2);  // Return earliest positive time
    } else if (t1 >= 0) {
        return t1;
    } else if (t2 >= 0) {
        return t2;
    } else {
        throw std::invalid_argument("No positive time solution");
    }
}

} // namespace kinematics
} // namespace physics
