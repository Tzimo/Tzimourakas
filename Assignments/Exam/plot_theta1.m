function plot_theta1(t,theta1,theta2,x1,z1,x2,z2,handles)
grid on
axes(handles.theta1)
plot(handles.theta1,t,theta1)
grid on
xlabel('Time [sec]')
ylabel('Angle [deg]')
title('Angle of Mass 1')
end

