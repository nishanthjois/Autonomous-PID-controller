#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {

	p_gain  = Kp;
	i_gain = Ki;
	d_gain = Kd;

	// p_error = 0.0;
	// i_error = 0.0;
	// d_error = 0.0;
}

void PID::UpdateError(double cte) {

	d_error = cte - p_error;
	i_error+=cte;
	p_error=cte;
}

double PID::TotalError() {
	return -1*(p_gain*p_error+d_gain*d_error+i_gain*i_error);

}

