%% Title
% Michael Tzimourakas
% ASEN 4057
% Exam
%% Part 1
%global m1 m2 l1 l2 
%% Given
%g = 9.81; % m/s^2
%% System of Equations
% Acceleration system
%syms theta_dot_dot1 theta_dot_dot2 theta1 theta2 theta_dot1 theta_dot2 m1 m2 l1 l2 g
%Y = (m1+m2)*l1*theta_dot_dot1 + m2*l2*theta_dot_dot2*cos(theta1-theta2) + m2*l2*theta_dot2^2*sin(theta1-theta2) + g*(m1+m2)*sin(theta1) == 0;
%theta_dot_dot1 = solve(Y,theta_dot_dot1);

%X = (m2*l2)*theta_dot_dot2 + m2*l1*theta_dot_dot1*cos(theta1-theta2) - m2*l1*theta_dot1^2*sin(theta1-theta2)+m2*g*sin(theta2) == 0;
%[theta_dot_dot1,theta_dot_dot2] = solve([X,Y],[theta_dot_dot1,theta_dot_dot2])

function [t,x1,z1,x2,z2,theta1,theta2,theta_dot1,theta_dot2] = main(m1,m2,l1,l2,theta1,theta2,theta_dot1,theta_dot2,tfinal,handles)
%% Test Case
global g
m1 = m1;
m2 = m2;
l1 = l1;
l2 = l2;
tspan = [0,tfinal];
g = 9.81;
y0 = [theta1,theta2,theta_dot1,theta_dot2];
%% Output
[t,y] = ode45(@simulate_pendulum,tspan,y0);
theta1 = y(:,1);
theta2 = y(:,2);
theta_dot1 = y(:,3);
theta_dot2 = y(:,4);
x1 = l1*sin(theta1);
z1 = -l1*cos(theta1);
x2 = l1*sin(theta1) + l2*sin(theta2);
z2 = -l1*cos(theta1) - l2*cos(theta2);
end