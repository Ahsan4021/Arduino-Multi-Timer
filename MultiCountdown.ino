#include <RTClib.h>
#include <Arduino.h>

RTC_DS3231 rtc;

struct Countdown {
    DateTime startTime;
    DateTime targetTime;
    bool running = false;
    int hours = 0;
    int minutes = 0;
};

Countdown countdowns[4];

void setup() {
    Serial.begin(115200);
    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
        while (1);
    }
    Serial.println("RTC initialized.");
    Serial.println("Enter 'set X HH MM' to set time for timer X (0-3), 'start X' to begin, 'stop X' to stop.");
}

void loop() {
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n');
        input.trim();
        handleSerialInput(input);
    }
    countDownTimers();
}

void handleSerialInput(String input) {
    if (input.startsWith("set")) {
        int id, h, m;
        if (sscanf(input.c_str(), "set %d %d %d", &id, &h, &m) == 3 && id >= 0 && id < 4) {
            countdowns[id].hours = h;
            countdowns[id].minutes = m;
            Serial.print("Timer "); Serial.print(id);
            Serial.print(" set to: ");
            Serial.print(h); Serial.print(" hours ");
            Serial.print(m); Serial.println(" minutes");
        } else {
            Serial.println("Invalid format! Use: set X HH MM (X = 0-3)");
        }
    } else if (input.startsWith("start")) {
        int id;
        if (sscanf(input.c_str(), "start %d", &id) == 1 && id >= 0 && id < 4) {
            startCountdown(id);
        } else {
            Serial.println("Invalid format! Use: start X (X = 0-3)");
        }
    } else if (input.startsWith("stop")) {
        int id;
        if (sscanf(input.c_str(), "stop %d", &id) == 1 && id >= 0 && id < 4) {
            stopCountdown(id);
        } else {
            Serial.println("Invalid format! Use: stop X (X = 0-3)");
        }
    } else {
        Serial.println("Invalid command. Use 'set X HH MM', 'start X', 'stop X'");
    }
}

void countDownTimers() {
    for (int i = 0; i < 4; i++) {
        if (countdowns[i].running) {
            DateTime currentTime = rtc.now();
            long timeRemaining = countdowns[i].targetTime.unixtime() - currentTime.unixtime();
            
            if (timeRemaining > 0) {
                int remainingHours = timeRemaining / 3600;
                int remainingMinutes = (timeRemaining % 3600) / 60;
                int remainingSeconds = timeRemaining % 60;

                Serial.print("Timer "); Serial.print(i);
                Serial.print(" Time left: ");
                Serial.print(remainingHours); Serial.print("h ");
                Serial.print(remainingMinutes); Serial.print("m ");
                Serial.print(remainingSeconds); Serial.println("s");
            } else {
                Serial.print("Timer "); Serial.print(i);
                Serial.println(" finished!");
                countdowns[i].running = false;
            }
        }
    }
}

void startCountdown(int id) {
    if (countdowns[id].hours != 0 || countdowns[id].minutes != 0) {
        countdowns[id].startTime = rtc.now();
        countdowns[id].targetTime = countdowns[id].startTime + TimeSpan(0, countdowns[id].hours, countdowns[id].minutes, 0);
        Serial.print("Timer "); Serial.print(id);
        Serial.println(" started.");
        countdowns[id].running = true;
    } else {
        Serial.println("Set the time first using 'set X HH MM'");
    }
}

void stopCountdown(int id) {
    if (countdowns[id].running) {
        Serial.print("Timer "); Serial.print(id);
        Serial.println(" stopped.");
        countdowns[id].running = false;
        countdowns[id].hours = 0;
        countdowns[id].minutes = 0;
    }
}
