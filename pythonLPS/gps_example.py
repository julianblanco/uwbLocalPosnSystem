import numpy as np

# Julian Blanco
# 09 May 2017
# Iterative Least Squared Estimation for GPS


AnchorsX = np.array([7433442.899,-4930906.599,348603.197,-11440481.794,20929924.126])
AnchorsY = np.array([-22926895.92,-25650220.33,-15668323.327,-23040016.991,-7467688.968])
AnchorsZ = np.array([11096844.746,4268436.452,21765664.376,6063975.734,14549441.864])

actual_pos = np.array([8.714344783566145e5,-5.087634969190530e+06,3.734064076242158e+06])
prop_speed = 3e8



TOA_dif = np.array([-0.82393, -0.081971, 1.3548, 0.75345, 0.81529])
PR = [22784055.7,23772239.8, 23313223.8, 24292916.5, 25312443.4];
#seed an intial assumed posistion
assumed_pos = np.array([1.00,1.00,1.00])

# Intialize the arrays as floats with arbirtray values 
AR = np.array([10.0,1.0,1.0,1.0])

DxDyDsi = None
for idx in range(0,10):
	#calculate the assumed ranges between rx and transmitter
	AR = np.sqrt(((assumed_pos[0]-AnchorsX)**2) + ((assumed_pos[1]-AnchorsY)**2) + ((assumed_pos[2]-AnchorsZ)**2))
	#calculate each range diff per transmitter
	XH = (assumed_pos[0] - AnchorsX)/AR
	YH = (assumed_pos[1] - AnchorsY)/AR
	ZH = (assumed_pos[2] - AnchorsZ)/AR
	#create your H matrix
	H = [[XH[0] , YH[0],ZH[0],1]     ,[XH[1] , YH[1],ZH[1],1],    [XH[2] , YH[2],ZH[2],1]   ,    [XH[3] , YH[3],ZH[3],1], [XH[4] , YH[4],ZH[4],1]]
	deltaPR = np.subtract(AR,PR)
	#solve
	DxDyDsi =  np.linalg.lstsq(H,deltaPR,rcond=None)[0]
	# print(np.linalg.lstsq(H,deltaPR))
	print("Step " + str( idx) + " Calculated POSN: ", assumed_pos)
	assumed_pos = np.subtract(assumed_pos,DxDyDsi[0:3])
print("")
print("Final calculated postion of tag")
print(assumed_pos)
print("Actual Pos")
print(actual_pos)
error = assumed_pos-actual_pos
errorsum = np.sqrt(error[0]**2 + error[1]**2 + error[2]**2)
print("Error: ", errorsum)
time_offset = DxDyDsi[3]/prop_speed
print("Time offset is: ",time_offset)