import numpy as np

# Julian Blanco
# 09 May 2017
# Iterative Least Squared Estimation example, 
# 4 Ultrawide band anchors or "GPS Satilites"
# Location stored in the XYZ arrays in meters
# pos is the location of the tag or "GPS Reciever"

AnchorsX = np.array([4.2672,4.2672,0.0,0.0])
AnchorsY = np.array([0.0,9.4488,9.4488 ,0.0])
# Postion of the tag to back calculate the ranges for testing purposes
pos = np.array([0.00,4.00])

# Intialize the arrays as floats with arbirtray values 
AR = np.array([10.0,1.0,1.0,1.0])
PR = np.array([2.0,2.0,2.0,2.0])

#Calculate the ranges to the anchors, noramally would be solved for by the UWB (TREK1000) "GPS" system
PR= np.sqrt(((pos[0]-AnchorsX)**2) + ((pos[1]-AnchorsY)**2) )

for idx in range(0,10):
	AR = np.sqrt(((pos[0]-AnchorsX)**2) + ((pos[1]-AnchorsY)**2))
	XH = (pos[0] - AnchorsX)/AR
	YH = (pos[1] - AnchorsY)/AR
	H = [[XH[0] , YH[0]]   ,[XH[1] , YH[1]],    [XH[1] , YH[2]]  ,    [XH[3] , YH[3]]]

	deltaPR = np.subtract(AR,PR)
	posChang =  np.linalg.lstsq(H,deltaPR)[0]
	pos = np.subtract(pos,posChang)
print "Final calculated postion of tag"
print pos