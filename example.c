/* compile with: gcc -o example example.c -L. -Isrc/ -lmcp23s17 */
#include <stdio.h>
#include <unistd.h>
#include "mcp23s17.h"


int main(void)
{
    const int bus = 0;
    const int chip_select = 0;
    const int hw_addr = 0;

    int mcp23s17_fd = mcp23s17_open(bus, chip_select);

    // config register
    uint8_t ioconfig = BANK_OFF | \
                       INT_MIRROR_OFF | \
                       SEQOP_OFF | \
                       DISSLW_OFF | \
                       HAEN_ON | \
                       ODR_OFF | \
                       INTPOL_LOW;
    mcp23s17_write_reg(ioconfig, IOCON, hw_addr, mcp23s17_fd);

    // I/O direction
    mcp23s17_write_reg(0x00, IODIRA, hw_addr, mcp23s17_fd);
    mcp23s17_write_reg(0xff, IODIRB, hw_addr, mcp23s17_fd);

    // GPIOB pull ups
    mcp23s17_write_reg(0xff, GPPUB, hw_addr, mcp23s17_fd);

    // Write 0xaa to GPIO Port A
    mcp23s17_write_reg(0x00, GPIOA, hw_addr, mcp23s17_fd);
    sleep(1);
    mcp23s17_write_reg(0xaa, GPIOA, hw_addr, mcp23s17_fd);
    sleep(1);
    mcp23s17_write_reg(0x55, GPIOA, hw_addr, mcp23s17_fd);
    sleep(1);
    mcp23s17_write_reg(0x00, GPIOA, hw_addr, mcp23s17_fd);

    // print the input state
    uint8_t input = mcp23s17_read_reg(GPIOB, hw_addr, mcp23s17_fd);
    printf("Inputs: 0x%x\n", input);

    close(mcp23s17_fd);
}
