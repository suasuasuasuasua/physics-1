"""
Example: Projectile Motion Visualization

This script demonstrates how to use the physics_1 library to solve
a projectile motion problem and visualize the results.

Problem:
A projectile is launched at 45 degrees with initial velocity 30 m/s.
Calculate and plot its trajectory.
"""

import physics_1 as phys
import numpy as np

# To visualize, install matplotlib:
# pip install matplotlib
# Then uncomment the import below:
# import matplotlib.pyplot as plt


def projectile_trajectory(v0, angle_deg, g=-9.8, dt=0.01):
    """
    Calculate projectile trajectory.
    
    Parameters
    ----------
    v0 : float
        Initial velocity (m/s)
    angle_deg : float
        Launch angle (degrees)
    g : float
        Gravitational acceleration (m/s^2)
    dt : float
        Time step (s)
        
    Returns
    -------
    tuple
        Arrays of (times, x_positions, y_positions)
    """
    # Convert angle to radians
    angle_rad = np.radians(angle_deg)
    
    # Initial velocity components
    v0x = v0 * np.cos(angle_rad)
    v0y = v0 * np.sin(angle_rad)
    
    # Calculate flight time (when y returns to 0)
    flight_time = 2 * v0y / abs(g)
    
    # Generate time points
    times = np.arange(0, flight_time, dt)
    
    # Calculate positions at each time
    x_positions = []
    y_positions = []
    
    for t in times:
        # Horizontal motion (constant velocity)
        x = phys.kinematics.position(0, v0x, t, 0)
        
        # Vertical motion (constant acceleration)
        y = phys.kinematics.position(0, v0y, t, g)
        
        # Stop if projectile hits ground
        if y < 0:
            break
            
        x_positions.append(x)
        y_positions.append(y)
    
    return np.array(times[:len(x_positions)]), np.array(x_positions), np.array(y_positions)


def main():
    """Main function to run the simulation."""
    
    # Problem parameters
    v0 = 30.0  # m/s
    angle = 45.0  # degrees
    g = -9.8  # m/s^2
    
    print("Projectile Motion Analysis")
    print("=" * 50)
    print(f"Initial velocity: {v0} m/s")
    print(f"Launch angle: {angle}°")
    print(f"Gravitational acceleration: {g} m/s²")
    print()
    
    # Calculate trajectory
    times, x_pos, y_pos = projectile_trajectory(v0, angle, g)
    
    # Calculate key metrics
    max_height = np.max(y_pos)
    max_range = np.max(x_pos)
    flight_time = times[-1]
    
    print("Results:")
    print("-" * 50)
    print(f"Maximum height: {max_height:.2f} m")
    print(f"Maximum range: {max_range:.2f} m")
    print(f"Flight time: {flight_time:.2f} s")
    print()
    
    # Theoretical calculations for verification
    angle_rad = np.radians(angle)
    v0y = v0 * np.sin(angle_rad)
    theoretical_max_height = v0y * v0y / (2 * abs(g))
    theoretical_range = v0 * v0 * np.sin(2 * angle_rad) / abs(g)
    
    print("Theoretical values (for verification):")
    print("-" * 50)
    print(f"Maximum height: {theoretical_max_height:.2f} m")
    print(f"Maximum range: {theoretical_range:.2f} m")
    print()
    
    # Verification
    height_error = abs(max_height - theoretical_max_height)
    range_error = abs(max_range - theoretical_range)
    
    print("Verification:")
    print("-" * 50)
    print(f"Height error: {height_error:.4f} m")
    print(f"Range error: {range_error:.4f} m")
    
    if height_error < 0.1 and range_error < 0.1:
        print("✓ Results match theoretical predictions!")
    else:
        print("⚠ Large discrepancy detected")
    
    # Plotting (uncomment if matplotlib is installed)
    """
    plt.figure(figsize=(10, 6))
    plt.plot(x_pos, y_pos, 'b-', linewidth=2, label='Trajectory')
    plt.plot(x_pos[0], y_pos[0], 'go', markersize=10, label='Launch')
    plt.plot(x_pos[-1], y_pos[-1], 'ro', markersize=10, label='Landing')
    
    # Mark maximum height
    max_idx = np.argmax(y_pos)
    plt.plot(x_pos[max_idx], y_pos[max_idx], 'k*', markersize=15, label='Max Height')
    
    plt.xlabel('Horizontal Distance (m)', fontsize=12)
    plt.ylabel('Vertical Height (m)', fontsize=12)
    plt.title(f'Projectile Motion: v₀={v0} m/s, θ={angle}°', fontsize=14)
    plt.grid(True, alpha=0.3)
    plt.legend(fontsize=10)
    plt.axis('equal')
    
    plt.tight_layout()
    plt.savefig('projectile_motion.png', dpi=150)
    print("\n✓ Plot saved as 'projectile_motion.png'")
    
    plt.show()
    """


if __name__ == "__main__":
    main()
