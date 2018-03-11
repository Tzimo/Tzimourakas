/*
Michael Tzimourakas
Ross Kloetzel
*/


int main()
{

double m_M,m_E,m_S,r_M,r_E,G,theta_S,theta_M;


G = 6.674e-11; //% N(m/kg)^2
m_M = 7.34767309e22; //% kg (Moon)
m_E = 5.97219e24; //% kg (Earth)
m_S = 28833; //% kg (Spacecraft)
r_M = 1737100; //% m (Moon)
r_E = 6371000; //% m (Earth)
theta_S = 50; //% degrees (Spacecraft)
theta_M = 42.5; //% Degrees (Moon)
step = 1; // m/s
vf = 100; // final velocity to test
steps = vf/step; // step size
}


//int main( x_S,y_S,x_M,y_M,v_S_x,v_S_y + 80,v_M_x,v_M_y,stop )
//{

/*% Calculating 4th oder Runge Kutta Method
xrunge = x0;
yrunge = y0;

for i = 1:steps
    
    k1 = dydx(xrunge(i), yrunge(i));
    k2 = dydx(xrunge(i) + .5*dx, yrunge(i) + .5*k1*dx);
    k3 = dydx(xrunge(i) + .5*dx, yrunge(i) + .5*k2*dx);
    k4 = dydx(xrunge(i) + dx, yrunge(i) + k3*dx);
    
        yrunge(i+1) = yrunge(i) + (dx/6)*(k1 + 2*k2 + 2*k3 + k4);
        xrunge(i+1) = xrunge(i) + dx;
end
*/






//}