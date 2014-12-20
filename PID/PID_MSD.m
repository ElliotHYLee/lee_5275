%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Example of PID control
%
% Affiliation: Ocean Engineering Lab., Seoul National University
% Name: Gyungnam Jo
%
% Problem: second order oscillation system (Mass-Spring-Damper system)
% My"(t) + By'(t) + Ky(t) = u(t)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

close all
clear all
clc

disp('Example for PID controller test');

tTimeStep = 1E-02;      % step size for numerical integration
tTotalTime = 2E+01;     % total simulation time
tHorizon = round(tTotalTime/tTimeStep);

% values for RK4 (4th order Runge-Kutta)
k1 = [0 0]';
k2 = [0 0]';
k3 = [0 0]';
k4 = [0 0]';

x   = [0 0]';   % initial value: x1(0) = 0, x2(0) = 0
r   = 3;        % reference input
ui  = 0;

out = zeros(tHorizon+1, 3);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% PID control
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Kp  = 5;        % Propotional gain
Ki  = 2;        % Integral gain
Kd  = 10;       % Differential gain

e       = 0;
ePre    = r;
eIntg   = 0;
eDiff   = 0;

out(1, :) = [x' ui];    % at t = 0
for t = 2:1:(tHorizon+1)
    y = [1 0]*x;
    e = r - y;
    eIntg = eIntg + (e + ePre)*tTimeStep/2;
    eDiff = (e - ePre)/tTimeStep;
    ePre = e;

    % input
    ui = Kp*e + Ki*eIntg + Kd*eDiff;

    % RK4
    k1 = MSD(x, ui);
    k2 = MSD(x + 0.5*tTimeStep*k1, ui);
    k3 = MSD(x + 0.5*tTimeStep*k2, ui);
    k4 = MSD(x + tTimeStep*k3, ui);

    x = x + tTimeStep*(k1 + 2*k2 + 2*k3 + k4)/6;

    out(t, :) = [x' ui];
end

disp('End of simulation')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Display
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

disp('Now... display the results')
t = 0:tTimeStep:tTotalTime;

figure('Name','position & velocity','NumberTitle','off');
subplot(211)
hold on
plot(t, out(:, 1), 'linewidth', 2, 'color', 'red'), grid;
plot(t, out(:, 2), 'linewidth', 2, 'color', 'green');
title('PID control'), legend('x_1: position', 'x_2: velocity');
hold off

subplot(212), plot(t, out(:, 3), 'linewidth', 2, 'color', 'red'), grid;
title('Input by PID'), legend('u');

disp('END');
