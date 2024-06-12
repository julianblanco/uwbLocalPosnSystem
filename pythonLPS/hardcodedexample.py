import numpy as np

# Julian Blanco
# 09 May 2017
# Iterative Least Squared Estimation example, 
# 4 Ultrawide band anchors or "GPS Satilites"
# Location stored in the XYZ arrays in meters
# pos is the location of the tag or "GPS Reciever"


#transmitter locations
AnchorsX = np.array([4.2672,4.2672,0.0,0.0])
AnchorsY = np.array([0.0,9.4488,9.4488 ,0.0])
AnchorsZ = np.array([0.0,0.0,2.1336,0.0])

# Postion of the tag to back calculate the ranges for testing purposes
actual_pos = np.array([0.00,5.00,2.00])

#seed an intial assumed posistion
assumed_pos = np.array([1.00,1.00,1.00])

# Intialize the arrays as floats with arbirtray values 
AR = np.array([10.0,1.0,1.0,1.0])


#noise to add into the psuedorange 
noise = np.random.normal(0,0.25,4)
noise = [ 0.1386615 ,  0.15243554 ,-0.0791783,   0.13177498]
print(noise)
# first argument is the mean of the normal distribution you are choosing from
# 2nd is the standard deviation of the normal distribution
# third is the number of elements you get in array 


#Calculate the ranges to the anchors, normally would be solved for by the UWB (TREK1000) "GPS" system with noise
acutal_ranges = PR= np.sqrt(((actual_pos[0]-AnchorsX)**2) + ((actual_pos[1]-AnchorsY)**2) + ((actual_pos[2]-AnchorsZ)**2))
PR= acutal_ranges + noise
print("Actual Ranges: " ,acutal_ranges)
print("Noisy Ranges: ", PR)
print("")
for idx in range(0,10):
	#calculate the assumed ranges between rx and transmitter
	AR = np.sqrt(((assumed_pos[0]-AnchorsX)**2) + ((assumed_pos[1]-AnchorsY)**2) + ((assumed_pos[2]-AnchorsZ)**2))
	#calculate each range diff per transmitter
	XH = (assumed_pos[0] - AnchorsX)/AR
	YH = (assumed_pos[1] - AnchorsY)/AR
	ZH = (assumed_pos[2] - AnchorsZ)/AR
	#create your H matrix
	H = [[XH[0] , YH[0],ZH[0]]     ,[XH[1] , YH[1],ZH[1]],    [XH[2] , YH[2],ZH[2]]   ,    [XH[3] , YH[3],ZH[3]]]
	deltaPR = np.subtract(AR,PR)
	#solve
	posChang =  np.linalg.lstsq(H,deltaPR,rcond=None)[0]
	# print(np.linalg.lstsq(H,deltaPR))
	print("Step " + str( idx) + " Calculated POSN: ", assumed_pos)
	assumed_pos = np.subtract(assumed_pos,posChang)
print("")
print("Final calculated postion of tag")
print(assumed_pos)
print("Actual Pos")
print(actual_pos)
error = assumed_pos-actual_pos
errorsum = np.sqrt(error[0]**2 + error[1]**2 + error[2]**2)
print("Error: ", errorsum)