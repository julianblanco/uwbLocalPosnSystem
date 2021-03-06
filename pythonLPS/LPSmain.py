#!/usr/bin/env python

import serial
import numpy as np
# Julian Blanco
# 09 May 2017

# Iterative Least Squared Estimation example, 
# 4 Ultrawide band anchors or "GPS Satilites"
# Location stored in the XYZ arrays in meters
# pos is the location of the tag or "GPS Reciever"
s = serial.Serial('/dev/ttyACM0', timeout = 3 )

AnchorsX = np.array([4.2672,4.2672,0.0,0.0])
AnchorsY = np.array([0.0,9.4488,9.4488 ,0.0])
AnchorsZ = np.array([0.0,0.0,2.1336,0.0])

# Postion of the tag to back calculate the ranges for testing purposes
pos = np.array([0.00,4.00,2.00])

# Intialize the arrays as floats with arbirtray values 
AR = np.array([10.0,1.0,1.0,1.0])
PR = np.array([2.0,2.0,2.0,2.0])



for x in range(0,500):

	try:
		data = s.readline().split()
		if data[0] == 'mr':
			mask = int(data[1],16)
			if (mask & 0x01):
				range0 = int(data[2],16)/1000.0
				range1 = int(data[3],16)/1000.0
				range2 = int(data[4],16)/1000.0
				range3 = int(data[5],16)/1000.0
				PR = [range0 , range1 ,range2,range3]
				# Implment iterative least squared estimation
				for idx in range(0,10):
					AR = np.sqrt(((pos[0]-AnchorsX)**2) + ((pos[1]-AnchorsY)**2) + ((pos[2]-AnchorsZ)**2))
					XH = (pos[0] - AnchorsX)/AR
					YH = (pos[1] - AnchorsY)/AR
					ZH = (pos[2] - AnchorsZ)/AR
					H = [[XH[0] , YH[0],ZH[0]]     ,[XH[1] , YH[1],ZH[1]],    [XH[1] , YH[2],ZH[2]]   ,    [XH[3] , YH[3],ZH[3]]]
					deltaPR = np.subtract(AR,PR)
					posChang =  np.linalg.lstsq(H,deltaPR)[0]
					pos = np.subtract(pos,posChang)
				print(chr(27) + "[2J")
				print("rnstr:" + str(range0) + "," + str(range1) + "," + str(range2) + ","+str(range3))
				print pos
			else:
			  pass

		

	except:
		pass
	# print range3



s.close()