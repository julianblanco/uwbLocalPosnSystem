import numpy as np
import sympy as sym

# Julian Blanco
# 09 May 2017
# Iterative Least Squared Estimation for GPS


AnchorsX = np.array([0,1000])
AnchorsY = np.array([0,0])


actual_pos = np.array([400,-100])
prop_speed = 1500

acutal_ranges = PR= np.sqrt(((actual_pos[0]-AnchorsX)**2) + ((actual_pos[1]-AnchorsY)**2) )
actual_arrival_times =acutal_ranges/prop_speed 
print("Arrival times: ", actual_arrival_times)

reciever_offset = 1
measured_arrival_times = actual_arrival_times + reciever_offset

psuedoranges = measured_arrival_times*prop_speed
x,t = sym.symbols('x,t')

eq1 = sym.Eq(sym.sqrt(x**2 +actual_pos[1]**2) + prop_speed*t,measured_arrival_times[0]*prop_speed)
eq2 = sym.Eq(sym.sqrt(((AnchorsX[1]-actual_pos[0])**2 + actual_pos[1]**2)) + prop_speed*t,measured_arrival_times[1]*prop_speed)
result = sym.solve([eq1,eq2],(x,t))
print(result)