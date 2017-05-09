#!/usr/bin/env python

import serial
import numpy as np
from itertools import combinations

s = serial.Serial('/dev/ttyACM0', timeout = 3 )

# anchor coordianates in  meters
AnchorsX = np.array([0.0,0.0,-3.2004,-1.6764])
AnchorsY = np.array([0,6.096,5.0292,1.8288])
AnchorsZ = np.array([1,1.5,1,1])

pos = np.array([0.00,4.00,2.00])
AR = np.array([[10],[1],[1],[1]])
PR = np.array([[2.9],[2.0],[2.7],[2.8]])

# PR0 = np.sqrt(((pos[0]-AnchorsX[0])**2) + ((pos[1]-AnchorsY[0])**2) + ((pos[2]-AnchorsZ[0])**2))
# PR1 = np.sqrt(((pos[0]-AnchorsX[1])**2) + ((pos[1]-AnchorsY[1])**2) + ((pos[2]-AnchorsZ[1])**2))
# PR2 = np.sqrt(((pos[0]-AnchorsX[2])**2) + ((pos[1]-AnchorsY[2])**2) + ((pos[2]-AnchorsZ[2])**2))
# PR3 = np.sqrt(((pos[0]-AnchorsX[3])**2) + ((pos[1]-AnchorsY[3])**2) + ((pos[2]-AnchorsZ[3])**2))+1
# PR = np.array([PR0,PR1,PR2,PR3])


	
for x in range(0,500):

	try:
		data = s.readline().split()
		if data[0] == 'mr':
			strn1='0'
			strn2='0'
			strn3='0'
			strn0='0'
		#print "read data as a list:"
		#print data
			mask = int(data[1],16)
			if (mask & 0x01):
			  #print "range0 good"
			  range0 = int(data[2],16)/1000.0
			  strn0=str(range0)

			else:
			  print "range0 bad"
			  # range0 = -1
			if (mask & 0x02):
			  #print "range1 good"
			  range1 = int(data[3],16)/1000.0
			  strn1=str(range1)

			else:
			  print "range1 bad"
			  # range1 = -1
			if (mask & 0x04):
			  #print "range2 good"
			  range2 = int(data[4],16)/1000.0
			  strn2=str(range2)

			else:
			  print "range2 bad"
			  # range2 = -1
			if (mask & 0x08):
			  #print "range3 good"
			  range3 = int(data[5],16)/1000.0
			  strn3=str(range3)

			else:
			  pass
			  #print "range3 bad"
			  # range3 = -1


		print( "rnstr:"+strn0+","+strn1+","+strn2+","+strn3)
	
		PR[0] =range0
		PR[1] = range1
		PR[2] = range2
		PR[3] =range3
		for idx in range(0,10):
			AR0 = np.sqrt(((pos[0]-AnchorsX[0])**2) + ((pos[1]-AnchorsY[0])**2) + ((pos[2]-AnchorsZ[0])**2))
			AR1 = np.sqrt(((pos[0]-AnchorsX[1])**2) + ((pos[1]-AnchorsY[1])**2) + ((pos[2]-AnchorsZ[1])**2))
			AR2 = np.sqrt(((pos[0]-AnchorsX[2])**2) + ((pos[1]-AnchorsY[2])**2) + ((pos[2]-AnchorsZ[2])**2))
			AR3 = np.sqrt(((pos[0]-AnchorsX[3])**2) + ((pos[1]-AnchorsY[3])**2) + ((pos[2]-AnchorsZ[3])**2))
			AR = np.array([AR0,AR1,AR2,AR3])

			XH = (pos[0] - AnchorsX)/AR
			YH = (pos[1] - AnchorsY)/AR
			ZH = (pos[2] - AnchorsZ)/AR
			H = [[XH[0] , XH[1],XH[2],XH[3]],[YH[0],YH[1],YH[2],YH[3]],[ZH[0],ZH[1],ZH[2],ZH[3]]]# print XH[0,1]
			# print H
			# print ''
			# print np.transpose(H)
			# print ''
			# print 'AR'
			# print AR
			# print ''
			# print 'PR'
			# print PR
			# assumedPR = ((pos[0,0] - AnchorsX)^2) + ((pos[0,1] - AnchorsY)^2) + ((pos[0,2] - AnchorsZ)^2)
			deltaPR = np.subtract(np.transpose(AR),np.transpose(PR))
			# print 'deltaPR'
			# print deltaPR
			# print ''
			# print np.shape(deltaPR)
			posChang =  np.linalg.lstsq(np.transpose(H), np.transpose(deltaPR))[0]
			# print 'posChang'
			# print posChang
			
			pos[0] = pos[0] - posChang[0]
			pos[1] = pos[1] - posChang[1]
			pos[2] = pos[2] - posChang[2]

			# print 'pos'
			# print pos

			# num_vars = Anchors.shape[1]
			# rank = np.linalg.matrix_rank(Anchors)
			# sol = np.linalg.lstsq(Anchors, ranges)[0]    # not under-determined
			# print sol
		print(chr(27) + "[2J")
		print pos

	except:
		pass
	# print range3



s.close()