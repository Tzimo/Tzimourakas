clear
close all
clc

load('optimum_1_10000_0p1.txt')
x_S = optimum_1_10000_0p1(:,1);
y_S = optimum_1_10000_0p1(:,2);
x_M = optimum_1_10000_0p1(:,3);
y_M = optimum_1_10000_0p1(:,4);


r_E = 6371000; % m (Earth)
plot(x_S,y_S)
hold on
plot(x_M,y_M)
circle(0,0,r_E)
xlabel('x')
ylabel('y')
legend('Spacecraft','Moon','Earth')
pbaspect([1 1 1])


