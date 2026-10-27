# 🤖 RoboCup - Pikachu

Código de controle e automação desenvolvido para o robô **Pikachu**, campeão do 1º lugar na **RoboCup** promovida pela **FIAP** — evento que integra o maior festival de tecnologia universitária da América Latina.

---

## 📋 Sobre o Projeto

Este firmware é responsável pelo gerenciamento completo do robô durante a competição. Ele realiza o controle inteligente de motores de tração via comunicação serial (`Serial3`), gerencia os ciclos de acionamento, manutenção e recolhimento da arma de combate (através de máquina de estados temporizados e sensores), e customiza em tempo real a sinalização visual do robô utilizando LEDs endereçáveis (FastLED).

---

## ✨ Principais Funcionalidades

* **Controle de Movimentação (Tração):** Recebe comandos via comunicação serial (`w`, `s`, `a`, `d`, `q`) para movimentação direcional e parada de motores com controle PWM e registradores de deslocamento.
* **Automação da Arma:** Sistema baseado em máquina de estados e temporizadores (`millis()`) para acionar, manter e recolher a arma do robô com precisão milimétrica após o acionamento de sensor.
* **Feedback Visual com LEDs Endereçáveis:** Integração com a biblioteca **FastLED** (`WS2812B`) para alterar dinamicamente as cores dos LEDs conforme o estado operacional e os comandos recebidos do robô.

---

## 🛠️ Tecnologias e Componentes Utilizados

* **Hardware:**
  * Microcontrolador compatível com Arduino (utilizando portas seriais adicionais e pinos PWM/digitais).
  * Fita de LED Endereçável WS2812B (`61 LEDs`).
  * Motores CC controlados via PWM e portas de direção.
  * Sensor digital com pull-up interno.
* **Software:**
  * **Arduino IDE**
  * **Biblioteca FastLED**

---

## 🎮 Comandos de Controle (Serial)

O robô responde a comandos enviados por Serial:
* **`w`**: Frente (LEDs Azuis)
* **`s`**: Ré (LEDs Vermelhos)
* **`a`**: Esquerda (LEDs Verdes)
* **`d`**: Direita (LEDs Roxos)
* **`q`**: Parar / Break (LEDs Apagados)

---

## 🏆 Conquistas

* 🥇 **1º Lugar** na **RoboCup FIAP** (Maior evento de tecnologia universitária da América Latina).

---

## 📂 Estrutura do Código

* `Pikachu_1.ino`: Arquivo principal contendo a lógica de setup, loop, máquina de estados da arma, tratamento de interrupções/comandos seriais e animações dos LEDs.
