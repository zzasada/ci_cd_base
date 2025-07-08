#!/bin/bash
echo "=== Building Unit Tests ==="
cd /workdir/project/ci_cd_base/tests
west build -b native_sim --build-dir build_test -p always

if [ $? -eq 0 ]; then
    echo "=== Running Unit Tests ==="
    # Check what the actual executable is called
    ls -la build_test/zephyr/
    echo "Running tests..."
    ./build_test/zephyr/zephyr
else
    echo "Build failed!"
    exit 1
fi
