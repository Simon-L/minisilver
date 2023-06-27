#include "PluginDSP.hpp"

const char* PluginDSP::getLabel() const noexcept {return "eightohat";}
const char* PluginDSP::getDescription() const {return "Simplified analog modeled TR-808 clone";}
const char* PluginDSP::getLicense() const noexcept {return "GPL-3.0-or-later";}
const char* PluginDSP::getMaker() const noexcept {return "Simon L";}
uint32_t PluginDSP::getVersion() const noexcept {return d_version(1, 0, 0);}
int64_t PluginDSP::getUniqueId() const noexcept {return d_cconst('a', 'b', 'c', 'd');}