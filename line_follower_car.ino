/**
 * Motor Driver Module:
 * HG7881 (L9110) Dual Channel. 
 * See: https://www.bananarobotics.com/shop/How-to-use-the-HG7881-(L9110)-Dual-Channel-Motor-Driver-Module
 * 
 * Obs: É recomendado usar os inputs 1A para controlar a velocidade e 1B para a direção.
 */
const int motor_de_velocidade_esquerdo = 3; // A-1A
const int motor_de_direcao_esquerdo = 9; // A-1B

const int motor_de_velocidade_direito = 10; // B-1A
const int motor_de_direcao_direito = 11; // B-1B

const int velocidade_pwd_devagar = 90;
const int velocidade_pwd_rapido = 20;

/**
 * Sensores Ópticos Reflexivos
 * Modelo: TCRT5000
 */
const int sensor_da_direita = 2;
const int sensor_da_esquerda = 4;

/** 
 * Os valores de tempo, podem variar de acordo com o circuito.
 * Todos os tempos podem ser alterados para que o carrinho fique mais acurado,
 * porém, ainda não achei uma a relação entre eles.
 */

/* Tempo que o carrinho deve esperar antes de comçar a se mover, assim que é ligado. */
const int tempo_de_inicio = 1000; 

/* Tempo que o carrinho deve esperar sempre que os motores forem forçados a parar. */
const int tempo_de_parada = 20;

/* Tempo minimo que o carrinho deve esperar após realizar uma manobra. */
const int tempo_de_manobra = 50;

/**
 * OS ENUMs estão sendo utilizados para que o código tenho melhor semântica.
 * A não utilização dos mesmo, pode ser mais eficaz, quando se tem total conhecimento.
 */
enum VELOCIDADES {
  PARADO,
  DEVAGAR,
  RAPIDO
};

enum DIRECAO {
  PARA_FRENTE,
  PARA_TRAS
};

enum MOTOR {
  ESQUERDO,
  DIREITO
};

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // Espera a porta serial ser conectada.
  }
  
  pinMode(sensor_da_direita, INPUT);
  pinMode(sensor_da_esquerda, INPUT);
  
  pinMode(motor_de_direcao_esquerdo, OUTPUT);
  pinMode(motor_de_direcao_direito, OUTPUT);
  pinMode(motor_de_velocidade_esquerdo, OUTPUT);
  pinMode(motor_de_velocidade_direito, OUTPUT);

  pararMotores();
  delay(tempo_de_inicio);
}

void loop() {
  int se = digitalRead(sensor_da_esquerda);
  int sd = digitalRead(sensor_da_direita);
  
  if (se == HIGH && sd == LOW) {
    Serial.println("Virar para a esquerda!");
    virarParaEsquerda();
  } else if (se == LOW && sd == HIGH) {
    Serial.println("Virar para a direita!");
    virarParaDireita();
  } else if (se == LOW && sd == LOW) {
    Serial.println("Acelera Gzuis!");
    seguirEmFrente();
  } else {
    Serial.println("PARA! PARA! PARA! PARA! PARA!!!!");
    pararMotores();
  }

}

void virarParaEsquerda() {
  motorDireitoParaFrenteRapido();
  motorEsquerdoParaTrasDevagar();
  delay(tempo_de_manobra);
}

void virarParaDireita() {
  motorEsquerdoParaFrenteRapido();
  motorDireitoParaTrasDevagar();
  delay(tempo_de_manobra);
}

void seguirEmFrente() {
  // set the motor speed and direction
  digitalWrite( motor_de_direcao_direito, HIGH );
  analogWrite( motor_de_velocidade_direito, velocidade_pwd_rapido );
  digitalWrite( motor_de_direcao_esquerdo, HIGH );
  analogWrite( motor_de_velocidade_esquerdo, velocidade_pwd_rapido );
}

void pararMotores() {
  digitalWrite( motor_de_direcao_direito, LOW );
  digitalWrite( motor_de_direcao_esquerdo, LOW );
  digitalWrite( motor_de_velocidade_direito, LOW );
  digitalWrite( motor_de_velocidade_esquerdo, LOW );
  delay(tempo_de_parada);
}

void motorDireitoParaFrenteRapido() {
  digitalWrite( motor_de_direcao_direito, HIGH );
  analogWrite( motor_de_velocidade_direito, velocidade_pwd_rapido );
}

void motorDireitoParaFrenteDevagar() {
  digitalWrite( motor_de_direcao_direito, HIGH );
  analogWrite( motor_de_velocidade_direito, velocidade_pwd_rapido );
}

void motorDireitoParaTrasRapido() {
  digitalWrite( motor_de_direcao_direito, LOW );
  analogWrite( motor_de_velocidade_direito, 255-velocidade_pwd_rapido );
}

void motorDireitoParaTrasDevagar() {
  digitalWrite( motor_de_direcao_direito, LOW );
  analogWrite( motor_de_velocidade_direito, 255-velocidade_pwd_devagar );
}

void motorEsquerdoParaFrenteRapido() {
  digitalWrite( motor_de_direcao_esquerdo, HIGH );
  analogWrite( motor_de_velocidade_esquerdo, velocidade_pwd_rapido );
}

void motorEsquerdoParaFrenteDevagar() {
  digitalWrite( motor_de_direcao_esquerdo, HIGH );
  analogWrite( motor_de_velocidade_esquerdo, velocidade_pwd_rapido );
}

void motorEsquerdoParaTrasRapido() {
  digitalWrite( motor_de_direcao_esquerdo, LOW );
  analogWrite( motor_de_velocidade_esquerdo, 255-velocidade_pwd_rapido );
}

void motorEsquerdoParaTrasDevagar() {
  digitalWrite( motor_de_direcao_esquerdo, LOW );
  analogWrite( motor_de_velocidade_esquerdo, 255-velocidade_pwd_devagar );
}
