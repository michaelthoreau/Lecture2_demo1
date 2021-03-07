#include <mbed.h>
#include <USBSerial.h>

USBSerial serial;

// reference: http://www.ethernut.de/en/documents/arm-inline-asm.html
// also:      https://azeria-labs.com/downloads/cheatsheetv1.3-1920x1080.png

//asm(code : output operand list : input operand list : clobber list);


extern "C" uint32_t add2(uint32_t a, uint32_t b);
extern "C" uint32_t bad_add(uint32_t a, uint32_t b);



uint32_t add2_func(uint32_t a, uint32_t b) {
	return a+b;
}

int main(void)
{

	uint32_t x = 1;
	uint32_t y = 5;
	uint32_t result;
	while (1) {
		
		/* add 2 numbers in c */
		result = add2_func(x,y);
		serial.printf("c prog - x: %lu   y: %lu   result: %lu\n\r", x, y, result);

		/* add 2 numbers in assembly - inline */
		asm(
		"add %[out], %[val1], %[val2]\n\t"
		: [out] "=r" (result)
		: [val1] "r" (x), [val2] "r" (y)
		:
		);
		serial.printf("inline - x: %lu   y: %lu   result: %lu\n\r", x, y, result);

		/* add 2 numbers in assembly - external*/
		result = add2(x,y);
		serial.printf("extern - x: %lu   y: %lu   result: %lu\n\r", x, y, result);

		/* add 2 numbers in assembly - external*/
		result = bad_add(x,y);
		serial.printf("bad_add - x: %lu   y: %lu   result: %lu\n\r", x, y, result);
	}

}