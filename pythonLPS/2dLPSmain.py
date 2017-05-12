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
xbee= serial.Serial('/dev/ttyUSB0',baudrate=9600,   timeout = 3 )


AnchorsX = np.array([6.7056,0.0,0.0,6.7056])
AnchorsY = np.array([0.0,0.0,6.7056,6.7056])

# Postion of the tag to back calculate the ranges for testing purposes
pos = np.array([0.00,4.00])

# Intialize the arrays as floats with arbirtray values 
AR = np.array([10.0,1.0,1.0,1.0])
PR = np.array([2.0,2.0,2.0,2.0])



for x in range(0,5000):

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
					AR = np.sqrt(((pos[0]-AnchorsX)**2) + ((pos[1]-AnchorsY)**2))
					XH = (pos[0] - AnchorsX)/AR
					YH = (pos[1] - AnchorsY)/AR
					H = [[XH[0] , YH[0]]   ,[XH[1] , YH[1]],    [XH[1] , YH[2]]  ,    [XH[3] , YH[3]]]

					deltaPR = np.subtract(AR,PR)
					posChang =  np.linalg.lstsq(H,deltaPR)[0]
					pos = np.subtract(pos,posChang)
				print(chr(27) + "[2J")
				print("rnstr:" + str(range0) + "," + str(range1) + "," + str(range2) + ","+str(range3))
				listsend2 = ['<10,' , str(pos[0]) , ',' , str(pos[1]) , ',1>']
				# print listsend2
				# print('1')
				stringsend2 = ''.join("%s" % ''.join(map(str, x)) for x in listsend2)
				print(stringsend2)
				print pos
				xbee.write(stringsend2)
			else:
			  pass

		

	except:
		pass
	# print range3



s.close()