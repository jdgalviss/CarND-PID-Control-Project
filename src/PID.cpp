#include "PID.h"

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  /**
   * Initialize PID coefficients (and errors, if needed)
   */
  p_error = 0.0f;
  i_error = 0.0f;
  d_error = 0.0f;
  Kp = Kp_;
  Ki = Ki_;
  Kd = Kd_;

}

double PID::UpdateSteering(double cte, double cte_prev) {
  /**
   * TODO: Update PID errors based on cte.
   */
  d_error = (-cte-p_error);
  p_error = -cte;
  i_error += p_error;
  
  double steering = Kp*(p_error + Ki*i_error + Kd*d_error);
  TotalError();
  return steering;


}

double PID::TotalError() {
  /**
   * TODO: Calculate and return the total error
   */
  total_error += pow(p_error,2);
  return total_error;  // TODO: Add your total error calc here!
}