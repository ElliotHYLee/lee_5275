% Group F
% Brady Kreamer, Elliot Lee, Yunan He, Whitney Smelly
% Section 1, 8:00am

% Task 7
% Calculating the Train's Speed

% Connect the arduino

% Turn Train On in the forward direction.
a.motorRun(1,'forward')

% Turn train on at maximum speed.
a.motorSpeed(1,255)

% set approach and depature values
approach = 2;
departure = 3;

   app= a.analogRead(approach)
   dep= a.analogRead(departure)
    
while ((app<100) & (dep<120))
    a.motorRun(1,'Forward')
    a.motorSpeed(1,255)
 
    if ((app<100)&(dep>50))
            start = tic
    elseif ((app<50) & (dep>100))
            theEnd = toc(start)
    end
end 
    a.motorSpeed(1,0)




