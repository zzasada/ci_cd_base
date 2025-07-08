# Start Docker
docker run -it --rm -v //c/Z/Blaze/docker/ncs-workspace:/workdir/project ncs-3.0.1

# Navigate to work directory
cd /workdir/project/ci_cd_base/

# Build the project
west build -b nrf52840dk/nrf52840 --build-dir build -p always

# Run unit tests
cd /workdir/project/ci_cd_base/tests
west build -b native_sim --build-dir build_test
./build_test/tests/zephyr/zephyr.exe

# Coverage
cd /workdir/project/ci_cd_base/
west twister -T tests/ -p native_sim --coverage

./filter_coverage.sh

## 🚀 CI/CD Pipeline

This project includes a comprehensive CI/CD pipeline with GitHub Actions:

### 📋 Workflows

- **CI (`ci.yml`)**: Runs on every push and PR
  - ✅ Unit tests with native simulator
  - 📊 Code coverage analysis
  - 🔧 Multi-target firmware builds
  - 📦 Artifact uploads

- **Docker Build (`docker-build.yml`)**: Maintains Docker images
  - 🐳 Builds NCS development environment
  - 📤 Pushes to GitHub Container Registry
  - 💾 Caches for faster builds

- **Security (`codeql.yml`)**: Code security analysis
  - 🔒 Static security analysis
  - 🐛 Quality checks
  - 📈 Security reporting

### 🎯 Quality Gates

- ✅ All unit tests must pass
- 📊 Coverage reports generated
- 🔒 Security analysis passed
- 🔧 Firmware builds successfully

### 📦 Artifacts

Each successful build generates:
- 💾 **Firmware binaries** (`.hex`, `.elf`, `.bin`)
- 📊 **Coverage reports** (HTML + JSON)
- 🧪 **Test results** (XML format)

### 🏷️ Releases

Automatic releases are created when:
- Push to `main` branch
- Commit message contains `[release]`
- All tests pass

### 🔧 Local Development

```bash
# Run the same tests locally
docker run --rm -v $(pwd):/workdir/project ncs-3.0.1 \
  bash -c "cd /workdir/project/tests && west build -b native_sim --build-dir build_test && ./build_test/tests/zephyr/zephyr.exe"

# Generate coverage locally
docker run --rm -v $(pwd):/workdir/project ncs-3.0.1 \
  bash -c "cd /workdir/project && west twister -T tests/ -p native_sim --coverage"
```