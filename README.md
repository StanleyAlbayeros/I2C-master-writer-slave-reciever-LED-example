# I2C master writer slave reciever LED example

This is an I2C example where a master device relays a sequence of three bytes to a slave device. 
The slave device saves the data and "displays" it through a sequence of colors in a single RGB led. 
For ease of use, I also implemented serial communication with a PC and a parser that relays any combination of three of 
the letters "R", "G" and "B" to the master device, saves them into a buffer and uses this information to relay it to 
the slave device.