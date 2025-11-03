"""Mathematical constants and conversion functions."""
from __future__ import annotations

import math

# Mathematical constants
PI = math.pi
E = math.e

def deg_to_rad(ang: float) -> float:
    """Convert degrees to radians.
    
    Args:
        ang: Angle in degrees
        
    Returns:
        Angle in radians
    """
    return ang * (PI / 180.0)

__all__ = ["PI", "E", "deg_to_rad"]
