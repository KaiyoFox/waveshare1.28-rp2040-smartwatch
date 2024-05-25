# RP2040 Smartwatch

The RP2040 Smartwatch is a customizable wearable device powered by the Raspberry Pi RP2040 microcontroller. This README provides information on how to flash the firmware and wire the required components.

## Flashing Instructions

To flash the firmware onto the RP2040 Smartwatch, follow these steps:

1. Hold down the **Reset** button.
2. While holding down **Reset**, also hold down the **Boot** button.
3. Release the **Reset** button.

This will put the device into firmware flash mode, allowing you to upload the desired firmware.

### Firmware Files

- **UF2 File (RP2040):** UF2 file for the RP2040 microcontroller can be found in the [Releases section](https://github.com/KaiyoFox/waveshare1.28-rp2040-smartwatch/releases/latest). This file is used for flashing the RP2040.
- **Seeed.ino File (Seeed Xiao):** This file is used for flashing the Seeed Xiao and can be found in the repository.

## Required Components

### RP2040 Touch LCD 1.28" Display

The RP2040 Smartwatch utilizes the Waveshare RP2040 Touch LCD 1.28" round display. You can find more information and purchase the display from [Waveshare](https://www.waveshare.com/rp2040-touch-lcd-1.28.htm).

### Seeed Xiao BLE nRF52840

The Seeed Xiao BLE nRF52840 is used for its Bluetooth capabilities. You can find more information and purchase the Seeed Xiao BLE from [Seeed Studio](https://www.seeedstudio.com/Seeed-XIAO-BLE-nRF52840-p-5201.html).

## Wiring Diagram

| RP2040 Pin | Seeed Pin / Other |
|------------|-----------|
| GND        | GND       |
| VSYS       | 3V3       |
| Run        | D1        |
| Boot       | D0        |
| GND2       | Connect to GPIO 26 on RP2040 via a 100k resistor and button |
| ADC_AVDD   | Other end of button |
| GPIO 16    | D5        |
| GPIO 17    | D4        |
| GPIO 18    | D3        |
| GPIO 26    | Connect to 100k resistor that is on GND2 |
| GPIO 27    | Unused   |
| GPIO 28    | Haptic Motor +   |

Note: On the button put a capacitor on both ends, Negative on GND2

## Flashing the Seeed Xiao

Please refer to the [Seeed Studio Wiki](https://wiki.seeedstudio.com/XIAO_BLE/) for instructions on flashing the Seeed Xiao.

## Customizing the Firmware

If you wish to modify the firmware to suit your needs, follow these steps:

1. Install firmware for flashing from the Arduino IDE (not needed if flashing UF2).
2. For RP2040 flashing, refer to the [Waveshare Wiki](https://www.waveshare.com/wiki/RP2040-Touch-LCD-1.28) for detailed instructions.

Feel free to customize and experiment with the firmware to create your own unique smartwatch experience!

