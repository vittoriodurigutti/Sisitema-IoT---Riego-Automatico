// ----------------------------------------------------------------
// Prototipo:
// En proceso, evaluando la estructura general medinte el uso de FreeRTOS.
// Asi mismo estamos reevaluando cada bloque de codigo de cada sensor, 
// para compatibilizar, y sea choerente con la funcion FreeRTOS propuesta
// ----------------------------------------------------------------

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <WiFi.h>
#include "HS1.2Sensor.h"  // Sensor de humedad de suelo
#include "LDRSensor.h"    // Sensor LDR
#include "PIRSensor.h"    // Sensor PIR
#include "AHT10Sensor.h"  // Sensor de temperatura y humedad
#include "BH1750Sensor.h"  // Sensor de luz
#include "HC_SR04.h"      // Sensor de nivel de agua (ultrasonido)

// Definición de pines
#define SOIL_SENSOR_SIGNAL_PIN 34 // Pin del sensor de humedad de suelo
#define LDR_SIGNAL_PIN 35         // Pin del LDR
#define PIR_SIGNAL_PIN 32         // Pin del sensor PIR
#define AHT10_I2C_ADDRESS 0x38    // Dirección I2C del AHT10
#define BH1750_I2C_ADDRESS 0x23    // Dirección I2C del BH1750
#define HC_SR04_TRIGGER_PIN 26     // Pin Trigger del sensor ultrasónico
#define HC_SR04_ECHO_PIN 27        // Pin Echo del sensor ultrasónico
#define BOMB_PIN 23                // Pin para activar la bomba

// Instancias de sensores
HS12Sensor soilSensor(SOIL_SENSOR_SIGNAL_PIN, 25, 26, 27, 14); // Multiplexor
LDRSensor ldrSensor(LDR_SIGNAL_PIN);
PIRSensor pirSensor(PIR_SIGNAL_PIN);
AHT10Sensor aht10Sensor(AHT10_I2C_ADDRESS);
BH1750Sensor bh1750Sensor(BH1750_I2C_ADDRESS);
HC_SR04 hc_sr04(HC_SR04_TRIGGER_PIN, HC_SR04_ECHO_PIN);

// Variables globales para el estado de sensores
int soilMoisture;
float temperature;
float humidity;
float lightLevel;
bool motionDetected;
float waterLevel;

// Variables para condiciones de riego
const int HUMIDITY_THRESHOLD = 800; // Umbral de humedad del suelo
const float WATER_LEVEL_THRESHOLD = 10.0; // Umbral de nivel de agua

// Tarea de inicialización
void taskInitialization(void *pvParameters) {
    Serial.begin(9600);
    delay(2000); // Espera un poco para la inicialización
    soilSensor.begin();
    ldrSensor.begin();
    pirSensor.begin();
    aht10Sensor.begin();
    bh1750Sensor.begin();
    hc_sr04.begin();

    Serial.println("Sensores inicializados.");
    vTaskDelete(NULL); // Elimina esta tarea, no es necesaria después de inicializar
}

// Tarea de revisión de sensores críticos
void taskCriticalSensorReview(void *pvParameters) {
    while (true) {
        // Leer sensor de humedad del suelo
        soilMoisture = soilSensor.readSensor();
        Serial.print("Humedad Suelo: ");
        Serial.println(soilMoisture);

        // Leer sensor de nivel de agua
        waterLevel = hc_sr04.readDistance();
        Serial.print("Nivel de Agua: ");
        Serial.println(waterLevel);

        // Activar bomba si es necesario
        if (soilMoisture < HUMIDITY_THRESHOLD && waterLevel > WATER_LEVEL_THRESHOLD) {
            digitalWrite(BOMB_PIN, HIGH); // Encender bomba
            Serial.println("Bomba activada.");
        } else {
            digitalWrite(BOMB_PIN, LOW); // Apagar bomba
            Serial.println("Bomba desactivada.");
        }

        vTaskDelay(5000 / portTICK_PERIOD_MS); // Espera 5 segundos
    }
}

// Tarea de revisión de sensores de apoyo
void taskSupportingSensorReview(void *pvParameters) {
    while (true) {
        // Leer sensores ambientales
        aht10Sensor.readTemperatureHumidity(&temperature, &humidity);
        Serial.print("Temperatura: ");
        Serial.print(temperature);
        Serial.print(" °C, Humedad: ");
        Serial.println(humidity);

        lightLevel = bh1750Sensor.readLightLevel();
        Serial.print("Nivel de Luz: ");
        Serial.println(lightLevel);

        // Ajustar riego según condiciones climáticas
        if (humidity > 70) {
            Serial.println("Condiciones adecuadas, ajuste de riego necesario.");
        } else {
            Serial.println("Condiciones secas, ajuste de riego activo.");
        }

        vTaskDelay(5000 / portTICK_PERIOD_MS); // Espera 5 segundos
    }
}

// Tarea de revisión de sensores de monitoreo
void taskMonitoringSensorReview(void *pvParameters) {
    while (true) {
        // Leer el sensor de movimiento
        motionDetected = pirSensor.isMotionDetected();
        Serial.print("Movimiento detectado: ");
        Serial.println(motionDetected ? "Sí" : "No");

        // Leer LDR
        lightLevel = ldrSensor.readLightLevel();
        Serial.print("Nivel de Luz (LDR): ");
        Serial.println(lightLevel);

        vTaskDelay(5000 / portTICK_PERIOD_MS); // Espera 5 segundos
    }
}

// Tarea de conexión y envío de datos
void taskConnectionAndData(void *pvParameters) {
    // Aquí puedes agregar tu código para conectar a WiFi y enviar datos
    WiFi.begin("SSID", "PASSWORD"); // Reemplaza con tus credenciales

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando a WiFi...");
    }

    Serial.println("Conectado a WiFi.");

    while (true) {
        // Aquí puedes agregar el código para enviar los datos a través de WiFi
        Serial.println("Enviando datos...");
        // Simulación de envío de datos
        vTaskDelay(10000 / portTICK_PERIOD_MS); // Espera 10 segundos
    }
}

void setup() {
    // Crear tareas
    xTaskCreate(taskInitialization, "TaskInitialization", 2048, NULL, 1, NULL);
    xTaskCreate(taskCriticalSensorReview, "TaskCriticalSensorReview", 2048, NULL, 2, NULL);
    xTaskCreate(taskSupportingSensorReview, "TaskSupportingSensorReview", 2048, NULL, 2, NULL);
    xTaskCreate(taskMonitoringSensorReview, "TaskMonitoringSensorReview", 2048, NULL, 1, NULL);
    xTaskCreate(taskConnectionAndData, "TaskConnectionAndData", 2048, NULL, 1, NULL);
}

void loop() {
    // No se requiere ninguna operación en el loop principal
}
