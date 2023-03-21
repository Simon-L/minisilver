#include "PluginDSP.hpp"

const char* PluginDSP::getLabel() const noexcept {return "minisilver";}
const char* PluginDSP::getDescription() const {return "Simplified analog modeled TB-303 clone";}
const char* PluginDSP::getLicense() const noexcept {return "ISC";}
const char* PluginDSP::getMaker() const noexcept {return "Jean Pierre Cimalando, falkTX, Simon L";}
uint32_t PluginDSP::getVersion() const noexcept {return d_version(1, 0, 0);}
int64_t PluginDSP::getUniqueId() const noexcept {return d_cconst('a', 'b', 'c', 'd');}