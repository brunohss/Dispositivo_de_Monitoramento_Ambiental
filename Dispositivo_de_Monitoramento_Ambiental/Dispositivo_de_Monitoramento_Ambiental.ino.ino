#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>
#include <MQ135.h>

// Configuração WiFi
const char* ssid = "SEU_SSID";
const char* password = "SUA_SENHA";

// Configuração MQTT
const char* mqtt_server = "broker.hivemq.com";
const char* topic_quality = "monitoramento/qualidade";
const char* topic_oxygen = "monitoramento/oxigenio";
const char* topic_gases = "monitoramento/gases";

WiFiClient espClient;
PubSubClient client(espClient);

// Sensores
Adafruit_BME680 bme; // Sensor de qualidade do ar
MQ135 mq135(34); // Sensor MQ-135 conectado ao pino 34

void setup_wifi() {
  delay(10);
  Serial.println("Conectando ao WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Conectado ao WiFi!");
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Tentando conectar ao MQTT...");
    if (client.connect("ESP32Monitor")) {
      Serial.println("Conectado ao broker MQTT!");
    } else {
      Serial.print("Falha na conexão MQTT, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos.");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  // Inicializar WiFi
  setup_wifi();
  client.setServer(mqtt_server, 1883);

  // Inicializar sensores
  if (!bme.begin()) {
    Serial.println("Erro ao inicializar o BME680!");
    while (1);
  }

  Serial.println("BME680 e MQ-135 inicializados.");
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Leitura dos sensores
  if (!bme.performReading()) {
    Serial.println("Erro ao ler o BME680!");
    return;
  }

  float temperature = bme.temperature;
  float humidity = bme.humidity;
  float air_quality = bme.gas_resistance / 1000.0; // Em kOhms
  float co2_estimate = mq135.getPPM(); // CO2 estimado em ppm

  // Publicar dados no MQTT
  char payload[100];
  snprintf(payload, sizeof(payload), "Temp: %.2f°C, Hum: %.2f%%, Qualidade: %.2fkOhms", temperature, humidity, air_quality);
  client.publish(topic_quality, payload);

  snprintf(payload, sizeof(payload), "CO2 estimado: %.2fppm", co2_estimate);
  client.publish(topic_gases, payload);

  // Exibir no Serial Monitor
  Serial.println(payload);

  delay(2000); // Ajuste conforme necessário
}
