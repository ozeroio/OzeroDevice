# OzeroDevice

Arduino C++ library (v6.2.1) that abstracts external devices communicating over I2C (primary) and SPI buses.

## Architecture

Class hierarchy (multiple inheritance):

```
RegisterBasedDevice  (abstract: readRegisterBlock / writeRegisterBlock pure virtual)
        |
        +──────────────────────────────┐
                                       |
WiredDevice  (I2C via Wire)    RegisterBasedWiredDevice
        |
        └── EepromBasedWiredDevice  (EEPROM: multi-byte addressing, write cycle delays, retry logic)
```

- `RegisterBasedDevice` — register read/write/configure helpers (`readRegister`, `writeRegister`, `getRegisterBits`, `setRegisterBits`, `clearRegisterBits`, `configureRegisterBits`)
- `WiredDevice` — raw I2C byte read/write; negative return values are Wire error codes (-1 to -5)
- `RegisterBasedWiredDevice` — combines both; `MAX_RETRIES_ON_READING = 0x7f`
- `EepromBasedWiredDevice` — extends `WiredDevice`; configurable `addressSize` (default 2), `writeCycleTime` (default 5000 µs); supports `dynamicAddress()` override for devices like 24x08 that use hardware address bits for memory bank selection

## Error Codes (Wire)

| Code | Meaning |
|------|---------|
| -1 | Data too long for transmit buffer |
| -2 | NACK on address |
| -3 | NACK on data |
| -4 | Other error |
| -5 | Timeout |

## Build System

PlatformIO (`platformio.ini`). Default `src_dir` points to `test/RegisterBasedWiredDevice`.

```bash
# Build and upload to a target
pio run -e uno
pio run -e espressif32
pio run -e esp32-s3-wroom-1-n8r2

# Upload + monitor
pio run -e uno -t upload && pio device monitor -e uno
```

Supported environments: `uno`, `espressif8266`, `espressif32`, `esp32-s3-wroom-1-n8r2`, `esp32-s3-fh4r2`, `esp32-s3-korvo`

ESP variants define `CUSTOM_WIRE_PINS_SUPPORT_ENABLED=1`. To use custom I2C pins on ESP32, call `Wire.begin(sda, scl)` before device use.

## Tests

Tests live in `test/<ClassName>/main.cpp` and are full Arduino sketches (hardware-in-the-loop). To switch the active test, update `src_dir` in `platformio.ini`.

Available test directories:
- `test/RegisterBasedWiredDevice/`
- `test/EepromBasedWiredDevice/`
- `test/EepromBasedWiredDevice24x08/`
- `test/scan/`

## Code Style

Formatted with clang-format (LLVM base). Key rules:
- Tabs for indentation (width 4)
- No column limit
- Pointer alignment: right (`uint8_t *buf`)
- Braces on same line (`AfterFunction: false`, `AfterControlStatement: Never`)
- Run `clang-format -i` on modified files before committing

## Conventions

- Return values: `>= 0` success, `< 0` error code
- Headers use include guards (`#ifndef OZERO_DEVICE_*_H`)
- All classes have `virtual ~ClassName() = default`
- Use `ozero_min` / `ozero_max` macros from `<ozero.h>` instead of `std::min/max` (avoids Arduino framework conflicts)
- `src/` is the `include_dir` — include as `#include <ClassName/ClassName.h>`
