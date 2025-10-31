# Physics-1 Quick Reference

## Kinematics Functions

### `position(x0, v0, t, a)`
Calculate position with constant acceleration.

**Equation:** `x = x0 + v0*t + 0.5*a*t²`

**Parameters:**
- `x0` - Initial position (m)
- `v0` - Initial velocity (m/s)
- `t` - Time elapsed (s)
- `a` - Acceleration (m/s²)

**Returns:** Position at time t (m)

**Example:**
```python
import physics_1 as phys

# Car accelerating from rest at 2 m/s² for 5 seconds
x = phys.kinematics.position(0, 0, 5, 2)
# Result: 25.0 m
```

---

### `velocity_at_time(v0, t, a)`
Calculate velocity at a given time with constant acceleration.

**Equation:** `v = v0 + a*t`

**Parameters:**
- `v0` - Initial velocity (m/s)
- `t` - Time elapsed (s)
- `a` - Acceleration (m/s²)

**Returns:** Velocity at time t (m/s)

**Example:**
```python
# Car accelerating from 10 m/s at 2 m/s² for 5 seconds
v = phys.kinematics.velocity_at_time(10, 5, 2)
# Result: 20.0 m/s
```

---

### `velocity_from_position(v0, x, x0, a)`
Calculate velocity from position using kinematics.

**Equation:** `v² = v0² + 2*a*(x - x0)`

**Parameters:**
- `v0` - Initial velocity (m/s)
- `x` - Final position (m)
- `x0` - Initial position (m)
- `a` - Acceleration (m/s²)

**Returns:** Velocity at position x (m/s)

**Example:**
```python
# Ball thrown up at 20 m/s, what's velocity at 15m height?
v = phys.kinematics.velocity_from_position(20, 15, 0, -9.8)
# Result: ~10.8 m/s
```

---

### `time_to_position(x0, x, v0, a)`
Calculate time to reach a given position with constant acceleration.

**Equation:** Solves `x = x0 + v0*t + 0.5*a*t²` for t

**Parameters:**
- `x0` - Initial position (m)
- `x` - Final position (m)
- `v0` - Initial velocity (m/s)
- `a` - Acceleration (m/s²)

**Returns:** Time to reach position x (s)

**Raises:** Exception if position is unreachable

**Example:**
```python
# Ball dropped from 100m, when does it hit ground?
t = phys.kinematics.time_to_position(100, 0, 0, -9.8)
# Result: ~4.52 seconds
```

---

## Common Physics Problems

### Free Fall
```python
g = -9.8  # gravity (m/s²)
h0 = 100  # initial height (m)

# Time to hit ground
t = phys.kinematics.time_to_position(h0, 0, 0, g)

# Impact velocity
v = phys.kinematics.velocity_at_time(0, t, g)
```

### Projectile Launched Upward
```python
g = -9.8
v0 = 20  # initial upward velocity (m/s)

# Time to reach max height (v=0)
t_max = -v0 / g

# Maximum height
h_max = phys.kinematics.position(0, v0, t_max, g)

# Time to return to ground
t_total = 2 * v0 / abs(g)
```

### Car Braking
```python
v0 = 30  # initial speed (m/s)
a = -6   # braking acceleration (m/s²)

# Time to stop (v=0)
t_stop = -v0 / a

# Braking distance
d = phys.kinematics.position(0, v0, t_stop, a)
```

### Two-Object Problem
```python
# Car A at constant speed, Car B accelerating from rest
v_A = 25  # m/s
a_B = 5   # m/s²

# When they meet: x_A = x_B
# 25*t = 0.5*5*t²
# Solve: t = 10 seconds

t = 10
x_A = phys.kinematics.position(0, v_A, t, 0)
x_B = phys.kinematics.position(0, 0, t, a_B)
# Both: 250 m
```

---

## Unit Conversions

### Common Conversions
```python
# mph to m/s
mph_to_ms = lambda mph: mph * 0.44704

# km/h to m/s
kmh_to_ms = lambda kmh: kmh / 3.6

# feet to meters
ft_to_m = lambda ft: ft * 0.3048
```

### Usage
```python
# 60 mph in m/s
v_mph = 60
v_ms = v_mph * 0.44704  # 26.8 m/s

# Calculate stopping distance
d = phys.kinematics.position(0, v_ms, 5, -6)
```

---

## Constants

```python
g = -9.8        # gravity on Earth (m/s²)
g_moon = -1.62  # gravity on Moon (m/s²)
g_mars = -3.71  # gravity on Mars (m/s²)
```

---

## Testing Your Understanding

### Problem Template
```python
def test_my_problem():
    """
    Problem: [State the problem]
    
    Given: [List knowns]
    Find: [What to calculate]
    """
    # Your solution
    result = phys.kinematics.function(...)
    
    # Verify
    assert abs(result - expected) < 0.01
```

### Example
```python
def test_free_fall():
    """
    Problem: Drop a rock from a cliff 50m high.
    How long until it hits water below?
    
    Given: h0=50m, v0=0, g=-9.8m/s²
    Find: time t
    """
    t = phys.kinematics.time_to_position(50, 0, 0, -9.8)
    expected = (2 * 50 / 9.8) ** 0.5  # ~3.19s
    assert abs(t - expected) < 0.01
```

---

## Tips

### 1. Sign Conventions
- **Positive**: upward, rightward, forward
- **Negative**: downward, leftward, backward
- Gravity: `g = -9.8` (downward)

### 2. Units
- Always use SI units (m, s, kg)
- Convert before calculating
- Check dimensional analysis

### 3. Sanity Checks
```python
# Does the result make physical sense?
assert position >= 0  # Can't be underground
assert time >= 0      # Time flows forward
assert abs(velocity) < 300  # Slower than sound (usually)
```

### 4. Error Handling
```python
try:
    result = phys.kinematics.time_to_position(...)
except Exception as e:
    print(f"Position unreachable: {e}")
```

---

## Next Steps

After mastering kinematics:
1. **Dynamics** - Forces, Newton's laws
2. **Energy** - Work, kinetic/potential energy
3. **Momentum** - Collisions, conservation
4. **Rotation** - Angular motion
5. **Oscillations** - Springs, pendulums

---

## Resources

- [SETUP_GUIDE.md](SETUP_GUIDE.md) - Full development guide
- [INITIAL_ASSESSMENT.md](INITIAL_ASSESSMENT.md) - Project overview
- [tests/test_kinematics.py](tests/test_kinematics.py) - Example problems
- [examples/projectile_motion.py](examples/projectile_motion.py) - Visualization
- [MIT OCW](https://ocw.mit.edu/courses/8-01sc-classical-mechanics-fall-2016/) - Course material

---

**Last Updated:** 2025-10-31  
**Version:** 0.1.0  
**Module:** Kinematics ✅
