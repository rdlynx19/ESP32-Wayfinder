# ESP32-Wayfinder

## Motivation

The primary aim of our project is to address the navigation challenges faced by cyclists and bikers in a safer manner compared to using mobile phones. Recognizing the risks posed by mobile phone usage while riding, we have developed a solution called WAYFINDER, acompact and easy-to-mount navigation device that prioritizes user-friendliness. Our goal is to provide a reliable, cost-effective and efficient navigation tool that enhances the safety of riders and pedestrians alike.

## Solution

WAYFINDER, designed to be a sleek and minimalist navigation device, is powered by an ESP32 microcontroller and features a MAX7219 LED Matrix display for a streamlined and efficient user experience.

The ESP32 microcontroller acts as a receiver for **audio signals** from popular navigation applications such as Google Maps or Waze, which are transmitted via the **onboard Bluetooth** module. These incoming audio signals are then processed using a **fast Fourier transform** (FFT) function to extract the audio frequency information. Once the audio frequency is isolated, the microcontroller uses simple **conditional** statements in the code to trigger corresponding **animations** on an LED Matrix display. For instance, if the detected frequency falls within the range of 200-220 Hz, a '3-2-1 GO' animation could be displayed, synchronizing with the navigation application's cues. This approach enables a visually engaging and intuitive way to convey navigation instructions to the user while minimizing the need for distracting audio cues.

![block-diagram](https://i.imgur.com/qb9Gqkx.png)

## Components and Circuit Diagram

- ESP32-WROOM Microcontroller (2.2 to 3.6V, 600mA)

- MAX 7219 8x8 LED Matrix Display (5V,320mA)

- 5V Li-ion Battery

![](https://i.imgur.com/cqQYnXy.png)


## Conclusion

The key breakthrough in our project is the utilization of voice packs for navigation, which allows our device to be used in both bright sunlight and dark conditions. It is compact, easy to use, and does not require any custom applications as it leverages existing voice packs. This device can be used in various vehicles and can also be optimized for use as a directional indicator when attached to the rear of a bicycle.

## Acknowledgements

This project draws inspiration from the work of Prakrut Kotecha and team on [PixGuide](https://github.com/prakrutk/PixGuide). We express our sincere appreciation and gratitude to Prakrut and team for their invaluable contributions and assistance in during this project.
