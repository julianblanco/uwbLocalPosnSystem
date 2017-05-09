
function [ outstring ] = converttoGGA( x,y,z,beginLat,beginLong)
%Converts x,y,z coordinates to a GNGGA string
%   Detailed explanation goes here



lat=beginLat+(x/111319.9);
lat1=lat-floor(lat);
lat2=floor(lat);
lat3=lat1*60;
Lat=strcat(num2str(lat2),num2str(lat3));

long=beginLong+(y/111319.9)
long1=long-floor(long);
long2=floor(long);
long3=floor(long1*60);
long4=(long1*60)-long3;
Long=strcat(num2str(long2),num2str(long3,'%02.0f'),num2str(long4,'%1.4f'));


tiempo=clock;
outstring=strcat('$GNGGA,',num2str(tiempo(4)),num2str(tiempo(5)),num2str(round(tiempo(6)))...
    ,',',Lat,',N,',Long,',W,1,08,0.9,',num2str(z),',M,46.9,M*****');

outstring=strcat('<$OA008',',',num2str(lat),',',num2str(long),',',num2str(z),'>');
%outstring=strcat('<$OA008',',','5',',','10',',',num2str(z),'>');


end



% 
% 
% GGA - essential fix data which provide 3D location and accuracy data.
% 
%  $GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47
% 
% Where:
%      GGA          Global Positioning System Fix Data
%      123519       Fix taken at 12:35:19 UTC
%      4807.038,N   Latitude 48 deg 07.038' N
%      01131.000,E  Longitude 11 deg 31.000' E
%      1            Fix quality: 0 = invalid
%                                1 = GPS fix (SPS)
%                                2 = DGPS fix
%                                3 = PPS fix
% 			       4 = Real Time Kinematic
% 			       5 = Float RTK
%                                6 = estimated (dead reckoning) (2.3 feature)
% 			       7 = Manual input mode
% 			       8 = Simulation mode
%      08           Number of satellites being tracked
%      0.9          Horizontal dilution of position
%      545.4,M      Altitude, Meters, above mean sea level
%      46.9,M       Height of geoid (mean sea level) above WGS84
%                       ellipsoid
%      (empty field) time in seconds since last DGPS update
%      (empty field) DGPS station ID number
%      *47          the checksum data, always begins with *
% 
