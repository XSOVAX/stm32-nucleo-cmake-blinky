#!/bin/bash
set -e

PROJECT_DIR="$(pwd)"
BUILD_DIR="$PROJECT_DIR/build"

echo "🗑️  Чистим старую сборку..."
rm -rf "$BUILD_DIR"

echo "🏗️  Создаём build..."
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

echo "🔧 Запускаем CMake..."
cmake "$PROJECT_DIR" -DCMAKE_TOOLCHAIN_FILE="$PROJECT_DIR/arm-gcc.cmake"

echo "🔨 Собираем..."
cmake --build .

echo "✅ Готово! Прошивка: $BUILD_DIR/blinky.bin"