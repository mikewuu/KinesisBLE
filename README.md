# KinesisBLE

Custom Kinesis Controller with Wireless BLE based on the nRF52 chip.

For i2c / TWI use the i2c branch with v2 (untested) / v1 board files.

If you're brave enough to try this, read the [project](https://hackaday.io/project/161578-wireless-ble-kinesis-advantage-custom-controller) first!

The master branch will always be for the latest build.

V4 (SPI, current) - Lost RGB on the power button in order to free up the TX/RX pins. This board is untested as I just cut the traces and re-soldered on my v3 board, but I used the same pins so the firmware works. If anybody gets one of these made, please let me know how you go.

V3 (SPI) - This board still has RGB power led that shows yellow for charging / green when full. But suffers from battery drain from the serial chip (7mA).

V2 (i2c) - Swapped pins from TX/RX but we're still using i2c (MCP23017) chip which isn't that fast and limits the power savings of the board (5-7mA).  

V1 (i2c) - Uses TX/RX and suffers battery drain.



## Many thanks to

- [Adafruit](https://www.adafruit.com/product/3406) - Awesome documentation, libs and support on the forums. Pointed me in the right direction more than once.
- [afriggeri](https://github.com/afriggeri/kb) - The keyboard firmware borrows heavily from his [Blanck Keyboard](https://medium.com/@friggeri/the-blanck-keyboard-24afe12e81a) firmware. I would never have thought of bit-shifting each column or having 2 byte keycodes for modifier keys.
- [Stapelberg](https://michael.stapelberg.de/posts/2013-03-21-kinesis_custom_controller/) - Michael Stapelberg's custom controller inspired this project. I also tried to route the board myself at first and ended up with a mess of over 50 vias. After copying the routing between connectors, I ended up with a total of 12 vias and a better looking board.
- [Humble Hacker](http://humblehacker.com/blog/20100720/hacking-the-kinesis-contoured-keyboard/) - Thankfully Kinesis hasn't made any changes to the key matrices (only connector types). So I just used the same matrix and connections as David did.
- [PCBgogo](http://www.pcbgogo.com) - Had some confusion with the design files and they helped clear it up. Delivery was also surprisingly fast.
