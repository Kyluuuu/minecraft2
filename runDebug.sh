
#!/bin/bash

cmake -B build -S . \
    -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"

if [ $? -ne 0 ]; then
    echo "CMake configuration failed"
    exit 1
fi

cmake --build build --config Debug

if [ $? -ne 0 ]; then
    echo "Build failed"
    exit 1
fi

./build/Debug/minecraft.exe
