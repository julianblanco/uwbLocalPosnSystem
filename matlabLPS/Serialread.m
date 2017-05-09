clear all;
clc;
closeSerial;
comPort = '/dev/ttyUSB0';
BAUD=9600;



Targetbox =findobj(Bobogui,'Tag','Target');
Truebox =findobj(Bobogui,'Tag','True');
GPSHeadingbox =findobj(Bobogui,'Tag','GpsHeading');
Gyrobox =findobj(Bobogui,'Tag','Gyro');
HeadingErrorbox =findobj(Bobogui,'Tag','HeadingError');
Fixbox =findobj(Bobogui,'Tag','Fix');
WPnumbox =findobj(Bobogui,'Tag','WPnumbox');
Speedbox =findobj(Bobogui,'Tag','SOG');
CurLat =findobj(Bobogui,'Tag','CurrentLat');
CurLong =findobj(Bobogui,'Tag','CurrentLong');
TarLat =findobj(Bobogui,'Tag','TargetLat');
TarLong =findobj(Bobogui,'Tag','TargetLong');




[arduino ,flag] = setupSerial(comPort,BAUD);
pause(.01);
alpha = 5;
  dummy = fgetl(arduino);
for k =1:300;
dist= fgetl(arduino);
   if strcmp(dist(1),'&')
    dummy= fgetl(arduino);
    %TargetHeading=str2num(dummy(17:24));
    TargetHeading=str2num(dummy(18:24));
    disp(strcat('Target Heading: ',num2str(TargetHeading)));
    
    dummy= fgetl(arduino);
    TrueHeading=str2num(dummy(18:24));
    disp(strcat('TrueHeading: ',num2str(TrueHeading)));
    
     
    dummy= fgetl(arduino);
    GpsHeading=str2num(dummy(13:20));
    disp(strcat('GPS Heading: ',num2str(GpsHeading)));
    
    dummy= fgetl(arduino);
    GyroHeading=str2num(dummy(15:21));
    disp(strcat('Gyro Heading: ',num2str(GyroHeading)));
    
    dummy= fgetl(arduino);
    HeadingError=str2num(dummy(16:22));
    disp(strcat('Heading Error: ',num2str(HeadingError)));
    
    dummy= fgetl(arduino);
    Fix=str2num(dummy(6:7));
    disp(strcat('Fix: ',num2str(Fix)));
    
    dummy= fgetl(arduino);
    CurrentLat=str2num(dummy(13:20));
    disp(strcat('Current Lat: ',num2str(CurrentLat)));
    
    dummy= fgetl(arduino);
    CurrentLong=str2num(dummy(15:20));
    disp(strcat('Current Long: ',num2str(CurrentLong)));
    
     dummy= fgetl(arduino);
    TargetLat=str2num(dummy(13:20));
    disp(strcat('Target Lat: ',num2str(TargetLat)));
    
     dummy= fgetl(arduino);
    TargetLong=str2num(dummy(15:21));
    disp(strcat('Target Long: ',num2str(TargetLong)));
    
    dummy= fgetl(arduino);
    SpeedOverGround=str2num(dummy(6:8));
    disp(strcat('SpeedOverGround: ',num2str(SpeedOverGround)));
    
    dummy= fgetl(arduino);
    wpnum=str2num(dummy(7:8));
    disp(strcat('WP Number: ',num2str(wpnum)));
    
    dummy= fgetl(arduino);
    Distance2Target=str2num(dummy(13:19));
    disp(strcat('Distance 2 Target: ',num2str(Distance2Target)));
    
    disp('************************************************')
 
    
    
    
    
    set(Targetbox,'String',num2str(TargetHeading));
    set(Truebox,'String',num2str(TrueHeading));
    set(GPSHeadingbox,'String',num2str(GpsHeading));
    set(Gyrobox,'String',num2str(GyroHeading));
    set(HeadingErrorbox,'String',num2str(HeadingError));
    set(Fixbox,'String',num2str(Fix));
    set(WPnumbox,'String',num2str(wpnum));
    set(Speedbox,'String',num2str(SpeedOverGround));
    set(CurLat,'String',num2str(CurrentLat));
    set(CurLong,'String',num2str(CurrentLong));
    set(TarLat,'String',num2str(TargetLat));
    set(TarLong,'String',num2str(TargetLong));
    
    drawnow;
    
   end
    
end



   disp('Finished')
