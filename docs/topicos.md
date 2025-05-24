# 📡 Estrutura de Tópicos MQTT e Formato de Payload

Este documento descreve a **estrutura dos tópicos MQTT** utilizados no projeto de **Monitoramento Inteligente da Qualidade da Água - Versão 1**, bem como o **formato das mensagens (payloads)**.

---

## ✅ Tópicos Utilizados

### 1. `watermonitor/temperature`

- **Descrição:**  
Tópico responsável por publicar os valores de **temperatura simulada** coletados pelo sistema.

- **Origem da mensagem:**  
Script Python (`publisher.py`), que lê os dados da **porta serial** do Arduino e publica no **broker MQTT**.

- **Tipo de dado:**  
`float` — valor numérico com uma casa decimal, representando a temperatura simulada em graus Celsius.

- **Exemplo de publicação:**

```plaintext
Topic: watermonitor/temperature
Payload: 27.5