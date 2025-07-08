# Go back to project root and run twister with coverage
cd /workdir/project/ci_cd_base

echo "=== Running twister with coverage (should execute tests automatically) ==="
west twister -T tests/ -p native_sim --coverage

# After twister completes, look for coverage data
echo ""
echo "=== Checking twister-generated coverage ==="
find twister-out -name "*.gcda" -exec ls -la {} \;

echo ""
echo "=== Looking for .gcov files in twister output ==="
find twister-out -name "*.gcov" -exec basename {} \;

# If .gcov files exist, show the firmware coverage
echo ""
echo "=== FIRMWARE COVERAGE FROM TWISTER ==="
find twister-out -name "*.gcov" | while read gcov_file; do
    filename=$(basename "$gcov_file")
    if [[ "$filename" == *"led_driver"* ]] || [[ "$filename" == *"test_led"* ]]; then
        echo "=== Coverage for $filename ==="
        head -15 "$gcov_file"
        echo ""
    fi
done