# Decode/Encode Testing

## Setup

You'll need GNU Radio with GNU Radio Companion (at least version 3.10.11) and [gr-satellites](https://github.com/daniestevez/gr-satellites) (Tested with version 5.6.0).

For compiling the test data generator you'll need cmake and a reasonably modern c++ compiler.

## Telemetry (downlink) Decode

GNU Radio reads `/tmp/input.bin`. The data format is "one bit per byte", meaning that each byte can be either 0x00 or 0x01 to represent a 0 or 1 bit.  

For non-convolutionally-coded data there needs to be 512 bit or more of padding after the data packet to flush all buffers.  
For convolutionally coded data an additional 512 bit of padding need to be added in front of the packet.

First copy your input file to the location mentioned above.  
After that start the flowgraph (the easiest way is to open it in GNU Radio Companion and press play.  
You'll find the decoded output both in the log of GNU Radio and in `/tmp/output.bin`.  

Example C++ code can be found in `test_data_generator` that generates valid telemetry (downlink) packets both with and without convolutional coding.  
Files starting with `tm` are intended to simulate telemetry data from the cubesat, files starting with `tc` are intended to be used to send test telecommand data to the cubesat.

## In case you want to test real hardware

Use the flowgraph prefixed with "sdr". It's not perfect - the FSK demodulator could be quite a bit better - but it works.

The `tc` flowgraph needs quite a lot (at least ~400 Byte) of trailing data to flush the buffer.  
The test data generator automatically accounts for this.

## License

As some parts of the test data generator are GPLv3 licensed, I made the decision to license the whole repo under GPLv3.  
Should this be an issue for you please contact me - apart from the mentioned parts I can (and am willing to) relicense if a good reason is given.
