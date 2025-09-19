
cmake_minimum_required(VERSION 3.20)

project(stm32f103rb_cmsis_blinky C ASM)

# Явно указываем компиляторы — на случай, если find_program не сработал
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
find_program(CMAKE_SIZE_UTIL arm-none-eabi-size)

# Определяем макрос устройства, если задан
if(STM32F103xB)
    add_definitions(-DSTM32F103xB)
endif()
if(NOT CMAKE_OBJCOPY)
    message(FATAL_ERROR "arm-none-eabi-objcopy not found!")
endif()

if(NOT CMAKE_SIZE_UTIL)
    message(FATAL_ERROR "arm-none-eabi-size not found!")
endif()



# Явно указываем исходники
file(GLOB_RECURSE SOURCES
    "FreeRTOS/*.c"
    "FreeRTOS/portable/GCC/ARM_CM3/port.c"
    "FreeRTOS/portable/MemMang/heap_4.c"
    "src/*.c"
    "cmsis/startup_stm32f103xb.s"
    "cmsis/system_stm32f1xx.c"
)

# Указываем пути для заголовков
include_directories(
    FreeRTOS
    FreeRTOS/include
    FreeRTOS/portable/GCC/ARM_CM3/
    inc
    cmsis
    ld
)

# Создаём исполняемый файл .elf
add_executable(${PROJECT_NAME}.elf ${SOURCES})

# Указываем линкер-скрипт
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/ld/STM32F103RB_FLASH.ld)

target_compile_options(${PROJECT_NAME}.elf PRIVATE
    -mcpu=cortex-m3
    -mthumb
    -Wall
    -O1              
    -g
    -ffreestanding
)
# Флаги линковки
target_link_options(${PROJECT_NAME}.elf PRIVATE
    -T${LINKER_SCRIPT}
    -nostdlib
    -nostartfiles 
    -lgcc           
    -Wl,--gc-sections
    -Wl,-Map=${PROJECT_NAME}.map
)

# Генерация .hex
add_custom_target(${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
    DEPENDS ${PROJECT_NAME}.elf
    COMMENT "Generating HEX file"
)

# Генерация .bin
add_custom_target(${PROJECT_NAME}.bin
    COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
    DEPENDS ${PROJECT_NAME}.elf
    COMMENT "Generating BIN file"
)


# Цель: прошивка через OpenOCD
#add_custom_target(flash
#    COMMAND openocd
#        -f interface/stlink.cfg
#        -f target/stm32f1x.cfg
#        -c "init"
#        -c "reset halt"
#        -c "flash write_image erase ${PROJECT_NAME}.hex"
#        -c "reset run"
#        -c "shutdown"
#    DEPENDS ${PROJECT_NAME}.hex
#    COMMENT "Flashing STM32 via ST-Link"
#)

# Цель: прошивка. Будем использовать st-flash — легковесный, быстрый, работает "из коробки"
add_custom_target(flash
    COMMAND st-flash write ${PROJECT_NAME}.bin 0x08000000
    DEPENDS ${PROJECT_NAME}.bin
    COMMENT "Flashing STM32 via st-flash"
)

# Цель: показать размер прошивки
add_custom_target(size
    COMMAND ${CMAKE_SIZE_UTIL} ${PROJECT_NAME}.elf
    DEPENDS ${PROJECT_NAME}.elf
    COMMENT "Showing firmware size"
)
