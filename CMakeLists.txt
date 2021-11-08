cmake_minimum_required(VERSION 3.16)

# initialize the SDK based on PICO_SDK_PATH
include(pico_sdk_import.cmake)
project(simo)

# initialize the Pico SDK
pico_sdk_init()


add_executable(simo
    core/src/main.c
	core/src/timer.c
	core/src/wdt.c
	core/src/simo/uart.c
	core/src/simo/i2c.c
	core/src/simo/spi.c
	core/src/simo/device.c
	core/src/simo/sim_device.c
	core/src/simo/AT45DB041E.c
	core/src/simo/_AT45DB041E.c  #nueva version
	core/src/simo/memory.c
	core/src/simo/memory_store.c
	core/src/simo/debug_interface.c
)

FILE(GLOB FreeRTOS_src FreeRTOS-Kernel/*.c)

add_library( FreeRTOS STATIC
	${FreeRTOS_src}
	FreeRTOS-Kernel/portable/GCC/ARM_CM0/port.c
	FreeRTOS-Kernel/portable/MemMang/heap_4.c
)

target_include_directories( FreeRTOS PUBLIC
		FreeRTOS-Kernel/include
		core/include/
		FreeRTOS-Kernel/portable/GCC/ARM_CM0
	)

target_link_libraries( simo
	pico_stdlib 
	hardware_gpio
	hardware_uart
	hardware_i2c
	hardware_spi
	FreeRTOS
	)

	
pico_add_extra_outputs(simo)