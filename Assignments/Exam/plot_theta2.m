function plot_theta2(t,theta1,theta2,x1,z1,x2,z2,handles)
grid on
axes(handles.theta2)
plot(handles.theta2,t,theta2)
grid on
xlabel('Time [sec]')
ylabel('Angle [deg]')
title('Angle of Mass 2')
end
