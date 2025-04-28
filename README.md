# ESP32 Button Toggle Project

This project allows you to toggle a button on a website using a real hardware button connected to an ESP32. The built-in LED on the ESP32 indicates two states, providing a visual cue.

## Getting Started

Follow these instructions to set up your ESP32 and get the project running.

### Prerequisites

- ESP32 board
- Arduino IDE or other compatible development environment
- Basic understanding of ESP32 programming and wiring

### Setup Instructions

1. **Modify Credentials**

   Before uploading the code to your ESP32, you need to update the Wi-Fi credentials:

   - Locate the `example-credentials.h` file in the project directory.
   - Edit the file to include your Wi-Fi network's SSID and password.
   - Save the file as `credentials.h`.

2. **Pinout Reference**

   You can find the pinout for the ESP32 board [here](https://lastminuteengineers.com/esp32-pinout-reference/). In this sketch, pin 13 was set as `INPUT_PULLUP` so you need one wire from ground to the button and one from the 13 to the button.

3. **Uploading the Code**

   - Open the main project file in your development environment.
   - Ensure that your ESP32 board is selected, and the correct port is configured.
   - Compile and upload the code to your ESP32.

## Usage

- **Hardware Button**

  Connect your button to the specified pins as per your circuit design. Pressing the button will toggle the website button.

- **ESP32 LED Indicator**

  The built-in LED will indicate the current state:
  - **ON**: State X
  - **OFF**: State Y

## License

This project is open-source and available under the MIT License.
