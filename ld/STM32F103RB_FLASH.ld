/* linker/STM32F103RB_FLASH.ld */
/* Скрипт линковки для STM32F103RB: 128K FLASH, 20K RAM */

ENTRY(Reset_Handler)

_estack = 0x20005000;    /* Вершина стека — конец RAM (0x20000000 + 20K) */
_Min_Stack_Size = 0x400; /* Минимальный размер стека — 1KB */
_Min_Heap_Size = 0x2000; /* Минимальный размер кучи  — 8KB для FreeRTOS */

MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 128K
    RAM (xrw)  : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
    /* Код и вектор прерываний — в начале FLASH */
    .text :
    {
        KEEP(*(.isr_vector))     /* Вектор прерываний — ДОЛЖЕН быть первым! */
        *(.text*)                /* Код */
        *(.rodata*)              /* Константы */
        _etext = .;              /* Конец секции .text */
    } >FLASH

    /* Инициализированные данные — копируются из FLASH в RAM при старте */
    .data : AT (_etext)
    {
        _sdata = .;
        *(.data*)
        _edata = .;
    } >RAM

    _sidata = LOADADDR(.data);
    /* Неинициализированные данные — в RAM */
    .bss :
    {
        _sbss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } >RAM

    /* Стек — в RAM, выравниваем по 8 байт */
    .stack ALIGN(8) (NOLOAD):
    {
        _stack_start = .;
        . = . + _Min_Stack_Size;
        _stack_end = .;
    } >RAM
    
    /* Куча — после стека и bss 
    .heap ALIGN(8) (NOLOAD):
    {
        __heap_start = .;
        . = . + _Min_Heap_Size;      
        __heap_end = .;
    } >RAM */
}
