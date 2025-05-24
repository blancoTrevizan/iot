import serial
import time
import paho.mqtt.client as mqtt

# Configurações da porta serial
SERIAL_PORT = 'COM3'  # ou '/dev/ttyUSB0' no Linux/Mac
BAUD_RATE = 9600

# Configurações do MQTT
BROKER = 'broker.hivemq.com'
PORT = 1883
TOPIC = 'watermonitor/temperature'

# Inicializar serial
ser = serial.Serial(SERIAL_PORT, BAUD_RATE)
time.sleep(2)  # Aguarda a inicialização do Arduino

# Inicializar cliente MQTT
client = mqtt.Client()
client.connect(BROKER, PORT, 60)

print("Iniciando leitura e publicação...")

try:
    while True:
        if ser.in_waiting > 0:
            linha = ser.readline().decode('utf-8').strip()
            if linha.startswith("TEMP:"):
                temperatura = linha.split(":")[1]
                print(f"Publicando: {temperatura} °C")
                client.publish(TOPIC, temperatura)
        time.sleep(1)
except KeyboardInterrupt:
    print("Encerrando...")

ser.close()
