#pragma once

#include <vector>
#include <utility>

#include <subsys/MechanismParameters.h>

typedef std::pair <MechanismParameters::MECHANISM_PARAM_TYPE, double> mechParamData;
typedef std::vector<mechParamData> mechParameters;
