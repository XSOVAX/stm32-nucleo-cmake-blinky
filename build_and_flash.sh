#!/bin/bash
set -e

PROJECT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="$PROJECT_DIR/build"

echo "========================================"
echo "🚀 Сборка и прошивка STM32F103RB (Nucleo)"
echo "========================================"

# Шаг 1: Проверяем зависимости
echo "🔍 Проверяем toolchain..."
if ! command -v arm-none-eabi-gcc &> /dev/null; then
    echo "❌ arm-none-eabi-gcc не найден. Установи:"
    echo "   sudo pacman -S arm-none-eabi-gcc arm-none-eabi-newlib"
    exit 1
fi

if ! command -v st-flash &> /dev/null; then
    echo "❌ st-flash не найден. Установи:"
    echo "   sudo pacman -S stlink"
    exit 1
fi

# Шаг 2: Пересобираем проект
echo "🗑️  Чистим старую сборку..."
rm -rf "$BUILD_DIR"

echo "🏗️  Создаём build..."
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

echo "🔧 Запускаем CMake..."
cmake "$PROJECT_DIR" -DCMAKE_TOOLCHAIN_FILE="$PROJECT_DIR/arm-gcc.cmake"

echo "🔨 Собираем прошивку..."
cmake --build . --target stm32f103rb_cmsis_blinky.bin
echo "🔨 bin файл создан..."
cmake --build . --target stm32f103rb_cmsis_blinky.hex
echo "🔨 hex файл создан..."

# Шаг 3: Прошиваем
echo "🔌 Подключаемся к STM32..."
if st-info --probe &> /dev/null; then
    echo "✅ ST-Link обнаружен"
else
    echo "⚠️  ST-Link не обнаружен. Проверь подключение платы."
    exit 1
fi

echo "💾 Прошиваем контроллер..."
st-flash write stm32f103rb_cmsis_blinky.bin 0x08000000

echo "📏 Показываем размер прошивки..."
arm-none-eabi-size stm32f103rb_cmsis_blinky.elf

echo "🎉 Готово! Светодиод должен мигать на PA5."