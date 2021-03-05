#include <mbed.h>
#include <USBSerial.h>

USBSerial serial;

// reference: http://www.ethernut.de/en/documents/arm-inline-asm.html
// also:      https://azeria-labs.com/downloads/cheatsheetv1.3-1920x1080.png

//asm(code : output operand list : input operand list : clobber list);


int main(void)
{
  while (1) {
    uint32_t x = 1;
    uint32_t y = 5;
    
    // swap x and y
    // asm(  "mov r0, %[value]\n\t"
    //       "mov %[result], r0"
    // : [result] "=r" (y) 
    // : [value] "r" (x): "r0");

    // add 1 to x until it is equal to y
    asm(  "mov r0, %[value]\n\t"
          "mov r1, %[threshold]\n\t"
          "loop:\n\t"
          "cmp r0, r1\n\t"
          "beq end\n\t"
          "add r0, #1\n\t"
          "b loop\n\t"
          "end:\n\t"
    :
    : [threshold] "r" (y), [value] "r" (x)
    : "r0", "r1", "cc");


    serial.printf("x: %d  y: %d\n", x, y);
  }
  
}