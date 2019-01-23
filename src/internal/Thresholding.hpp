#ifndef THRESHOLDING_HPP
#define THRESHOLDING_HPP

#include <math.h>

class Thresholding
{
public:
  Thresholding();
  Thresholding(const double &amplitude,const double &threshold);
  ~Thresholding();
  
  double getSignalThreshold(const double &signal);
  bool   setThreshold(const double &amplitude,const double &threshold);
private:
  double m_amplitude;
  double m_threshold;   

};

#endif // THRESHOLDING_HPP