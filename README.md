# Start Docker
docker run -it --rm -v //c/Z/Blaze/docker/ncs-workspace:/workdir/project ncs-3.0.1

# Navigate to work directory
cd /workdir/project/my_blinky/

# Build the project
west build -b nrf52840dk/nrf52840 --build-dir build -p always

# Run unit tests
cd /workdir/project/my_blinky/tests
west build -b native_sim --build-dir build_test
./build_test/tests/zephyr/zephyr.exe