function  closeSerial( )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here


if ~isempty(instrfind)
    fclose(instrfind);
    delete(instrfind);
end
close all
clc
disp('Serial Port Closed')

end

