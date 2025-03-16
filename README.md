# 🎮 Arduino Joystick LED Controller

This project is a simple LED controller using an **Arduino** and a **joystick**. By moving the joystick in different directions, you can control the brightness of four LEDs – each one corresponding to a direction (up, down, left, right).

## 🔧 How It Works

The joystick is connected to two analog pins (`A0` for X-axis and `A1` for Y-axis) and a push button (`D8`). Based on analog input values, the brightness of four LEDs is controlled using `analogWrite()`:

- 🔼 **Up** – `pin 5`
- 🔽 **Down** – `pin 10`
- ◀️ **Left** – `pin 6`
- ▶️ **Right** – `pin 3`

If the joystick is **pressed down**, all LEDs will light up to full brightness.  
Otherwise, moving the joystick in any direction will control the brightness of the corresponding LED proportionally.

## 🖼️ Circuit Photo

<!-- INSERT PHOTO BELOW -->
![Circuit Photo](https://github.com/user-attachments/assets/f82d97e4-78ec-4fb8-9266-42af7a878bbe)


## 🎥 Project Demo

<!-- INSERT VIDEO BELOW -->
[Watch the Demo](insert_video_link_here)

## ⚙️ Adjusting for Your Joystick

If the project doesn't work **perfectly on your hardware** (e.g. some LEDs light up even when the joystick is in the center), it's likely due to slight wear or calibration differences in your joystick module.

You can fix this by **adjusting the threshold values** in the `brightness()` function:

```cpp
if (vertical <= 520 && vertical > 500) { ... }
