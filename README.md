# Wireless Kinesis Advantage BLE (Bluetooth Low Energy)

Firmware for a custom controller to turn the [Kinesis Keyboard](https://www.kinesis-ergo.com/shop/advantage2/) wireless. Written for the Adafruit nRF52 Feather Arduino board, which is built on Nordic's nRF52 SOC bluetooth module. 

**If you're brave enough to try this, read the [project](https://hackaday.io/project/161578-wireless-ble-kinesis-advantage-custom-controller) first!**

## Which Branch?

SPI - master
i2c / TWI - i2c

## Board Versions

V4 (SPI, current) - Lost RGB on the power button in order to free up the TX/RX pins. This board is untested as I just cut the traces and re-soldered on my v3 board, but I used the same pins so the firmware works. 

V3 (SPI) - This board still has RGB power led that shows yellow for charging / green when full. But using the Tx/Rx pins results in some buggy behavior for the LED(s).

V2 (i2c) - Swapped pins from TX/RX but we're still using i2c (MCP23017) chip which isn't that fast and limits the power savings of the board (runs at 5-7mA).  

V1 (i2c) - Uses TX/RX and has high current leak.


## Many thanks to

- [Adafruit](https://www.adafruit.com/product/3406) - Awesome documentation, libs and support on the forums. Pointed me in the right direction more than once.
- [afriggeri](https://github.com/afriggeri/kb) - This keyboard's firmware borrows heavily from his [Blanck Keyboard](https://medium.com/@friggeri/the-blanck-keyboard-24afe12e81a) firmware. I would never have thought of bit-shifting each column or having 2 byte keycodes for modifier keys.
- [Stapelberg](https://michael.stapelberg.de/posts/2013-03-21-kinesis_custom_controller/) - Michael Stapelberg's custom controller inspired this project. I also tried to route the board myself at first and ended up with a mess of probably over 50 vias. After imitating the routing between connectors first, I ended up with less than 10 vias and a happier board.
- [Humble Hacker](http://humblehacker.com/blog/20100720/hacking-the-kinesis-contoured-keyboard/) - Thankfully Kinesis hasn't made any changes to the key matrices (only connector types). So I just used the same matrix and connections as David did.
- [PCBgogo](http://www.pcbgogo.com) - Had some confusion with the design files and they helped clear it up. Delivery was also surprisingly fast.
