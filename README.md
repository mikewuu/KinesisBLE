# KinesisBLE

Custom Kinesis Controller with Wireless BLE based on the nRF52 chip.

## Many thanks to

- [Adafruit](https://www.adafruit.com/product/3406) - Awesome documentation, libs and support on the forums. Pointed me in the right direction more than once.
- [afriggeri](https://github.com/afriggeri/kb) - The keyboard firmware is basically a stripped-down version of his [Blanck Keyboard](https://medium.com/@friggeri/the-blanck-keyboard-24afe12e81a) firmware. I would never have thought of bit-shifting each column or having 2 byte keycodes for modifier keys.
- [Stapelberg](https://michael.stapelberg.de/posts/2013-03-21-kinesis_custom_controller/) - Michael Stapelberg's custom controller inspired this project. I also tried to route the board myself at first and ended up with a mess of like 50 vias. I then copied the routing between connectors and ended up with a total of 10 vias and a way better looking board.
- [Humble Hacker](http://humblehacker.com/blog/20100720/hacking-the-kinesis-contoured-keyboard/) - Thankfully Kinesis hasn't made any changes to the key matrices (only connector types). So I just used the same matrix (transposed) and connections as David did.
