# Controle para um braço mecânico

Esse código foi desenvolvido para realizar o controle de um braço mecânico de 6 graus de liberdade, utilizando servomotores MG996R.
O _target_ do projeto é um ESP32, e o controle é feito utilizando o controlador PWM embutido no próprio chip do ESP32, também chamado de periférico LED Control (LEDC).
Os servos são alimentados com 6 volts de uma fonte externa, e o sinal de controle é fornecido via um conversor lógico de MOSFETs, que aumenta os 3,3 volts do ESP32 para os 6 volts dos servos.

Os pinos referentes aos servos podem ser encontrados no arquivo `lib/ServoBraco/include/braco.h`, no primeiro parâmetro das instanciações dos servos (ou seja, o primeiro valor númerico depois da abertura da chave nas linhas 15 a 20 do arquivo).
Já os pinos do joystick estão no arquivo `lib/Controle/include/controle.h`, nas linhas 61 a 71.
Neste caso, são o último valor da instanciação (o número logo antes do fechamento da chave).

## Uso do Braço

O programa de demonstração inclui duas formas de controle: via comandos do computador pela interface serial, e via um joystick conectado diretamente ao ESP32.

### Controle via Serial

Para controlar o braço pelo computador, é preciso digitar uma letra seguida de um número _float_.
A letra determina qual servo será controlado, e o número é a posição em graus desejada.
Caso o número _float_ esteja fora do range seguro para o servo, o microcontrolador automaticamente o corrige para o valor seguro mais próximo.

Abaixo segue uma tabela com os comandos para cada servo:

| Servo | Comando |
|-|-|
| Rotação | Q |
| Ombro | W |
| Cotovelo | E |
| Flexão do Pulso | R |
| Rotação do Pulso | T |
| Garra | F | 

Adicionalmente, pode se realizar uma parada de emergência de todos os servos com o comando P.

### Controle via Joystick

O braço também pode ser controlado com o joystick conectado ao ESP32.
Primeiramente, é preciso ativar o joystick apertando o botão E.
Após isso, o _stick_ analógico controlará o movimento do braço (de acordo com o modo atual, mais sobre isso a diante), enquanto a garra pode ser controlada com os botões A e C.

Para utilizar o mesmo _stick_ analógico no controle de todos os servos, o microcontrolador trabalha com dois modos de controle: 

- **Extensão/Rotação**: movimento no eixo Y controla a extensão do braço (servos Ombro e Cotovelo trabalham em conjunto) enquanto o eixo X controla a rotação do braço;
- **Pulso**: eixo Y controla a flexão do pulso, enquanto o eixo X controla a rotação do pulso.

A troca entre os modos é realizada com o aperto do botão K (pressionar o _stick_ analógico).

## Biblioteca ServoBraco

O código de controle do braço foi implementado com a criação da biblioteca ServoBraco, que permite reutilizar essa funcionalidade em outros projetos.

### Inicialização

Para usá-la, começe incluindo o arquivo header principal da biblioteca em sua main.cpp (ou em sua sketch .ino, caso use a IDE do Arduino).
Em seguida, defina uma instância da classe Braco, e a inicialize na ```setup()```.
Além disso, na versão atual da biblioteca (commit ```rewrite-9cfbed2```), é preciso implementar uma máquina de estados que atualize os motores do braço a cada 20 millisegundos.
Abaixo um exemplo de código mínimo de inicialização:

```c++
#include <ServoBraco.h>

// Definir um tipo customizado, contendo os nossos estados
typedef enum {STARTUP, STANDBY, UPDATE} Estados;

// Variaveis globais de estado
Estados g_estadoAtual = STARTUP;
Estados g_estadoProximo = STANDBY;

// Declarar uma instancia da classe Braco
Braco g_meuBraco;

unsigned long g_ultimoUpdate = 0;

void setup()
{
	// Inicializar o braco
	g_meuBraco.init();

	// Entrar em STANDBY ao fim da inicialização
	g_estadoAtual = STANDBY;
}

void loop()
{
	g_estadoAtual = g_estadoProximo;

	// Entrar no estado UPDATE a cada 20 ms
	if(millis() >= g_ultimoUpdate + 20)
	{
		g_estadoProximo = UPDATE;
		g_ultimoUpdate = millis();
	}

	switch(estadoAtual)
	{
		default:
		case STANDBY:
			// Fazer nada :)
			break;
		case UPDATE:
			g_meuBraco.update();

			// *** Importante!!! ***
			//	Voltar para STANDBY após o UPDATE. É fácil esquecer de
			// 	implementar a saída de um estado, e ficar eternamente preso 
			// 	nele
			g_estadoProximo = STANDBY;
			break;
	}
}
```

### Movimentação dos Servos

O braço possui 6 motores servo, a maior parte nomeados com base em analogia com a anatomia humana:

- Servo de rotação do braço como um todo (```rotacao```)
- Servo do ombro (```ombro```)
- Servo do cotovelo (```cotovelo```)
- Servo de flexão do pulso(```pulsoFlexao```)
- Servo de rotação do pulso (```pulsoRotacao```)
- Servo da garra (```garra```)

Cada um desses servos está implementado como uma instância da classe servo, dentro da classe Braco.
Para movimentá-los, usa-se o método ```setTargetPosition(posDegree)```, dando como argumento a nova posição desejada (em graus de rotação do servo).
Para mover o braço declarado acima para uma posição de rotação de -30 graus, por exemplo:

```c++
meuBraco.rotacao.setTargetPosition(-30.0);
```

Observe que essa função não move o servo por si só, mas sim define sua nova posição-alvo.
Toda vez que o braço entrar no estado de atualização, ele moverá todos os servos que não estiverem na posição-alvo por um pequeno valor, de acordo com a velocidade definida. 
Dessa forma, é possível mover vários servos de uma vez só, e também realizar outras tarefas enquanto o movimento é executado.

Alternativamente, é possível apenas mandar um servo se mover em uma direção por tempo indeterminado com a função ```move()```. 
Esse movimento pode ser então interrompido com ```stop()```.
Observe que todos os servos tem mínimos e máximos definidos no arquivo ```include/braco.h```, e serão também automaticamente parados quando chegarem nas bordas desse range.
Exemplo:

```c++
meuBraco.rotacao.move(FORWARD);
delay(100);
meuBraco.rotacao.move(BACKWARD);
delay(100);
meuBraco.rotacao.stop();
```

Por padrão, os servos se movem com uma velocidade de 50 graus por segundo.
Essa velocidade pode ser alterada com a função ```setFeedRate()```.
É comum, no contexto de máquinas CNC, denominar a velocidade de movimento como feedrate, e por isso essa convenção também foi utilizada aqui.
Caso queira mudar a feedrate para 25 graus por segundo, para um movimento mais controlado:

```c++
meuBraco.rotacao.setFeedRate(25.0);
```

## Biblioteca Controle

Esta biblioteca define uma classe Controle, que reúne o _stick_ e os botões sob um único objeto.
Os eixos do _stick_ são definidos como instâncias da classe Potenciometro, enquanto todos os botões são instâncias da classe Botao.
Ambas as classes possuem em comum os parâmetros `id` e `pin`, que guardam um caractére identificador e um número de pino, respectivamente.
Também possuem os métodos `init()`, para inicialização, e `update()` para atualizar seus valores armazenados com base no estado atual dos componentes físicos.

### Classe Potenciometro

A classe em questão possui uma variável `value`, que guarda um valor _float_ referente à posição atual do potenciômetro físico.
Nesse caso, 0.0 indica a posição central, 1.0 a posição máxima, e -1.0 a posição mínima.
Além disso, possuimos a variável `offset`, utilizada para calibração do ponto central, e a variável `deadzone`, que define a deflexão mínima que o potenciômetro precisa ter para o _software_ registrar um movimento (isso evita que haja movimentos espúrios quando o _stick_ está quase, mas não exatamente, no centro).

Há também o método específico `getValue()`, que quando chamado retorna o valor atual da variável `value`.

### Classe Botao

A classe Botao possui as variáveis booleanas `curState` e `prevState`, que guardam o estado atual e o anterior do botão, respectivamente.
É necessário saber o último estado do botão para poder realizar detecção de bordas, para os métodos `isRisingEdge()` e `isFallingEdge()`.
Esses métodos retornam um valor booleano indicando se o botão está sendo pressionado ou solto nesse exato momento.
Isto é útil para eventos que devem ocorrer apenas no momento exato que o botão é apertado ou solto, e não repetidos enquanto ele é segurado.

Caso o evento deva acontecer continuamente enquanto o botão estiver apertado, o método `getState()` retorna apenas o valor de `curState`, indicando o estado atual do botão.

### Classe Controle

Por fim, essa classe reune todas as instâncias necessárias para o _joystick_  em um único objeto.
Além de poder acessar diretamente cada um dos objetos (eles são definidos como públicos), o usuário da classe pode chamar os métodos `init()`, que roda as funções de inicialização de cada uma das instâncias, e `update()`, que atualiza os valores de todas as instâncias.

O método `getModoAtual()` indica qual modo de controle está ativo no momento, de acordo com a variável `modoAtual`.
É possível ativar ou desativar o _joystick_ com o método `flipAtivoState()`, e verificar a situação atual com `getAtivoState()`.

## TO-DO

### Controle manual

- Estudar a viabilidade de mudar o mecanismo de atualização com interrupções por timer de modo a eliminar a necessidade da máquina de estados e simplificar o uso da biblioteca.
