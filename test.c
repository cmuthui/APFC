#include <stdio.h>

// Constants
#define TARGET_PF 0.96       // Target power factor
#define CAPACITOR_KVAR 100  // Capacitor bank kVAR rating

// Function to calculate reactive power
float calculateReactivePower(float apparentPower, float powerFactor) {
    return apparentPower * sqrtf(1 - (powerFactor * powerFactor));
}

int main() {
    float realPower, apparentPower, powerFactor, reactivePower;
    int requiredCapacitorBanks;

    while (1) {
        // Simulated measurements, replace with actual measurements from power measurement devices
        printf("Enter real power (kW): ");
        scanf("%f", &realPower);

        printf("Enter apparent power (kVA): ");
        scanf("%f", &apparentPower);

        // Calculate power factor
        powerFactor = realPower / apparentPower;

        printf("Measured power factor: %.2f\n", powerFactor);

        // Check if correction is required
        if (powerFactor < TARGET_PF) {
            // Calculate required reactive power
            reactivePower = calculateReactivePower(apparentPower, TARGET_PF);

            // Calculate number of capacitor banks required
            requiredCapacitorBanks = (int)(reactivePower / CAPACITOR_KVAR) + 1;

            printf("Correction required. Switching on %d capacitor banks.\n", requiredCapacitorBanks);
            // Code to activate the switching devices and connect the capacitor banks goes here
        } else {
            printf("No correction required.\n");
        }

        printf("------------------------------\n");
    }

    return 0;
}
