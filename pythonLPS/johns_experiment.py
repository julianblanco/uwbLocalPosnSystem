#!/usr/bin/env python

import serial

s = serial.Serial('/dev/ttyACM0', timeout = 3 )

	
for x in range(0,50):

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

	except:
		pass
	# print range3



s.close()