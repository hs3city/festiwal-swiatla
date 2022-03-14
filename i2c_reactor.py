#  Raspberry Pi Master for Arduino Slave
#  i2c_master_pi.py
#  Connects to Arduino via I2C
  
#  DroneBot Workshop 2019
#  https://dronebotworkshop.com

from smbus import SMBus
import time

addrs = [0x1, 0x9] # bus address
bus = SMBus(1) # indicates /dev/ic2-1

numb = 1

b = 0
ledstate = 0

print ("Enter 1 for ON or 0 for OFF")
while numb == 1:
	time.sleep(0.1)

	if ledstate == 1:
		for addr in addrs:
			bus.write_byte(addr, 0x1) # switch it on
                        b = bus.read_byte(addr)
                        print(b)
	elif ledstate == 0:
		for addr in addrs:
			bus.write_byte(addr, 0x0) # switch it on
                        b = bus.read_byte(addr)
                        print(b)
	else:
		numb = 0

	if b > 0:
		ledstate = 1
	else:
		ledstate = 0
