#include "PluginDSP.hpp"

#include <cstdint>

void PluginDSP::handleMidi(const MidiEvent* event)
{   
    uint8_t b0 = event->data[0]; // status + channel
    uint8_t b1 = event->data[1]; // note
    uint8_t b2 = event->data[2]; // velocity
    d_stdout("MIDI in 0x%x %d %d", b0, b1, b2);
    // if ((b0 != 0x90) || (b0 != 0x80)) {
    //     d_stdout("Blaaa");
    //     continue;
    // }
    if ((b0 == 0xb0) && (b1 == 123)) {
        d_stdout("All notes off");
        synth.panic();
        return;
    }
    if (b0 == 0x90) {
        if (nextGateOff == -1) {
            d_stdout("Gate ON after rest, disable slide, nextGateOff is %d", b1);
            nextGateOff = b1;
            accent = b2 > 100;
            if (accent) {
                d_stdout("Accent!");
            } else {
                accent = false;
            }
            synth.setMidiNote(b1);
            synth.gateOn(accent);
            hat1.gateOn(accent);
        } else {
            d_stdout("Gate ON Slide to %d, nextGateOff is %d", b1, b1);
            nextGateOff = b1;
            synth.slideMidiNote(b1);
        }
        return;
    } else if (b0 == 0x80) {
        if (b1 == nextGateOff) {
            d_stdout("Gate OFF (%d)", b1);
            nextGateOff = -1;
            synth.gateOff();
            hat1.gateOff();
        } else {
            d_stdout("Ignored off for %d != %d", b1, nextGateOff);
        }
        return;
    }
}