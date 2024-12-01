# Dispositivo de Monitoramento Ambiental

## Descrição
Solução IoT desenvolvida para monitorar a qualidade do ar, níveis de oxigênio e gases em ambientes confinados. O dispositivo utiliza sensores avançados e conecta-se a um servidor MQTT para relatar os dados em tempo real.

## Tecnologias
- **Microcontrolador:** ESP32
- **Sensores:** 
  - Adafruit BME680 (temperatura, umidade, pressão e qualidade do ar)
  - MQ-135 (detecção de gases como CO2 e amônia)
- **Comunicação:** MQTT (via WiFi)

## Materiais Necessários
1. **Hardware**
   - ESP32
   - Sensor Adafruit BME680
   - Sensor MQ-135
   - Protoboard ou PCB
   - Jumpers
   - Resistores (10kΩ, conforme necessário)
   - Fonte de alimentação 5V

2. **Software**
   - Arduino IDE
   - Bibliotecas:
     - **WiFi.h**
     - **PubSubClient**
     - **Adafruit_Sensor**
     - **Adafruit_BME680**
     - **Adafruit_MQ135**

## Como Configurar
1. **Configuração do Hardware**
   - Conecte o BME680 aos pinos I2C do ESP32.
   - Conecte o MQ-135 ao pino analógico do ESP32 (pino 34, por exemplo).
   - Certifique-se de que todos os componentes estão alimentados adequadamente.

2. **Configuração do Código**
   - Edite o arquivo `main.ino` com:
     - Seu SSID e senha WiFi.
     - Servidor MQTT.
   - Faça upload do código para o ESP32 utilizando o Arduino IDE.

3. **Monitoramento**
   - Os dados serão publicados nos seguintes tópicos MQTT:
     - `monitoramento/qualidade`: Qualidade do ar (temperatura, umidade e resistência de gases).
     - `monitoramento/gases`: Estimativa de CO2 em ppm.

## Funcionamento
- O ESP32 lê os dados dos sensores periodicamente.
- Os dados são enviados para um broker MQTT em tópicos específicos.
- Pode ser integrado a um painel de controle como o Node-RED ou Home Assistant para monitoramento em tempo real.

## Exemplo de Dados Publicados
### Tópico: `monitoramento/qualidade`
