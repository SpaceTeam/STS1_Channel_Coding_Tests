# Decode/Encode Testing

## Setup

You'll need GNU Radio with GNU Radio Companion (at least version 3.10.11) and [gr-satnogs](https://gitlab.com/librespacefoundation/satnogs/gr-satnogs) (Tested with git master, commit 30ecab7736c032fe5f5651482e7e4d83462ce314).

Also you'll need python3 and pyzmq.

For compiling the test data generator you'll need cmake and a reasonably modern c++ compiler.

## Telemetry (downlink) Decode

GNU Radio reads `/tmp/input.bin`. The data format is "one bit per byte", meaning that each byte can be either 0x00 or 0x01 to represent a 0 or 1 bit.  

For non-convolutionally-coded data there needs to be 512 bit or more of padding after the data packet to flush all buffers.  
For convolutionally coded data an additional 512 bit of padding need to be added in front of the packet.

To run a decode test first start the `zmq_recv.py` python script. It will print the decoded output (packed in the JSON format used by SatNOGS).
Then copy your input file to the location mentioned above.
After that start the flowgraph (the easiest way is to open it in GNU Radio Companion and press play.

Example C++ code can be found in `test_data_generator` that generates valid telemetry (downlink) packets both with and without convolutional coding. 
## License

As some parts of the test data generator are GPLv3 licensed, I made the decision to license the whole repo under GPLv3.  
Should this be an issue for you please contact me - apart from the mentioned parts I can (and am willing to) relicense if a good reason is given.
