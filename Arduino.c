#include <Arduino.h>
#include <math.h>

// Constants
#define TARGET_PF 0.9       // Target power factor
#define CAPACITOR_KVAR 100  // Capacitor bank kVAR rating

// Function to calculate reactive power
float calculateReactivePower(float apparentPower, float powerFactor) {
    return apparentPower * sqrtf(1 - (powerFactor * powerFactor));
}

// Capacitor switch control pins
#define SWITCH_PIN_1 2     // Digital pin for switching device 1
#define SWITCH_PIN_2 3     // Digital pin for switching device 2
#define SWITCH_PIN_3 4     // Digital pin for switching device 3
#define SWITCH_PIN_4 5     // Digital pin for switching device 4

void setup() {
    pinMode(SWITCH_PIN_1, OUTPUT);
    pinMode(SWITCH_PIN_2, OUTPUT);
    pinMode(SWITCH_PIN_3, OUTPUT);
    pinMode(SWITCH_PIN_4, OUTPUT);
}

void loop() {
    float realPower, apparentPower, powerFactor, reactivePower;
    int requiredCapacitorBanks;

    // Simulated measurements, replace with actual readings from Arduino power measurement interfaces
    realPower = analogRead(A0);    // Assuming A0 pin is connected to real power sensor
    apparentPower = analogRead(A1);    // Assuming A1 pin is connected to apparent power sensor

    // Calculate power factor
    powerFactor = realPower / apparentPower;

    Serial.print("Measured power factor: ");
    Serial.println(powerFactor, 2);

    // Check if correction is required
    if (powerFactor < TARGET_PF) {
        // Calculate required reactive power
        reactivePower = calculateReactivePower(apparentPower, TARGET_PF);

        // Calculate number of capacitor banks required
        requiredCapacitorBanks = (int)(reactivePower / CAPACITOR_KVAR) + 1;

        Serial.print("Correction required. Switching on ");
        Serial.print(requiredCapacitorBanks);
        Serial.println(" capacitor banks.");

        // Activate the switching devices
        digitalWrite(SWITCH_PIN_1, HIGH);
        digitalWrite(SWITCH_PIN_2, HIGH);
        digitalWrite(SWITCH_PIN_3, HIGH);
        digitalWrite(SWITCH_PIN_4, HIGH);
    } else {
        Serial.println("No correction required.");

        // Deactivate the switching devices
        digitalWrite(SWITCH_PIN_1, LOW);
        digitalWrite(SWITCH_PIN_2, LOW);
        digitalWrite(SWITCH_PIN_3, LOW);
        digitalWrite(SWITCH_PIN_4, LOW);
    }

    Serial.println("------------------------------");
    delay(1000);    // Delay between measurements
}
