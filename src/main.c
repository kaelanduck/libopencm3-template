#include "main.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>

#include <FreeRTOS.h>
#include <task.h>

void setup_task(void *arg) {
	(void)arg;

	// startup some clocks
	rcc_periph_clock_enable(RCC_GPIOA);

	// flash an led
	gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_OPENDRAIN, GPIO1);
	while (1) { gpio_toggle(GPIOA, GPIO1); vTaskDelay(500); }

	// wait for some initialisation sequence
	//vTaskDelay(50);

	// force usb reenumerate
	//gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO12);
	//gpio_clear(GPIOA, GPIO12);
	//vTaskDelay(500);

	// create all main tasks
	//xTaskCreate(some_task_func, "some task", 512, NULL, 2, &handle);
	//xTaskCreate(some_other_task, "another task", 512, NULL, 1, &handle2);

	// delete the setup task
	vTaskDelete(NULL);
}

int main(void) {
	// set debug to swd
	gpio_primary_remap(AFIO_MAPR_SWJ_CFG_JTAG_OFF_SW_ON, 0);

	// setup for 72M core with 48M usb clock
	rcc_clock_setup_in_hse_8mhz_out_72mhz();
	rcc_set_usbpre(RCC_CFGR_USBPRE_PLL_CLK_DIV1_5);

	// create the setup task at max priority
	xTaskCreate(setup_task, "setup_task", 128, NULL, configMAX_PRIORITIES-1, NULL);

	// start the scheduler
	vTaskStartScheduler();

	// never get here
	return 0;
}

// FreeRTOS handler entrypoints, defined in freertos/port.c
void vPortSVCHandler(void);
void xPortPendSVHandler(void);
void xPortSysTickHandler(void);

// interrupt vectors needed by FreeRTOS
void sys_tick_handler(void) {xPortSysTickHandler();}
void sv_call_handler(void) {vPortSVCHandler();}
void pend_sv_handler(void) {xPortPendSVHandler();}
