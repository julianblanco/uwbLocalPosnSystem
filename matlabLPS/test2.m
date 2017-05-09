clc
lat=41.3703;
long=72.0987;
lat1=lat-floor(lat);
lat2=floor(lat);
lat3=lat1*60;
string=strcat(num2str(lat2),num2str(lat3))

long1=long-floor(long)
long2=floor(long)
long3=floor(long1*60)
long4=(long1*60)-long3
b=num2str(long3,'%02.0f')
Long=strcat('0',num2str(long2),num2str(long3,'%02.0f'),num2str(long4,'%1.4f'))
% a=sprintf('%05.4f',long3)
% disp(a)
% 
% long1=long-floor(long);
% long2=floor(long)*100;
% long3=long*60/100;
% long4=long2+long3;
% Long=num2str(long4)
