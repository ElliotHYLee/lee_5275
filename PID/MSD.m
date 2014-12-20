function xDot = MSD(x, ui)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Problem: second order oscillation system (Mass-Spring-Damper system)
% My"(t) + By'(t) + Ky(t) = u(t)
%
% Affiliation: Ocean Engineering Lab., Seoul National University
% Name: Gyungnam Jo
% Date: Aug. 3, 2008
% Revision: 
%
% ODE to state-space equation
% x1 = y;
% x2 = (dx1/dt)
% ==>
% x = [x1; x2]
% A = [0, 1; -K/M, -B/M];
% (dx/dt) = A*x
%
% input: x, ui
% x =   [x1, x2]'       state variable
% ui =  u               input value (scalar)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

M = 5;          % mass in kg 
B = 1;          % damping in N*m/s 
K = 2;          % spring contant in N/m

xDot1 = x(2);                                       % position  [m]
xDot2 = (-K/M)*x(1) + (-B/M)*x(2) + (1/M)*ui;       % velocity  [m/s]
xDot = [xDot1 xDot2]';
