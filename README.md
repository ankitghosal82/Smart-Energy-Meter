# ⚡ Smart Energy Meter using ESP32 & Blynk

> 📟 A real-time IoT-based energy monitoring system built with ESP32 and Blynk, featuring live LCD display, mobile app sync, and accurate power usage tracking.  
> 👨‍💻 Designed as a mini project in the 2nd year of B.Tech Electrical Engineering at IIEST Shibpur.

---

## 📌 Overview

This Smart Energy Meter project is an IoT-based solution that allows users to *monitor voltage, current, power, and energy consumption* in real-time using an ESP32 microcontroller. It integrates with the *Blynk IoT App* for wireless visualization and displays data on a *16x2 I2C LCD*.

Whether you're aiming to reduce your electricity bill or track appliance usage, this project is a powerful prototype toward smart power systems.

---

## 🎯 Features

- ✅ Real-time measurement of Voltage, Current, Power & Energy
- 📲 Live updates on *Blynk mobile app*
- 🔌 Auto-zeroing when power is below threshold
- 💡 16x2 LCD for local live monitoring
- 📉 Smooth readings using moving average filters
- ⚙ Energy calculation using time-integrated power

---

## ⚙ Hardware Used

- 🧠 *ESP32* – Microcontroller with WiFi
- ⚡ *ZMPT101B* – Voltage Sensor Module
- 🔌 *ACS712* – Current Sensor Module
- 📟 *16x2 I2C LCD*
- 🔋 Power supply, resistors, breadboard, jumper wires

---

## 💻 Software & Libraries

- Arduino IDE
- Blynk IoT Platform
- BlynkSimpleEsp32.h
- movingAvg.h
- LiquidCrystal_I2C.h

---

---

## 🚀 How It Works

1. ESP32 reads voltage & current from sensors
2. Calculates real power, Vrms, Irms, and energy
3. Displays data on LCD and pushes to Blynk mobile app
4. Uses moving average filters for smooth output
5. Energy accumulates over time (like an electricity meter)

---

## 🔧 Setup Instructions

1. Clone the repo or download as ZIP
2. Open code/main.ino in *Arduino IDE*
3. Install required libraries:
    - Blynk
    - LiquidCrystal_I2C
    - movingAvg
4. Replace BLYNK_AUTH_TOKEN, ssid, and pass with your credentials
5. Upload to ESP32 and power up the system

---

## 📑 Documentation

- [project_report.pdf](./project_report.pdf) — Full technical report
- [presentation.pptx](./presentation.pptx) — Mini project demonstration slides

---

## 👥 Team Members

- *Ankit Ghosal* — Code, Circuit, Integration, Documentation  
- (Add more teammates here if applicable)

---

## 🏁 Future Improvements

- 🔋 Add over-voltage/current protection
- ☁ Integrate cloud data logging
- 📲 App notifications for power spikes
- 🧠 AI-based usage prediction

---

## 🧾 License

This project is open-source and free to use for educational purposes.  
Feel free to fork and enhance it! 🌱

---

⭐ *If you liked this project, give it a star!*  
📬 For queries or collaboration, feel free to open an issue or contact me.