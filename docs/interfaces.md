# 📡 Documentação das Interfaces e Protocolos

Este documento descreve as **interfaces**, **protocolos** e **módulos de comunicação** utilizados no projeto de Monitoramento Inteligente da Qualidade da Água - Versão 1.

---

## 1. Interface Serial

- **Tipo:** USB Serial
- **Padrão:** UART
- **Função:** Comunicação entre o **Arduino UNO** e o **computador**.
- **Configuração:**
  - Baud rate: 9600 bps
  - Data bits: 8
  - Paridade: Nenhuma
  - Stop bits: 1
- **Fluxo:**
  - O Arduino envia a leitura simulada da temperatura (ex.: `TEMP:25.0`) pela **porta serial**.
  - O script Python lê e interpreta os dados.

---

## 2. Protocolo MQTT

- **Versão:** 3.1.1
- **Transporte:** TCP/IP
- **Broker:** Eclipse Mosquitto (ou equivalente)
- **Tópico publicado:** `watermonitor/temperature`
- **QoS:** 0 (não garantido) — suficiente para aplicações não críticas.

---

## 3. Módulo de Comunicação

- **Script Python:** `publisher.py`
  - **Leitura serial** via biblioteca `pyserial`.
  - **Publicação MQTT** via `paho-mqtt`.
- **Formato da mensagem:**
  - **Payload:** String representando temperatura (`float`), e.g., `25.0`.
  - **Tópico:** `watermonitor/temperature`.

---

## 4. Fluxo de Comunicação

```plaintext
Sensor (potenciômetro) → Arduino UNO → Serial USB → Python → MQTT Broker → Aplicações (Node-RED, Grafana)
```

---

## ✅ 5. **docs/hardware.md**

```markdown
# ⚙️ Documentação de Hardware

Este documento detalha os **componentes de hardware** utilizados no protótipo de Monitoramento Inteligente da Qualidade da Água - Versão 1.

---

## 1. Plataforma de Desenvolvimento

- **Microcontrolador:** Arduino UNO R3
- **Comunicação:** Serial via USB

---

## 2. Sensores

### Potenciômetro
- **Função:** Simula a variação da temperatura da água.
- **Conexão:**
  - Pino central → A0
  - Laterais → GND e 5V

---

## 3. Atuadores

### LED Vermelho
- **Função:** Indicação visual de temperatura acima do limite.
- **Conexão:**
  - Anodo → D8 via resistor 220Ω
  - Catodo → GND

---

## 4. Esquema Eletrônico

- Arquivo `.fzz` disponível em `fritzing/monitoramento.fzz`.
- Esquema montado em **protoboard** para fácil prototipagem.

---

## 5. Impressão 3D

Para futuras versões:

- **Caixa protetora** para o Arduino e componentes.
- **Suportes** para fixação de sensores reais (**DS18B20**, **pH**, **turbidez**).
- Medidas recomendadas:
  - Caixa: 110mm x 75mm x 40mm
  - Suporte do sensor: conforme especificação de cada modelo.

---

## 6. Evolução Prevista

- Troca do potenciômetro por sensor **DS18B20**.
- Inclusão de sensores de **pH** e **turbidez**.
- Implementação de **proteção IP65** para uso em ambientes externos.

---

## 7. Observações

Este hardware foi desenvolvido para **fins didáticos e validação conceitual**.  
Para aplicações reais, recomenda-se reforçar a **robustez** e realizar **ensaios de calibração** com amostras de água.
