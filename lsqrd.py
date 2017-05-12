import numpy as np

# Julian Blanco
# 09 May 2017
# Iterative Least Squared Estimation example, 
# 4 Ultrawide band anchors or "GPS Satilites"
# Location stored in the XYZ arrays in meters
# pos is the location of the tag or "GPS Reciever"

AnchorsX = np.array([5.18,-1.52,0.0,1.52])
AnchorsY = np.array([11.58,7.01,0,3.96])
AnchorsZ = np.array([1.31,1.06,1,3.048])

# Postion of the tag to back calculate the ranges for testing purposes
pos = np.array([0.00,4.00,2.00])

# Intialize the arrays as floats with arbirtray values 
AR = np.array([10.0,1.0,1.0,1.0])
PR = np.array([2.0,2.0,2.0,2.0])

#Calculate the ranges to the anchors, noramally would be solved for by the UWB (TREK1000) "GPS" system
PR= np.sqrt(((pos[0]-AnchorsX)**2) + ((pos[1]-AnchorsY)**2) + ((pos[2]-AnchorsZ)**2))

for idx in range(0,10):
	AR = np.sqrt(((pos[0]-AnchorsX)**2) + ((pos[1]-AnchorsY)**2) + ((pos[2]-AnchorsZ)**2))
	XH = (pos[0] - AnchorsX)/AR
	YH = (pos[1] - AnchorsY)/AR
	ZH = (pos[2] - AnchorsZ)/AR
	H = [[XH[0] , YH[0],ZH[0]]     ,[XH[1] , YH[1],ZH[1]],    [XH[1] , YH[2],ZH[2]]   ,    [XH[3] , YH[3],ZH[3]]]
	deltaPR = np.subtract(AR,PR)
	posChang =  np.linalg.lstsq(H,deltaPR)[0]
	pos = np.subtract(pos,posChang)
print "Final calculated postion of tag"
print pos