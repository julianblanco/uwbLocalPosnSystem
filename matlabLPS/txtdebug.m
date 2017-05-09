clear all 
clc
file = fopen('LPSdatadump3');
c= textscan(file,'%s %s %s %s %s %s %s %s %s %s');
Anchor0=cell2mat(c{3});
Anchor1=cell2mat(c{4});
Anchor2=cell2mat(c{5});
Anchor3=cell2mat(c{6});

for i=1:length(Anchor0)
    anchor0(i)=hex2dec(Anchor0(i,:))/1000;
    anchor1(i)=hex2dec(Anchor1(i,:))/1000;
    anchor2(i)=hex2dec(Anchor2(i,:))/1000;
    anchor3(i)=hex2dec(Anchor3(i,:))/1000;
end

X=[30;0;0;30];
Y=[30;30;0;0];
Z=[1.4;6.2;.6;1.4];

for index=1:length(anchor0)
    disp('*****************************************')
    disp(index)
    disp('*****************************************')
    
    PR(4,1)=anchor3(index);
    PR(3,1)=anchor2(index);
    PR(2,1)=anchor1(index);
    PR(1,1)=anchor0(index);
    
    x=0;
    y=0;
    z=0;
    for l=0:10
    H= [(x-X)./PR (y-Y)./PR (z-Z)./PR ] ;

    test2=H'*H;
    test1=det(test2);

    assumedPR= ((x-X).^2 + (y-Y).^2 + (z-Z).^2).^.5 ;
    deltaPR=assumedPR-PR ; 
    posChang= H\deltaPR ; 

    x=x-posChang(1,1) ;
    y=y-posChang(2,1) ;
    z=z-posChang(3,1) ;

    end


    disp('Calculated Position')
    disp('x')
    fprintf('%-0.9f\n',x);
    disp('y')
    fprintf('%1.1f\n',y);
    disp('z')
    fprintf('%1.1f\n\n',z);
    posn(index,1)=x;
    posn(index,2)=y;
    posn(index,3)=z;
end

% plot3(mat(:,1),mat(:,2),mat(:,3))
% axis([-8 8 -5.25 5.25 -3 10])
% hold on
% grid on
% pause(1)
% 
% disp('Finished')
% hold off;
%  
% pause()
%    closeSerial
