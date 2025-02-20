# Controle para um braço mecânico

Esse código foi desenvolvido para realizar o controle de um braço mecânico de 6 graus de liberdade, utilizando servomotores MG996R.
O _target_ do projeto é um ESP32, e o controle é feito utilizando o controlador PWM embutido no próprio chip do ESP32, também chamado de periférico LED Control (LEDC).
Os servos são alimentados com 6 volts de uma fonte externa, e o sinal de controle é fornecido via um conversor lógico de MOSFETs, que aumenta os 3,3 volts do ESP32 para os 6 volts dos servos.


## Biblioteca ServoBraco

O código de controle do braço foi implementado com a criação da biblioteca ServoBraco, que permite reutilizar essa funcionalidade em outros projetos.
Para usá-la, começe incluindo o arquivo header principal da biblioteca em sua main.cpp (ou em sua sketch .ino, caso use a IDE do Arduino).
Em seguida, defina uma instância da classe Braco, e a inicialize na ```setup()```.
Além disso, na versão atual da biblioteca (commit ```rewrite-9cfbed2```), é preciso implementar uma máquina de estados que atualize os motores do braço a cada 20 millisegundos.
Abaixo um exemplo de código mínimo de inicialização:

```c++
#include <ServoBraco.h>

// Definir um tipo customizado, contendo os nossos estados
typedef enum {STARTUP, STANDBY, UPDATE} Estados;

Estados estadoAtual = STARTUP;
Braco meuBraco;

unsigned long ultimoUpdate = 0;

void setup()
{
	meuBraco.init();

	// Entrar em STANDBY ao fim da inicialização
	estadoAtual = STANDBY;
}

void loop()
{
	// Entrar no estado UPDATE a cada 20 ms
	if(millis() >= ultimoUpdate + 20)
	{
		estadoAtual = UPDATE;
		ultimoUpdate = millis();
	}

	switch(estadoAtual)
	{
		default:
		case STANDBY:

			// Fazer nada :)
			break;
		
		case UPDATE:

			meuBraco.update();

			// *** Muito importante!!! ***
			//	Voltar para STANDBY após o UPDATE. É fácil esquecer de
			// 	implementar a saída de um estado, e ficar eternamente preso 
			// 	nele
			estadoAtual = STANDBY;
			break;
	}
}
```

O braço possui 6 motores servo, a maior parte nomeados com base em analogia com a anatomia humana:

- Servo de rotação do braço como um todo (```rotacao```)
- Servo do ombro (```ombro```)
- Servo do cotovelo (```cotovelo```)
- Servo de flexão do pulso(```pulsoFlexao```)
- Servo de rotação do pulso (```pulsoRotacao```)
- Servo da garra (```garra```)

Cada um desses servos está implementado como uma instância da classe servo, dentro da classe Braco.
Para movimentá-los, usa-se o método ```setTargetPosition(posDegree, newFeedRate)```, dando como argumentos a nova posição desejada (em graus de rotação do servo) e a _feedrate_ desejada, ou seja, a velocidade com que o servo se moverá (em graus por segundo).
Um bom feedrate para se utilizar na maior parte dos casos é ```20.0``` graus por segundo.
Para mover o braço declarado acima para a posição de -30 graus com _feedrate_ de 20 graus por segundo, por exemplo:

```c++
meuBraco.rotacao.setTargetPosition(30.0, 20.0);
```

Observe que essa função não move o servo por si só, mas sim define sua nova posição-alvo.
Toda vez que o braço entrar no estado de atualização, ele moverá todos os servos que não estiverem na posição-alvo por um pequeno valor, de acordo com a velocidade definida. 
Dessa forma, é possível mover vários servos de uma vez só, e também realizar outras tarefas enquanto o movimento é executado.

## TO-DO

### Controle manual

- ~~Implementar uma função que receba um comando e atue o servo correspondente~~
	- Extender essa função para um botão
	- Extender essa função para um controle analógico
		- O valor analógico modula o feedrate?

- Estudar a viabilidade de mudar o mecanismo de atualização com interrupções por timer de modo a eliminar a necessidade da máquina de estados e simplificar o uso da biblioteca.
