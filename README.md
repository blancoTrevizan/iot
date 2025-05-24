# 💧 Monitoramento Inteligente da Qualidade da Água - Versão 1

Este repositório contém toda a documentação e código-fonte do projeto de **Monitoramento Inteligente da Qualidade da Água** utilizando **Arduino UNO**, **comunicação serial** e **protocolo MQTT**.

## 📖 Descrição do Funcionamento

O sistema simula a leitura da **temperatura da água** por meio de um **potenciômetro** conectado ao Arduino UNO. A partir da leitura, os dados são processados para:

- Acionar um **LED** se a temperatura simulada ultrapassar um limiar definido.
- Publicar o valor da temperatura no **broker MQTT**, permitindo o monitoramento remoto via ferramentas como **Node-RED** e **Grafana**.

Este projeto é uma **prova de conceito** para validar a arquitetura de monitoramento inteligente, com foco em evolução futura para sensores reais e plataformas autônomas.

---

## 🛠️ Requisitos

### Hardware
- Arduino UNO R3
- Potenciômetro analógico (simulando sensor de temperatura)
- LED vermelho
- Resistor 220Ω
- Jumpers e Protoboard
- Cabo USB para comunicação serial

### Software
- [Arduino IDE](https://www.arduino.cc/en/software)
- [Python 3](https://www.python.org/)
- Bibliotecas Python:
  - `pyserial`
  - `paho-mqtt`
- Broker MQTT (Exemplo: Eclipse Mosquitto)

---

## 🚀 Como Usar

### 1. Montagem do Circuito
- Conecte o **potenciômetro** na porta analógica A0.
- Conecte o **LED** à porta digital D8, com resistor de 220Ω.
- Consulte o arquivo `fritzing/monitoramento.fzz` para detalhes do esquema eletrônico.

### 2. Programação do Arduino
- Carregue o sketch disponível em `arduino/monitoramento.ino` na placa.
- O código realiza:
  - Leitura analógica do potenciômetro.
  - Mapeamento para faixa de temperatura.
  - Acionamento do LED.
  - Envio dos dados via porta serial.

### 3. Execução do Middleware
- Execute o script Python `python/publisher.py` para:
  - Ler dados da **porta serial**.
  - Publicar dados no **broker MQTT** no tópico `watermonitor/temperature`.

```bash
pip install pyserial paho-mqtt
python publisher.py
```

## Autores

- Matheus Sampaio de Oliveira [@blancoTrevizan](https://github.com/blancoTrevizan)

- Felipe Morishita [@femori90](https://github.com/femori90)
