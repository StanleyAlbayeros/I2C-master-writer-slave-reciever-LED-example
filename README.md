# I2C master writer slave reciever LED example

This is an I2C example where a master device relays a sequence of three bytes to a slave device. 
The slave device saves the data and "displays" it through a sequence of colors in a single RGB led. 
For ease of use, I also implemented serial communication with a PC and a parser that relays any combination of three of 
the letters "R", "G" and "B" to the master device, saves them into a buffer and uses this information to relay it to 
the slave device. This serial communication can be turned on and off by toggling the boolean "noPC" variable at the start of the Master.ino sketch.
If noPC is TRUE, the color sequence will simply by "RGB". If toggled FALSE, you have to open the serial monitor in the Arduino IDE window that is
connected to the master COM port, select a 9600 baud rate and write any combination of the letters 'R' 'G' 'B' followed by pressing enter into the input box.
There are also several messages that get written into the serial monitor output frame that explain a bit of what's going on.