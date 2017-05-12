currentposn = [ 0,0];
targetpos   = [-10,-10];
errorpos = targetpos - currentposn;
errorpos(1) =  currentposn(1)-targetpos(1);


targetangle = rad2deg(atan2(errorpos(2),errorpos(1)) )-90
if targetangle < 0 
    
    targetangle = targetangle+360
end

