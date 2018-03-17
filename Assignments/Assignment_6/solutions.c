/*
 ASEN 4057 Assignment 6 - Apollo 13 Simulation
 Ross Kloetzel and Michael Tzimourakas
 March 16, 2018
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define pi 3.14159

void main(int argc, char **argv)
{
	int i =0;
	double objective=atof(argv[1]);
	double clearance=atof(argv[2]);
	double accuracy = atof(argv[3]);

	//printf("%f\n%f\n%f\n",objective,clearance,accuracy);
	double *V;
	double *V_time;
	double mag=100;

	FILE * fPointer;
	fPointer = fopen("solutions.txt", "w+");


	int time_length=(5*24*3600);
	int sizes=10000;
	if (objective==1)
	{
		int sizes=(40*3660);
		int step = 1;
	}
	else if (objective==2)
	{
		int sizes=(80*60);
		int step=1;
	}

	// int sizes=(85*3600);
	// Physical Variables of System 
	double m_M,m_E,m_S,r_M,r_E,G,theta_S,theta_M,
			d_ES,d_EM,x_E,y_E,x_M[sizes],y_M[sizes],x_S[sizes],y_S[sizes],
			vx_E,vy_E,v_M,vx_M[sizes],vy_M[sizes],v_S,vx_S[sizes],vy_S[sizes],
			Fx_EM,Fx_ES,Fx_MS,Fy_EM,Fy_ES,Fy_MS;
	int time=85*3600;

	m_M = 7.34767309e22; // [kg]
	m_E = 5.97219e24; 	 // [kg]
	m_S = 28833; 		 // [kg]
	r_M = 1737100;       // [m]
	r_E = 6371000;       // [m]
	G = 6.67408e-11;     // [N(m/kg)^2]
	theta_S = 50*(pi/180);      // [deg]
	theta_M = 42.5*(pi/180);    // [deg]
	// Distances
	d_ES = 338000000; // 338,000,000 [m]
	d_EM = 384403000; // 384,403,000 [m]
	// Position
	x_E = 0; // [m]
	y_E = 0; // [m]
	x_M[0] = d_EM*cos(theta_M); // [m]
	y_M[0] = d_EM*sin(theta_M); // [m]
	x_S[0] = d_ES*cos(theta_S); // [m]
	y_S[0] = d_ES*sin(theta_S); // [m]

	// Velocity
	vx_E = 0; // [m/s]
	vy_E = 0; // [m/s]
	v_M = sqrt((G*pow(m_E,2))/((m_E+m_M)*d_EM)); // [m/s]
	vx_M[0] = -v_M*sin(theta_M); 				// [m/s]
	vy_M[0] = v_M*cos(theta_M); 				// [m/s]
	v_S = 1000; 

	for (double k=-20;k<=20;k=k+accuracy/pow(2,0.5)){
		for (double j=60; j<=90;j=j+accuracy/pow(2,0.5)){
		// Delta V
		double delta_V[2] = {k,j};
		vx_S[0] = v_S*cos(theta_S) + delta_V[0];  // [m/s]
		vy_S[0] = v_S*sin(theta_S) + delta_V[1];  // [m/s] 
		// EULER
		int step = 100; 
		int i=0;

		for ( double deltat = 0; deltat < time_length; deltat = deltat + step) {
			double d_SM = sqrt(pow(x_S[i]-x_M[i],2)+pow(y_S[i]-y_M[i],2));
			double d_ES = sqrt(pow(x_E-x_S[i],2)+pow(y_E-y_S[i],2));
			double d_EM = sqrt(pow(x_E-x_M[i],2)+pow(y_E-y_M[i],2));
			double mag_temp = sqrt(pow(j,2)+pow(k,2));
			// Forces
			Fx_ES = (G*m_E*m_S*(x_E-x_S[i])) / pow(d_ES,3);
			Fy_ES = (G*m_E*m_S*(y_E-y_S[i])) / pow(d_ES,3);
			Fx_MS = (G*m_M*m_S*(x_M[i]-x_S[i])) / pow(d_SM,3);
			Fy_MS = (G*m_M*m_S*(y_M[i]-y_S[i])) / pow(d_SM,3);
			Fx_EM = (G*m_E*m_M*(x_E-x_M[i])) / pow(d_EM,3);
			Fy_EM = (G*m_E*m_M*(y_E-y_M[i])) / pow(d_EM,3);
			// Velocity
			vx_S[i+1] = vx_S[i] + step*(Fx_MS + Fx_ES)/(m_S);
			vy_S[i+1] = vy_S[i] + step*(Fy_MS + Fy_ES)/(m_S);
			vx_M[i+1] = vx_M[i] + step*(Fx_EM - Fx_MS)/(m_M);
			vy_M[i+1] = vy_M[i] + step*(Fy_EM - Fy_MS)/(m_M);
			// Position
			x_S[i+1] = x_S[i] + step*(vx_S[i+1]);
			y_S[i+1] = y_S[i] + step*(vy_S[i+1]);
			x_M[i+1] = x_M[i] + step*(vx_M[i+1]);
			y_M[i+1] = y_M[i] + step*(vy_M[i+1]);
			i++;
			double time_temp = i*step;
			// Check conditions
			if (d_SM <= (r_M + clearance)){
				break;
			}
			else if(d_ES <= r_E){
				if (objective ==1 && mag_temp<mag){
				mag=mag_temp;
				double results[3]={k,j,mag};
				V = results;
				//printf("%lf",mag);
	 	  		}
	    		if (objective==2 && time_temp<time){
				time=time_temp;
				//fprintf(fPointer, "%lf,%lf,%lf\n",k,j,mag);
				//double results_time[4]={k,j,mag_temp,time};
				double results[4]={k,j,mag_temp,time};
				V = results;
	    		}
				break;
			}
			else if (d_ES >= 2*d_EM)
			{
				break;
			}
			else {
				continue;
			} // If
		} // Euler
	} // Y for loop
	} // X for loop

	if (objective==1)
	{
	fprintf(fPointer, "%lf,%lf,%lf\n",*(V),*(V+1),*(V+2));
	printf("X DeltaV: %lf m/s\nY DeltaV: %lf m/s\nMagnitude: %lf m/s\n",
		*(V),*(V+1),*(V+2));

	//fprintf(fPointer, "%lf\n",mag);
	}
	else if (objective==2)
	{
	fprintf(fPointer, "%lf,%lf,%lf,%lf\n",*(V),*(V+1),*(V+2),*(V+3));
	printf("X DeltaV: %lf m/s\nY DeltaV: %lf m/s\nMagnitude: %lf m/s\nTime: %lf hours\n",
		*(V),*(V+1),*(V+2),*(V+3)/3600);
	}
	fclose(fPointer);

// ------------------------------------------------------------ //
// ------------------------------------------------------------ //
	vx_S[0] = v_S*cos(theta_S) + *(V);  // [m/s]
	vy_S[0] = v_S*sin(theta_S) + *(V+1);  // [m/s] 
	// EULER
	int step = 100; 
	i=0;

	FILE * fPointer2;
	fPointer2 = fopen("optimum_1_10000_0p1.txt", "w+");

	for ( double deltat = 0; deltat < time_length; deltat = deltat + step) {
		double d_SM = sqrt(pow(x_S[i]-x_M[i],2)+pow(y_S[i]-y_M[i],2));
		double d_ES = sqrt(pow(x_E-x_S[i],2)+pow(y_E-y_S[i],2));
		double d_EM = sqrt(pow(x_E-x_M[i],2)+pow(y_E-y_M[i],2));
		//double mag_temp = sqrt(pow(j,2)+pow(k,2));
		// Forces
		Fx_ES = (G*m_E*m_S*(x_E-x_S[i])) / pow(d_ES,3);
		Fy_ES = (G*m_E*m_S*(y_E-y_S[i])) / pow(d_ES,3);
		Fx_MS = (G*m_M*m_S*(x_M[i]-x_S[i])) / pow(d_SM,3);
		Fy_MS = (G*m_M*m_S*(y_M[i]-y_S[i])) / pow(d_SM,3);
		Fx_EM = (G*m_E*m_M*(x_E-x_M[i])) / pow(d_EM,3);
		Fy_EM = (G*m_E*m_M*(y_E-y_M[i])) / pow(d_EM,3);
		// Velocity
		vx_S[i+1] = vx_S[i] + step*(Fx_MS + Fx_ES)/(m_S);
		vy_S[i+1] = vy_S[i] + step*(Fy_MS + Fy_ES)/(m_S);
		vx_M[i+1] = vx_M[i] + step*(Fx_EM - Fx_MS)/(m_M);
		vy_M[i+1] = vy_M[i] + step*(Fy_EM - Fy_MS)/(m_M);
		// Position
		x_S[i+1] = x_S[i] + step*(vx_S[i+1]);
		y_S[i+1] = y_S[i] + step*(vy_S[i+1]);
		x_M[i+1] = x_M[i] + step*(vx_M[i+1]);
		y_M[i+1] = y_M[i] + step*(vy_M[i+1]);
		i++;
		if(d_ES <= r_E){
			break;
		}
		else {
			fprintf(fPointer2, "%lf,%lf,%lf,%lf\n",x_S[i],y_S[i],x_M[i],y_M[i]);
			continue;
		} // If	
	} // FOR

fclose(fPointer2);


} // void main()
