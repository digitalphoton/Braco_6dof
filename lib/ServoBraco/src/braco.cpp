#include "braco.h"

void Braco::init(void) {
	rotacao.init();
	ombro.init();
	cotovelo.init();
	pulsoFlexao.init();
	pulsoRotacao.init();
	garra.init();
}
void Braco::update(void)
{
	rotacao.step();
	ombro.step();
	cotovelo.step();
	pulsoFlexao.step();
	pulsoRotacao.step();
	garra.step();
}
void Braco::estop(void) {
	rotacao.stop();
	ombro.stop();
	cotovelo.stop();
	pulsoFlexao.stop();
	pulsoRotacao.stop();
	garra.stop();
}
// recebe um comando e um argumento, atua o servo respectivo
void Braco::atuar(char comando, float argumento) {
	switch(comando) {
		default:
			Serial.println("Comando não reconhecido!");
			return;
		
		case 'Q':
		case 'q':
			Serial.print("Rotação definida para ");
			Serial.print( rotacao.setTargetPosition(argumento) );
			break;
			
		case 'W':
		case 'w':
			Serial.print("Posição do Ombro definida para ");
			Serial.print( ombro.setTargetPosition(argumento) );
			break;

		case 'E':
		case 'e':
			Serial.print("Posição do Cotovelo definida para ");
			Serial.print( cotovelo.setTargetPosition(argumento) );
			break;

		case 'R':
		case 'r':
			Serial.print("Flexão do Pulso definida para ");
			Serial.print( pulsoFlexao.setTargetPosition(argumento) );
			break;

		case 'T':
		case 't':
			Serial.print("Rotacao do Pulso definida para ");
			Serial.print( pulsoRotacao.setTargetPosition(argumento) );
			break;

		case 'F':
		case 'f':
			Serial.print("Posição da Garra definida para ");
			Serial.print( garra.setTargetPosition(argumento) );
			break;
		case 'p':
		case 'P':
			Serial.print("PARADA DE EMERGÊNCIA");
			estop();
			break;

	}
	Serial.println();
}
