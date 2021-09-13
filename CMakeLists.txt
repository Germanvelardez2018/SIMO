cmake_minimum_required(VERSION 3.19)

# initialize the SDK based on PICO_SDK_PATH
include(pico_sdk_import.cmake)
project(simo)

# initialize the Pico SDK
pico_sdk_init()


add_executable(simo
    core/src/main.c
	core/src/uart.c
	core/src/timer.c
	core/src/comm.c
	core/src/wdt.c
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
	FreeRTOS
	)

	
pico_add_extra_outputs(simo)