## Development notes

In this project a regular digital camera was turned into a remote controllable one using arduino and an infrared remote.

The main components in this project are:
-the camera (Olympus u760)
-arduino nano
-infrared receiver module TSOP1738
-generic infrared remote from an audio pre-amplifier (MaiA Pre-amp)
-lithium-ion cell 18650 3.7 V and a holder for it

## Workflow:

The first thing was to ensure all the main components are in working order. The camera's battery had died over the years and unfortunately could not be used anymore.
So to confirm that the camera works, wires needed to be connected to the battery contacts of the camera and voltage applied to them. I used a workbench power supply to provide 4.0 volts to the camera and ensure proper function.

As a new power source was needed for the camera, I chose to use a simple 18650 lithium-ion cell I had heaps of laying around from other projects. The battery was charged full with a separate Li-Ion charger and was confirmed to hold charge well by measuring its voltage with a multimeter during the construction of the project.
The battery provides power not only for the camera, but for all the other components as well (excluding the remote).

Human eye can't sense the infrared light from the remote, but a digital camera can. So I just pointed it at my mobile phone's camera to confirm that the IR led indeed was lit.

The next thing was to establish a connection between arduino and the infrared transmitter. I started by wiring the TSOP1738 to the arduino [image here].
The sensor datasheet [link here] includes a wiring example, which I replicated on my breadboard:
*-22 uF capacitor between 5 V and GND 
*-sensor Vs to 5 V via a 100 ohm resistor
*-GND to GND
*-sensor signal out pin to arduino digital pin 2

Before I started reading the sensor output with arduino, I confirmed that the sensor was outputting signal, which actually was very clear [image here]. The remote control has five buttons, all of which were tested with the oscilloscope.
The waveforms were saved and decoded with pencil and paper. The information turned out to be manchester-encoded [link here], which is a common encoding protocol in infrared communication.

It was time to reverse-engineer the camera. For that, the camera needed to be partly dissassembled [images here]. The shutter button controls both the focus and the shutter.  The goal was to control shutter and focus remotely
