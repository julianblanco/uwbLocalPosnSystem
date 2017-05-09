clear all;

clc;

debugmode=1;
%closeSerial;
%Roland Hall localzation

%ActualPos is where tag (plane) is inside of roland
%X ActualPos(1) is meters north of the center of roland
%Y ActualPos(2) is meters west of the center of roland
%Z ActualPos(3) is altitude in meters above the floor

%6 beacons spaced around roland
%   two at north end, 2 @ middle and 2 @ south end

%Beacon Locations
%1 AC unit
%2 Top of shelf
%3 Middle power lab bench 
X=[10;0;3];
Y=[-10;5;5];
Z=[0;-5;3];
one=[1;1;1] ;

%-------------------------------------------------
if debugmode==0
    %Establish the serial communication
    try
        comPort = '/dev/ttyUSB0';
        BAUD=9600;
        [xbee ,flag] = setupSerial(comPort,BAUD);
    catch
        try 
            comPort = '/dev/ttyUSB1';
            BAUD=9600;
            [xbee ,flag] = setupSerial(comPort,BAUD);
        catch
            comPort = '/dev/ttyUSB2';
            BAUD=9600;
            [xbee ,flag] = setupSerial(comPort,BAUD);
        end
    end
% %-------------------------------------------------
%Parse
end
for k =1:30;
    if debugmode ==0
        dist= fgetl(xbee);
        c = strsplit(dist,',');
        if strcmp(c(1),'3FB2')
            PR(3,1)=str2num(c(2));
            
        elseif strcmp(c(1),'B8AE')
            PR(2,1)=str2num(c(2));
            
        elseif strcmp(c(1),'N2AR')
            PR(1,1)=str2num(c(2));
            
        end
    end
       PR(3,1)=k/10;
       PR(2,1)=5;
        
       PR(1,1)=7;
%% Range Calculation
%Assume Pos Center of Roland
x=0;
y=0;
z=0;

for l=0:7
H= [(x-X)./PR (y-Y)./PR (z-Z)./PR one] ;

assumedPR= ((x-X).^2+(y-Y).^2+(z-Z).^2).^.5 ;
deltaPR=assumedPR-PR ;
posChang= H\deltaPR ; 

x=x-posChang(1,1) ;
y=y-posChang(2,1) ;
z=z-posChang(3,1) ;

end


disp('Calculated Position')
disp('x')
fprintf('%1.1f\n',x);
disp('y')
fprintf('%1.1f\n',y);
disp('z')
fprintf('%1.1f\n\n',z);
mat(k,1)=x;
mat(k,2)=y;
mat(k,3)=z;
plot3(mat(:,1),mat(:,2),mat(:,3))
hold on
grid on
end
    
disp('Finished')
hold off;
 
