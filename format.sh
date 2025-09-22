#!/bin/bash
find src cmsis FreeRTOS -name "*.c" -o -name "*.h" -o -name "*.s" -o -name "*.S" | xargs clang-format -i
echo "✅ Весь код отформатирован!"