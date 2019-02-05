/*
  Contador 10 Milhoes

  Conta ate dez milhoes e retorna contando ate zero.

  Versao: 
  2019-01-27 - 1.0 - Pierre

*/

#define S_ON  HIGH
#define S_OFF LOW

#define LED_A 2
#define LED_B 3
#define LED_C 4
#define LED_D 5
#define LED_E 6
#define LED_F 7
#define LED_G 8

#define DISPLAY_0 9
#define DISPLAY_1 10
#define DISPLAY_2 11
#define DISPLAY_3 12
#define DISPLAY_4 14
#define DISPLAY_5 15
#define DISPLAY_6 16

#define LED_FLASH 19

unsigned long ulNumeroBuffer = 0;
int iSoma = 1;
int iLedAcesso = 0;
int iTesteExecutado = 0;

unsigned long DELAY_TIME =1000; // 1000 para 1 sec
unsigned long ulDelayStart = 0; // the time the delay started
bool bDelayRunning = false; // true if still waiting for delay to finish


void teste_inicial( void );
void pierre(void);
void apagar_todos_displays(void);
void acender_todos_displays(void);
void exibir_numero( int numero );
void ativa_display( int iDisplay, int i_numero );

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_FLASH, OUTPUT);
  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_C, OUTPUT);
  pinMode(LED_D, OUTPUT);
  pinMode(LED_E, OUTPUT);
  pinMode(LED_F, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(DISPLAY_0, OUTPUT);
  pinMode(DISPLAY_1, OUTPUT);
  pinMode(DISPLAY_2, OUTPUT);
  pinMode(DISPLAY_3, OUTPUT);
  pinMode(DISPLAY_4, OUTPUT);
  pinMode(DISPLAY_5, OUTPUT);
  pinMode(DISPLAY_6, OUTPUT);
  ulDelayStart = millis();   // start delay
  bDelayRunning = true; // not finished yet
}

// the loop function runs over and over again forever
void loop() {
    if( iTesteExecutado < 1 ){
      teste_inicial();
      pierre();
      apagar_todos_displays();
    }
  
    if (bDelayRunning && ((millis() - ulDelayStart) >= (DELAY_TIME-950))) {
        iLedAcesso = S_OFF;
        digitalWrite(LED_FLASH, iLedAcesso);
    }
    
    if (bDelayRunning && ((millis() - ulDelayStart) >= DELAY_TIME)) {
        ulDelayStart += DELAY_TIME;
        ulNumeroBuffer += iSoma;
        if( ulNumeroBuffer == 10000000 ) iSoma *= (-1);
        if( ulNumeroBuffer == 0 ) iSoma *= (-1);
        iLedAcesso = S_ON;
        digitalWrite(LED_FLASH, iLedAcesso);
    }
    if( ( ulNumeroBuffer % 3600) == 0 ) pierre();
    
    exibir_numero( ulNumeroBuffer );
}


void exibir_numero( unsigned long ulNumero ){
    char cNumero[]={"1234567"};
    char cNN[]="";

    sprintf( cNumero, "%07lu", ulNumero  );
    strncpy( cNN, &cNumero[0], 1 );
    ativa_display(  DISPLAY_0, cNN );
    delay(2);
    strncpy( cNN, &cNumero[1], 1 );
    ativa_display(  DISPLAY_1, cNN );
    delay(2);
    strncpy( cNN, &cNumero[2], 1 );
    ativa_display(  DISPLAY_2, cNN );
    delay(2);
    strncpy( cNN, &cNumero[3], 1 );
    ativa_display(  DISPLAY_3, cNN );
    delay(2);
    strncpy( cNN, &cNumero[4], 1 );
    ativa_display(  DISPLAY_4, cNN );
    delay(2);
    strncpy( cNN, &cNumero[5], 1 );
    ativa_display(  DISPLAY_5, cNN );
    delay(2);
    strncpy( cNN, &cNumero[6], 1 );
    ativa_display(  DISPLAY_6, cNN );
    delay(2);
}



void ativa_display( int iDisplay, char *c_numero ){
    int mapa_digitos[][7] = {
      //a,b, c, d, e, f, g
      { S_ON,  S_ON,  S_ON,  S_ON,  S_ON,  S_ON,  S_OFF}, // 0
      {S_OFF, S_ON,  S_ON,  S_OFF, S_OFF, S_OFF, S_OFF}, // 1
      {S_ON,  S_ON,  S_OFF, S_ON,  S_ON,  S_OFF, S_ON }, // 2
      {S_ON,  S_ON,  S_ON,  S_ON,  S_OFF, S_OFF, S_ON }, // 3
      {S_OFF, S_ON,  S_ON,  S_OFF, S_OFF, S_ON,  S_ON }, // 4
      {S_ON,  S_OFF, S_ON,  S_ON,  S_OFF, S_ON,  S_ON }, // 5
      {S_ON,  S_OFF, S_ON,  S_ON,  S_ON,  S_ON,  S_ON }, // 6
      {S_ON,  S_ON,  S_ON,  S_OFF, S_OFF, S_OFF, S_OFF}, // 7
      {S_ON,  S_ON,  S_ON,  S_ON,  S_ON,  S_ON,  S_ON }, // 8
      {S_ON,  S_ON,  S_ON,  S_ON,  S_OFF, S_ON,  S_ON }, // 9
      {S_ON , S_ON , S_ON , S_OFF, S_ON , S_ON , S_ON }, // A
      {S_OFF, S_OFF, S_ON , S_ON , S_ON , S_ON , S_ON }, // B
      {S_ON , S_OFF, S_OFF, S_ON , S_ON , S_ON , S_OFF}, // C
      {S_OFF, S_ON , S_ON , S_ON , S_ON , S_OFF, S_ON }, // D
      {S_ON , S_OFF, S_OFF, S_ON , S_ON , S_ON , S_ON }, // E
      {S_ON , S_OFF, S_OFF, S_OFF, S_ON , S_ON , S_ON }, // F
      {S_OFF, S_OFF, S_OFF, S_OFF, S_OFF, S_OFF, S_OFF}, // tudo apagado
    };  

    apagar_todos_displays();
    if( iDisplay == DISPLAY_0 ){
        digitalWrite(DISPLAY_0, LOW);
    }
    if( iDisplay == DISPLAY_1 ){
        digitalWrite(DISPLAY_1, LOW);
    }
    if( iDisplay == DISPLAY_2 ){
        digitalWrite(DISPLAY_2, LOW);
    }
    if( iDisplay == DISPLAY_3 ){
        digitalWrite(DISPLAY_3, LOW);
    }
    if( iDisplay == DISPLAY_4 ){
        digitalWrite(DISPLAY_4, LOW);
    }
    if( iDisplay == DISPLAY_5 ){
        digitalWrite(DISPLAY_5, LOW);
    }
    if( iDisplay == DISPLAY_6 ){
        digitalWrite(DISPLAY_6, LOW);
    }
    int i_numero = atoi( c_numero );
    for (int i = LED_A, x=0; i <= LED_G; i++, x++) {
        digitalWrite( i, mapa_digitos[i_numero][x]);
    }
}


void teste_inicial( void ){
    apagar_todos_displays();    
    acender_todos_displays();    
    for (int i = LED_A; i <= LED_G; i++ ) {
        digitalWrite( i, S_ON);
        delay( 80 );
        digitalWrite( i, S_OFF);
        if( i > LED_G ) break;
    }
    apagar_todos_displays();
    for (int i = LED_A; i <= LED_G; i++ ) {
        digitalWrite( i, S_ON);
    }
    for( int i = DISPLAY_0; i <= DISPLAY_6; i++ ){
        digitalWrite( i, LOW);
        delay(180);
        digitalWrite( i, HIGH);
    }
    for( int i = DISPLAY_6; i >= DISPLAY_0; i-- ){
        digitalWrite( i, LOW);
        delay(180);
        digitalWrite( i, HIGH);
    }
    apagar_todos_displays();    
    delay(200);
    for( int i=0; i<3; i++ ){
        acender_todos_displays();    
        delay(500);
        apagar_todos_displays();    
        delay(500);
    }
    apagar_todos_displays();    
    iTesteExecutado++;
}


void pierre(void){
    int mapa_digitos[][7] = {
      //a,b, c, d, e, f, g
      { S_ON,  S_ON,  S_OFF,  S_OFF,  S_ON,  S_ON,  S_ON}, // 0 - P
      {S_OFF, S_OFF,  S_OFF,  S_OFF, S_ON, S_ON, S_OFF}, // 1 - I
      {S_ON , S_OFF, S_OFF, S_ON , S_ON , S_ON , S_ON }, // 2 - E
      {S_OFF,  S_OFF,  S_OFF, S_OFF,  S_ON,  S_OFF, S_ON }, // 3 - r
    };  

    unsigned long ulInicio = millis();
   
    while( true ){  
        apagar_todos_displays();
        digitalWrite(DISPLAY_1, LOW);
        for (int i = LED_A, x=0; i <= LED_G; i++, x++) {
            digitalWrite( i, mapa_digitos[0][x]);
        }
        delay(2);
        apagar_todos_displays();
        digitalWrite(DISPLAY_2, LOW);
        for (int i = LED_A, x=0; i <= LED_G; i++, x++) {
            digitalWrite( i, mapa_digitos[1][x]);
        }
        delay(2);
        apagar_todos_displays();
        digitalWrite(DISPLAY_3, LOW);
        for (int i = LED_A, x=0; i <= LED_G; i++, x++) {
            digitalWrite( i, mapa_digitos[2][x]);
        }
        delay(2);
        apagar_todos_displays();
        digitalWrite(DISPLAY_4, LOW);
        for (int i = LED_A, x=0; i <= LED_G; i++, x++) {
            digitalWrite( i, mapa_digitos[3][x]);
        }
        delay(2);
        apagar_todos_displays();
        digitalWrite(DISPLAY_5, LOW);
        for (int i = LED_A, x=0; i <= LED_G; i++, x++) {
            digitalWrite( i, mapa_digitos[3][x]);
        }
        delay(2);
        apagar_todos_displays();
        digitalWrite(DISPLAY_6, LOW);
        for (int i = LED_A, x=0; i <= LED_G; i++, x++) {
            digitalWrite( i, mapa_digitos[2][x]);
        }
        delay(2);
        if( ( millis() - ulInicio ) > 3000 )break; 
    }
}


void apagar_todos_displays(void){
    digitalWrite(DISPLAY_6, HIGH);
    digitalWrite(DISPLAY_5, HIGH);
    digitalWrite(DISPLAY_4, HIGH);
    digitalWrite(DISPLAY_3, HIGH);
    digitalWrite(DISPLAY_2, HIGH);
    digitalWrite(DISPLAY_1, HIGH);
    digitalWrite(DISPLAY_0, HIGH);
}

void acender_todos_displays(void){
    digitalWrite(DISPLAY_6, LOW);
    digitalWrite(DISPLAY_5, LOW);
    digitalWrite(DISPLAY_4, LOW);
    digitalWrite(DISPLAY_3, LOW);
    digitalWrite(DISPLAY_2, LOW);
    digitalWrite(DISPLAY_1, LOW);
    digitalWrite(DISPLAY_0, LOW);
}
