# Morse Code Translator

This repository contains an Arduino sketch (`Morse_Code_Translate.ino`) for translating button presses into Morse code, and a Python script (`decode.py`) for decoding Morse code received from the Arduino. The decoded messages are then linked to ThingsBoard, an open-source IoT platform.

## Morse_Code_Translate.ino

### Description

This Arduino sketch uses a button to input Morse code. The code translates button presses into Morse code dots (.), dashes (-), and spaces (/). It sends the Morse code to a Raspberry Pi via the serial connection, and the decoded messages are linked to ThingsBoard for IoT integration.

### Setup

1. Connect a PIR motion sensor to pin 2, a buzzer to pin D3, and a button to pin D4 on your Arduino.
2. Upload the sketch to your Arduino board.

### Usage

1. Press and hold the button to input Morse code.
2. The buzzer will sound to represent dots and dashes.
3. Release the button to send the Morse code to the Raspberry Pi and, subsequently, to ThingsBoard.

## decode.py

### Description

This Python script receives Morse code from the Arduino through the serial connection. It decodes the Morse code into alphanumeric characters and prints the result. The decrypted messages are then linked to ThingsBoard for further IoT processing.

### Setup

1. Connect your Arduino to the Raspberry Pi.
2. Update the serial port in the script (`ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)`) to match your setup.

### Usage

1. Run the script on the Raspberry Pi.
2. The script will continuously receive and decode Morse code from the Arduino, printing the encrypted and decrypted messages, and linking them to ThingsBoard.

## Important Notes

- Adjust the `baseTime` and `tolerance` variables in the Arduino sketch for better Morse code interpretation based on your setup.
- Ensure proper serial port configuration in the Python script to match your environment.
- Ensure ThingsBoard is properly set up and configured for receiving and processing the decoded messages.

Feel free to customise and extend this code for your specific needs.
