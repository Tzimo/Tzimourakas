function [output] = simulate_pendulum(t,y)
%% Constants
global m1 m2 l1 l2 g
%% Initial Conditions
theta1 = y(1);
theta2 = y(2);
theta_dot1 = y(3);
theta_dot2 = y(4);
%% Equations of Motion

V = -(m1 + m2)*g*l1*cos(theta1) - m2*g*l2*cos(theta2);

K = (m1+m2)/2*l1^2*theta_dot1^2 +(0.5)*m2*l2^2*theta_dot2^2 + m2*l1*l2*theta_dot1*theta_dot2*cos(theta1-theta2);
L = K - V;

x1 = l1*sin(theta1);
z1 = -l1*cos(theta1);
x2 = l1*sin(theta1) + l2*sin(theta2);
z2 = -l1*cos(theta1) - l2*cos(theta2);

theta_dot_dot1 = -(l1*m2*cos(theta1 - theta2)*sin(theta1 - theta2)*theta_dot1^2 + l2*m2*sin(theta1 - theta2)*theta_dot2^2 + g*m1*sin(theta1) + g*m2*sin(theta1) - g*m2*cos(theta1 - theta2)*sin(theta2))/(l1*(m1 + m2 - m2*cos(theta1 - theta2)^2));
 
theta_dot_dot2 = (g*m1*cos(theta1 - theta2)*sin(theta1) - g*m2*sin(theta2) - g*m1*sin(theta2) + g*m2*cos(theta1 - theta2)*sin(theta1) + l1*m1*theta_dot1^2*sin(theta1 - theta2) + l1*m2*theta_dot1^2*sin(theta1 - theta2) + l2*m2*theta_dot2^2*cos(theta1 - theta2)*sin(theta1 - theta2))/(l2*(m1 + m2 - m2*cos(theta1 - theta2)^2));

output(3) = theta_dot_dot1;
output(4) = theta_dot_dot2;
output(1) = theta_dot1;
output(2) = theta_dot2;
output = output';
end

