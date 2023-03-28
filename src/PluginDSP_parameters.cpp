#include "PluginDSP.hpp"

void PluginDSP::initParameter(uint32_t index, Parameter& parameter)
{
    parameter.ranges.min = params.properties[index].ranges.min;
    parameter.ranges.max = params.properties[index].ranges.max;
    parameter.ranges.def = params.properties[index].ranges.def;
    parameter.hints = params.properties[index].hints;
    parameter.name = params.properties[index].name;
    parameter.shortName = params.properties[index].shortName;
    parameter.symbol = params.properties[index].symbol;
    parameter.unit = params.properties[index].unit;
    return;
}

float PluginDSP::getParameterValue(uint32_t index) const
{
    if (index < kParamCount)
        return params.values[index];
    return 0.0;
}

void PluginDSP::setParameterValue(uint32_t index, float value)
{
    d_stdout("DSP %d %s -> %f", index, params.properties[index].name.buffer(), value);
    params.values[index] = value;
    // if (index == foobar) 
        // jdjdjd
}