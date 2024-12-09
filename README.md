# Controle para um braço mecânico

Esse código foi desenvolvido para realizar o controle de um braço mecânico de 6 graus de liberdade, utilizando servomotores MG996R.
O _target_ do projeto é um ESP32, e o controle é feito utilizando o controlador PWM para LEDs embutido no próprio chip do ESP32, também chamado de periférico LED Control (LEDC).
Os servos são alimentados com 6 volts de uma fonte externa, e o sinal de controle é fornecido via um conversor lógico de MOSFETs.

## Biblioteca ServoBraco

O código de controle do braço foi implementado com a criação da biblioteca ServoBraco, que permite reutilizar essa funcionalidade em outros projetos.
Para usá-la, começe incluindo o arquivo header principal da biblioteca em sua main.cpp (ou em sua sketch .ino, caso use a IDE do Arduino).
Em seguida, defina uma instância da classe Braco, e a inicialize na ```setup()```.

## TO-DO

### Controle manual

- ~~Implementar uma função que receba um comando e atue o servo correspondente~~
	- Extender essa função para um botão
	- Extender essa função para um controle analógico
		- O valor analógico modula o feedrate?

- ~~(Urgente!!) Limites de movimento para os servos~~
