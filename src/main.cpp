#include <mbed.h>
#include <USBSerial.h>

USBSerial serial;


// reference: http://www.ethernut.de/en/documents/arm-inline-asm.html
// also:      https://azeria-labs.com/downloads/cheatsheetv1.3-1920x1080.png


extern "C" uint32_t add2(uint32_t a, uint32_t b);
extern "C" uint32_t bad_add(uint32_t a, uint32_t b);


int main(void)
{

	uint32_t x = 1;
	uint32_t y = 5;
	uint32_t result;
	while (1) {
		result = x+y;
		serial.printf("c prog - x: %lu   y: %lu   result: %lu\n\r", x, y, result);

		result = add2(x,y);
		serial.printf("assembly - x: %lu   y: %lu   result: %lu\n\r", x, y, result);

		//asm(code : output operand list : input operand list : clobber list);

		asm("mov r0, %[val1]\n\t"
			"add %[out], r0, %[val2]\n\t"
		:[out] "=r" (result)
		:[val1] "r" (x), [val2] "r" (y)
		:"r0"
		);

		asm("mov r0, r0");
		asm("nop");
		serial.printf("assembly2 - x: %lu   y: %lu   result: %lu\n\r", x, y, result);


		result = bad_add(x,y);
		serial.printf("bad asm - x: %lu   y: %lu   result: %lu\n\r", x, y, result);


	}

}