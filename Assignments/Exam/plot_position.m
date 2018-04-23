function plot_position(t,theta1,theta2,x1,z1,x2,z2,handles)
grid on
axes(handles.position1)
plot(handles.position1,x1,z1)
xlabel('x-position [m]')
ylabel('z-position [m]')
title('Position of Mass 1')
hold on
plot(handles.position1,x2,z2)
xlabel('x-position [m]')
ylabel('z-position [m]')
title('Position of Mass 2')
grid on
legend('Mass 1','Mass 2')
end
