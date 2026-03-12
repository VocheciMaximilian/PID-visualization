#include "common.h"

float clampValue(float val, float valMin, float valMax){
  if(val<valMin) return valMin;
  if(val>valMax) return valMax;
  return val;
}
