function [ s,flag ] = setupSerial(comPort,BAUD )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

flag = 1;
s = serial(comPort);
set(s,'DataBits',8);
set(s,'StopBits',1);
set(s,'BaudRate',BAUD);
set(s,'Parity','none');
fopen(s);
a='b';

%while a~='a'
 %   a=fread(s,1,'uchar');
%end

%if a=='a'
 %   disp('serial read');
%end
%fprintf(s,'%c','a');
mbox = msgbox('Serial Communication Setup'); uiwait(mbox);
%fscanf(s,'%u');
end

