# MY-DIGI-CARD

![Final Product Render 1](Images/FINAL1.png)
![Final Product Render 2](Images/FINAL2.png)
![Final Product Render 3](Images/FINAL3.png)
![Final Product Render 4](Images/FINAL4.png)

## Project Overview
MY-DIGI-CARD is fully custom Keycain type device which can dipaly any kind of text and animation the keychain is paired with the carbiner for th sturdy look and strong hook . The main objective to build this keychain is to igve a cool keychain which can display any animation isntead of the static images that why i use ESP32 super mini to handle this . Instead of requiring a wired computer connection to update the visuals, the onboard C++ firmware generates a dedicated Wi-Fi Captive Portal. This allows users to connect to the keychain’s local network from any standard smartphone, automatically open a web-based upload interface, and seamlessly transfer new animated GIFs directly into the ESP32’s internal LittleFS flash memory partition


## 3D Enclosure and CAD Design
The physical enclosure for this digital keychain requires a custom-designed, 3D-printable case designed in Fusion  360 to ensure all internal hardware is tightly secured without compressing the delicate wiring. The front or the top panel is made with the precision and also  have grooves for thw 2 tactile switches which control brightness and also with the slide switch to power it on or off the main objective to add brightness control is for the battery backup. The top case also have holes for the M@ scre heatset which help to tighly gold the bottom case with the top case the top case hold every electronics which are The display , ESP32 Super Mini , TP4056 and the battery along with the perf baord to secure all the connection and we avoid pcb to Minimize the cost as much as I can do.
![Top Case 1](Images/TOP1.png)
![Top Case 2](Images/TOP2.png)
![Top Case 3](Images/TOP3.png)

The back case also have the screw holes to tight them to the top case also the a circular ring attached to the back case for the carbiner the thicknes is about 3mm not so bulky yet enough sturdy to hold the keychain and absorb some shock as well.

![Bottom Case 1](Images/BOTTOM1.png)
![Bottom Case 2](Images/BOTTOM2.png)
![Bottom Case 3](Images/BOTTOM3.png)

## Circuit Architecture and Wiring
To maximize cost-effectivenes and accessibility, the entire physical circuit is manually assembled on a standard zero-PCB perfboard rather than relying on an expensive custom-printed circuit board. The power delivery system begins with a portable 3.7V LiPo battery wired directly to the input pads of a TP4056 Type-C charging module, which intelligently handles wall charging while supplying a regulated voltage output to the rest of the circuit. To give the user complete control over power consumption, a physical SPDT slide switch is wired in series on the positive voltage line bridging the TP4056 output and the ESP32-C3's 5V input pin, allowing the microcontroller and display to be completely shut down while the battery continues to safely charge in the background. The ESP32-C3 acts as the central processor, rapidly pulling decoded GIF frames from its flash memory and pushing the pixel data to the ILI9341 TFT screen over a high-speed SPI connection. 

![Circuit Schematic](Images/SCHEMATICS.png)



## Bill of Materials (BOM)
| Component | Quantity | Estimated Price (USD) | Source Link |
| :--- | :---: | :--- | :--- |
| **ESP32-C3 SuperMini** | 1 | ~$3.50 | [View on Robu.in](https://robu.in/product/esp32-c3-development-board-esp32-supermini/) |
| **2.0" SPI TFT LCD Color Screen ILI9225** | 1 | ~$7.13 | [View on Robu.in](https://robu.in/product/2-0-inch-spi-tft-lcd-color-screen-module-ili9225-serial-interface-176-x-220/) |
| **TP4056 Charging Module (Type-C)**| 1 | ~$0.50 | [View on Robu.in](https://robu.in/product/tp4056-1a-li-ion-lithium-battery-charging-module-with-current-protection-type-c/) |
| **3.7V LiPo Battery (e.g., 500mAh)** | 1 | ~$4.50 | [View on Robu.in](https://robu.in/product-category/1-cell-lipo-3-7v-4-2v/) |
| **SPDT Slide Switch** | 1 | ~$0.50 | [View on Robu.in](https://robu.in/product-category/slide-switches/) |
| **6x6x5 Tactile Push Buttons** | 2 | ~$0.50 | [View on Robu.in](https://robu.in/product/6x6x5-tactile-push-button-switch/) |
| **Perfboard / Zero PCB** | 1 | ~$1.00 | [View on Robu.in](https://robu.in/product-category/breadboard-and-zero-pcb/) |
| **Misc (Wires, Solder, Header Pins)** | 1 | ~$1.50 | N/A |
| **Carabiner** | 1 | ~$4.71 | [View on Amazon](https://amzn.in/d/09jRIfkX) |
| **Total Estimated Cost:** | | **~$23.84** | |

## Firmware Development and Testing Disclaimer
The software architecture driving this digital keychain is written in C++ utilizing the PlatformIO development environment within Visual Studio Code. The codebase relies heavily on the TFT_eSPI library for optimized hardware-level display driving, the AnimatedGIF library for efficient on-the-fly image decoding, and the ESPAsyncWebServer library to host the reliable local captive portal. It is important to note that the initial firmware architecture and project structure were developed with the assistance of artificial intelligence to establish a robust foundation. Because the codebase currently relies on theoretical pinouts and assumed library behaviors, the firmware will require active physical testing once the perfboard hardware is completely soldered and assembled. Moving forward, all subsequent bug fixes, memory optimizations, and display performance improvements will be directly committed to this repository as the physical prototype is tested and refined.I promise that when the hardware work complete in real life i will make the best firmware and optimised it as much as i can 
