#include "PID.h"

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  //Initializing PID coefficients 
  PID::Kp = Kp_;
  PID::Ki = Ki_;
  PID::Kd = Kd_;
  PID::prev_cte = 0;

}

void PID::UpdateError(double cte) {
  //Updating errors based on CTE
  PID::p_error = cte;
  PID::i_error += cte;
  PID::d_error = cte - PID::prev_cte;
  PID::prev_cte = cte;

}

double PID::TotalError() {
  
  return (PID::p_error * PID::Kp) + (PID::i_error * PID::Ki) + (PID::d_error * PID::Kd);
}

double PID::OnlyProportional()
{
  return (PID::p_error * PID::Kp);
}

double PID::ProportionalAndDerivative()
{
  return (PID::p_error * PID::Kp) + (PID::d_error * PID::Kd);
}

double PID::run(double p[])
{
  return (p[0] + p[1] + p[2])/(double)3;
}

void PID::twiddle()
{
  double p[3] = {0.27, 0.001, 3.0};
  double dp[3] = {0.05, 0.001, 0.05};
  double best_error = 1;
  
  if((dp[0] + dp[1] + dp[2]) > 0.01)
  {
    
    for(int i=0;i<3;i++)
    {
      bool best_error_found = false;
      std::cout << "Adding: " << dp[i] << std::endl;
      p[i] += dp[i];
      double error = PID::run(p);
      
      if(error < best_error)
      {
        best_error = error;
        dp[i] *= 1.1;
        best_error_found = true;
      }
      else
      {
        p[i] -= 2* dp[i];
        error = PID::run(p);
        if(error < best_error)
        {
          best_error = error;
          dp[i] *= 1.1;
          best_error_found = true;
        }
      }
      if(!best_error_found)
      {
        p[i] += dp[i];
        dp[i] *= 0.9;
      }
    }
  }
  std::cout << "DP Values: " << dp[0] << " " << dp[1] << " " << dp[2] << std::endl;
  std::cout << "After Twiddle: " << p[0] << " "  << p[1] << " " << p[2] << std::endl;
  PID::Kp = p[0];
  PID::Ki = p[1];
  PID::Kd = p[2];
}
