#include "main.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#define LED_GPIO_RCC RCC_GPIOA
#define LED_GPIO_PORT GPIOA
#define LED_GPIO_PIN GPIO1

int main(void) {
	// set debug to swd
	gpio_primary_remap(AFIO_MAPR_SWJ_CFG_JTAG_OFF_SW_ON, 0);

	// setup for 72M core with 48M usb clock
	rcc_clock_setup_in_hse_8mhz_out_72mhz();
	rcc_set_usbpre(RCC_CFGR_USBPRE_PLL_CLK_DIV1_5);

	// set up peripheral clock and set gpio for opendrain
	rcc_periph_clock_enable(LED_GPIO_RCC);
	gpio_set_mode(LED_GPIO_PORT, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_OPENDRAIN, LED_GPIO_PIN);

	// loop forever
	while (1) {
		// toggle the led pin and wait a short time
		gpio_toggle(LED_GPIO_PORT, LED_GPIO_PIN);
		for (volatile int i=0; i<1000000; i++);
	}

	return 0;
}
