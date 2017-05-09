clear all;

clc;

debugmode=1;
numanchs =5;
noise=.1;
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
X=[5.18;-1.52;0;1.52;-1000000000];
Y=[11.58;7.01;0;3.96;-1000000000];
Z=[1.31;1.06;1;3.048;-1000000000];
one=[1;1;1;1] ;


loops = 10;

% X=  [30 ;   0;  0;  30 ];
% Y=  [30 ;  30;  0;  0  ];
% Z=  [1.4; 6.2; .6;  1.4];
% one=[1  ;   1;  1;  1  ];
% 
% X=  [-4 ;   -1;  3;  0 ];
% Y=  [2 ;   -3;  2;  0  ];
% Z=  [1.05;  1.05; 1;  2.2];
% one=[1  ;   1;  1;  1  ];

sendmode = 0;
%establish connection to Trek1000
%-------------------------------------------------
if debugmode==0
    %Establish the serial communication
    try
        comPort = '/dev/ttyS100';
        BAUD=9600;
        [trek1000 ,flag] = setupSerial(comPort,BAUD);
    catch
        try 
            comPort = '/dev/ttyS101';
            BAUD=9600;
            [trek1000 ,flag] = setupSerial(comPort,BAUD);
        catch
             try 
                comPort = '/dev/ttyS102';
                BAUD=9600;
                [trek1000 ,flag] = setupSerial(comPort,BAUD);
             catch
                 try 
                    comPort = '/dev/ttyS103';
                    BAUD=9600;
                    [trek1000 ,flag] = setupSerial(comPort,BAUD);
                catch
                    comPort = '/dev/ttyS104';
                    BAUD=9600;
                    [trek1000 ,flag] = setupSerial(comPort,BAUD);
                end
               
             end
            
        end
    end
end
% %-------------------------------------------------

%establish connection to xbee 
%-------------------------------------------------
if sendmode==1
    %Establish the serial communication
    try
        comPort = '/dev/ttyS105';
        BAUD=9600;
        [xbee ,flag] = setupSerial(comPort,BAUD);
    catch
        try 
            comPort = '/dev/ttyS106';
            BAUD=9600;
            [xbee ,flag] = setupSerial(comPort,BAUD);
        catch
             try 
                comPort = '/dev/ttyS107';
                BAUD=9600;
                [xbee ,flag] = setupSerial(comPort,BAUD);
             catch
                 try 
                    comPort = '/dev/ttyS108';
                    BAUD=9600;
                    [xbee ,flag] = setupSerial(comPort,BAUD);
                catch
                    comPort = '/dev/ttyS109';
                    BAUD=9600;
                    [xbee ,flag] = setupSerial(comPort,BAUD);
                end
               
             end
            
        end
    end
% %-------------------------------------------------
%Parse
end

pos=[0;0;0];
for k =1:loops;
    if debugmode ==0
        disp('******************************************')
        dist= fgetl(trek1000);
        c = strsplit(dist,' ');
        if strcmp(c(1),'mc')
                 PR(4,1)=hex2dec(c(6))/1000;
                 PR(3,1)=hex2dec(c(5))/1000;
                 PR(2,1)=hex2dec(c(4))/1000;
                 PR(1,1)=hex2dec(c(3))/1000;
        end

    end
    
    if debugmode == 1
        averageerror=0;
        pos=[0;4;2];
       for anch=1:numanchs-1
           PR(anch,1)=((pos(1,1)-X(anch)).^2+(pos(2,1)-Y(anch)).^2+(pos(3,1)-Z(anch)).^2).^.5;
           PR(anch,1)=PR(anch,1)+(rand(1)*noise)-(noise*.5);
       end
       anch = 5;
        PR(anch,1)=((pos(1,1)-X(anch)).^2+(pos(2,1)-Y(anch)).^2+(pos(3,1)-Z(anch)).^2).^.5;
        
    end
    
      
%% Range Calculation
%Assume Pos Center of Roland
x=0;
y=0;
z=0;


    for l=0:loops
        %calculate assumed ranges
        for anch=1:numanchs 
           AR(anch,1)= ((pos(1,1)-X(anch)).^2+(pos(2,1)-Y(anch)).^2+(pos(3,1)-Z(anch)).^2).^.5;
        end
        
        %Calculate H matrix
        H= [(pos(1,1)-X)./AR (pos(2,1)-Y)./AR (pos(3,1)-Z)./AR ] ;
        H2H=H'*H;
        test1=det(H2H);
        confidence=inv(H2H)
        tracH=trace(confidence);
        
        %Iterate through assumptions
        deltaPR=AR-PR ;
        posChang= H\deltaPR ; 

        %Update assumed postion
        pos(1,1)=pos(1,1)-posChang(1,1) ;
        pos(2,1)=pos(2,1)-posChang(2,1) ;
        pos(3,1)=pos(3,1)-posChang(3,1) ;

    end
     disp('Calculated Position')
     disp('x')
     fprintf('%-0.4f\n',pos(1,1));
     disp('y')
     fprintf('%-0.4f\n',pos(2,1));
     disp('z')
     fprintf('%-0.4f\n\n',pos(3,1));

      if debugmode == 1
          averageerror=(averageerror + abs(pos(3,1)-2))/loops;
      end

    posn(l,1)=pos(1,1);
    posn(l,2)=pos(2,1);
    posn(l,3)=pos(3,1);

%     disp('Actual Position')
%     disp('x')
%     fprintf('%1.1f\n',pos(1));
%     disp('y')
%     fprintf('%1.1f\n',pos(2));
%     disp('z')
%     fprintf('%1.1f\n\n',pos(3));

mat(k,1)=pos(1,1);
mat(k,2)=pos(2,1);
mat(k,3)=pos(3,1);

%send data to craft
if sendmode
sendstring=converttoGGA(pos(1,1),pos(2,1),pos(3,1),41.370256, -72.098722);
disp(sendstring)
fprintf(xbee,'%c',sendstring);
%dist= fgetl(xbee)
end

% plotting postion
% plot3(mat(:,1),mat(:,2),mat(:,3))
% axis([-8 8 -5.25 5.25 -3 10])
% hold on
% grid on
% pause(1)
end

disp('Finished')
% hold off;
%  
% pause()
%    closeSerial

if debugmode
    averageerror
end
