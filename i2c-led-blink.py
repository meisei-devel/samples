import smbus
import time

count = 0

i2c = smbus.SMBus(1)
addr = 0x60

i2c.write_byte_data(addr, 0x00, 0x00) #ALL LED INIT

i2c.write_byte_data(addr, 0x17, 0xff) #LED4 ON

while True:
	if count % 2 == 0:
		i2c.write_byte_data(addr, 0x0f, 0x22) #LED4-R Level 0x22
	else:
		i2c.write_byte_data(addr, 0x0f, 0x00) #LED4-R Level 0x00(Off)

	time.sleep(1)

	count = count + 1
	print(count)

	if count >= 10:
		break
