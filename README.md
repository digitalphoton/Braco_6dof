# Controle para um braço mecânico

Esse código foi desenvolvido para realizar o controle de um braço mecânico de 6 graus de liberdade, utilizando servomotores MG996R.
O _target_ do projeto é um ESP32, e o controle é feito utilizando o controlador PWM para LEDs, também chamado de periférico LED Control (LEDC).
Os servos são alimentados com 6 volts de uma fonte externa, e o sinal de controle é fornecido via um conversor lógico de MOSFETs.

## TO-DO

- Implementar um sistema de interpolação para o controle, fazendo com que o servo vá gradualmente para a posição de destino
