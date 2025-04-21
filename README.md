# Arduino-Multi-Timer
This Arduino project allows you to manage **up to four independent countdown timers** using a DS3231 Real-Time Clock (RTC). Each timer can be set, started, and stopped individually through serial commands.

---

## 🧰 Hardware Required

- Arduino Uno, Nano, or compatible board
- DS3231 RTC module
- USB cable for serial communication
- Jumper wires

---

## 🔧 How It Works

- Timers are controlled via the **Serial Monitor** (115200 baud rate).
- Each timer has its own **hours** and **minutes** setting.
- You can run up to 4 timers concurrently.
- Time is accurately tracked using the DS3231 RTC.

---

## ⌨️ Serial Commands

| Command           | Description                                      |
|-------------------|--------------------------------------------------|
| `set X HH MM`     | Set timer `X` (0-3) for `HH` hours and `MM` minutes |
| `start X`         | Start timer `X`                                  |
| `stop X`          | Stop timer `X`                                   |

> ✅ Example:  
> `set 1 0 30` – Sets Timer 1 for 30 minutes  
> `start 1` – Starts Timer 1  
> `stop 1` – Stops Timer 1

---

## 🕒 Output

While a timer is running, you'll see updates in the Serial Monitor like:
Timer 1 Time left: 0h 29m 59s


## 🧠 Notes

- Make sure your RTC is properly wired to the I2C pins.
- The sketch uses the **RTClib** library from Adafruit.

---

## 📦 Libraries Used

Install these from the Arduino Library Manager:

- [RTClib](https://github.com/adafruit/RTClib)

---

## 💡 Future Ideas

- Add buzzer output when timers finish
- Include LCD or OLED display
- Save timer state in EEPROM

---

## 📜 License

MIT License
