// Projeto Final - Tamagotchi
#include "pic18f4520.h"
#include "bits.h"
#include "config.h"
#include "io.h"
#include "keypad.h"
#include "lcd.h"
#include "atraso.h"
#include "pwm.h"

// Variáveis do LCD
#define L_ON	0x0F
#define L_OFF	0x08
#define L_CLR	0x01
#define L_L1	0x80
#define L_L2	0xC0
#define L_L3    0x90
#define L_L4    0xD0
#define L_CR	0x0F		
#define L_NCR	0x0C	
#define L_CFG   0x38

// Função inicializa animação do Pet
void petInicio(void) {
    unsigned char i;

    unsigned char pet[48] = {0b00000, 0b00000, 0b00000, 0b00001, 0b00011, 0b00110, 0b01100, 0b01100,
        0b00000, 0b00000, 0b11111, 0b11111, 0b00000, 0b00000, 0b00000, 0b00000,
        0b00000, 0b00000, 0b00000, 0b10000, 0b11000, 0b01100, 0b00110, 0b00110,
        0b01100, 0b01100, 0b01100, 0b01100, 0b01100, 0b00110, 0b00011, 0b00001,
        0b11011, 0b11011, 0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b11111,
        0b00110, 0b00110, 0b00110, 0b00110, 0b00110, 0b01100, 0b11000, 0b10000};

    unsigned char pet_deitado[48] = {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b0011, 0b00110,
        0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b11111, 0b00000,
        0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b11000, 0b01100,
        0b01100, 0b11000, 0b11000, 0b11000, 0b11000, 0b01100, 0b00111, 0b00011,
        0b00000, 0b11011, 0b11011, 0b00000, 0b00000, 0b00000, 0b11111, 0b11111,
        0b00110, 0b00011, 0b00011, 0b00011, 0b00011, 0b00110, 0b11100, 0b11000};

    lcdCommand(0x40);

    for (i = 0; i < 48; i++) {
        lcdData(pet[i]);
    }
    lcdCommand(L_L2 + 6);
    lcdData(0);
    lcdData(1);
    lcdData(2);
    lcdCommand(L_L3 + 6);
    lcdData(3);
    lcdData(4);
    lcdData(5);
    atraso_ms(500);

    lcdCommand(0x40);

    for (i = 0; i < 48; i++) {
        lcdData(pet_deitado[i]);
    }
    lcdCommand(L_L2 + 6);
    lcdData(0);
    lcdData(1);
    lcdData(2);
    lcdCommand(L_L3 + 6);
    lcdData(3);
    lcdData(4);
    lcdData(5);
    atraso_ms(500);
}

// Função responsável por sincronizar os leds do PORTD com a fome
void fomeLed(unsigned char fome) {
    TRISD = 0x00; // setar TRIBD para saída
    switch (fome) {
        case '8':
            bitSet(PORTD, 0);
            bitSet(PORTD, 1);
            bitSet(PORTD, 2);
            bitSet(PORTD, 3);
            bitSet(PORTD, 4);
            bitSet(PORTD, 5);
            bitSet(PORTD, 6);
            bitSet(PORTD, 7);
            break;

        case '7':
            bitClr(PORTD, 0);
            bitSet(PORTD, 1);
            bitSet(PORTD, 2);
            bitSet(PORTD, 3);
            bitSet(PORTD, 4);
            bitSet(PORTD, 5);
            bitSet(PORTD, 6);
            bitSet(PORTD, 7);
            break;

        case '6':
            bitClr(PORTD, 0);
            bitClr(PORTD, 1);
            bitSet(PORTD, 2);
            bitSet(PORTD, 3);
            bitSet(PORTD, 4);
            bitSet(PORTD, 5);
            bitSet(PORTD, 6);
            bitSet(PORTD, 7);
            break;

        case '5':
            bitClr(PORTD, 0);
            bitClr(PORTD, 1);
            bitClr(PORTD, 2);
            bitSet(PORTD, 3);
            bitSet(PORTD, 4);
            bitSet(PORTD, 5);
            bitSet(PORTD, 6);
            bitSet(PORTD, 7);
            break;

        case '4':
            bitClr(PORTD, 0);
            bitClr(PORTD, 1);
            bitClr(PORTD, 2);
            bitClr(PORTD, 3);
            bitSet(PORTD, 4);
            bitSet(PORTD, 5);
            bitSet(PORTD, 6);
            bitSet(PORTD, 7);
            break;

        case '3':
            bitClr(PORTD, 0);
            bitClr(PORTD, 1);
            bitClr(PORTD, 2);
            bitClr(PORTD, 3);
            bitClr(PORTD, 4);
            bitSet(PORTD, 5);
            bitSet(PORTD, 6);
            bitSet(PORTD, 7);
            break;

        case '2':
            bitClr(PORTD, 0);
            bitClr(PORTD, 1);
            bitClr(PORTD, 2);
            bitClr(PORTD, 3);
            bitClr(PORTD, 4);
            bitClr(PORTD, 5);
            bitSet(PORTD, 6);
            bitSet(PORTD, 7);
            break;

        case '1':
            bitClr(PORTD, 0);
            bitClr(PORTD, 1);
            bitClr(PORTD, 2);
            bitClr(PORTD, 3);
            bitClr(PORTD, 4);
            bitClr(PORTD, 5);
            bitClr(PORTD, 6);
            bitSet(PORTD, 7);
            break;

        case '0':
            bitClr(PORTD, 0);
            bitClr(PORTD, 1);
            bitClr(PORTD, 2);
            bitClr(PORTD, 3);
            bitClr(PORTD, 4);
            bitClr(PORTD, 5);
            bitClr(PORTD, 6);
            bitClr(PORTD, 7);
            break;
    }
}

// Função responsável por sincronizar os leds do PORTB com a diversão
void funLed(unsigned char fun) {
    TRISB = 0x00; // setar TRISB par saída
    switch (fun) {
        case '7':
            bitSet(PORTB, 0);
            bitSet(PORTB, 1);
            bitSet(PORTB, 2);
            bitSet(PORTB, 3);
            bitSet(PORTB, 4);
            bitSet(PORTB, 5);
            bitSet(PORTB, 6);
            bitSet(PORTB, 7);
            break;

        case '6':
            bitClr(PORTB, 0);
            bitClr(PORTB, 1);
            bitSet(PORTB, 2);
            bitSet(PORTB, 3);
            bitSet(PORTB, 4);
            bitSet(PORTB, 5);
            bitSet(PORTB, 6);
            bitSet(PORTB, 7);
            break;

        case '5':
            bitClr(PORTB, 0);
            bitClr(PORTB, 1);
            bitClr(PORTB, 2);
            bitSet(PORTB, 3);
            bitSet(PORTB, 4);
            bitSet(PORTB, 5);
            bitSet(PORTB, 6);
            bitSet(PORTB, 7);
            break;

        case '4':
            bitClr(PORTB, 0);
            bitClr(PORTB, 1);
            bitClr(PORTB, 2);
            bitClr(PORTB, 3);
            bitSet(PORTB, 4);
            bitSet(PORTB, 5);
            bitSet(PORTB, 6);
            bitSet(PORTB, 7);
            break;

        case '3':
            bitClr(PORTB, 0);
            bitClr(PORTB, 1);
            bitClr(PORTB, 2);
            bitClr(PORTB, 3);
            bitClr(PORTB, 4);
            bitSet(PORTB, 5);
            bitSet(PORTB, 6);
            bitSet(PORTB, 7);
            break;

        case '2':
            bitClr(PORTB, 0);
            bitClr(PORTB, 1);
            bitClr(PORTB, 2);
            bitClr(PORTB, 3);
            bitClr(PORTB, 4);
            bitClr(PORTB, 5);
            bitSet(PORTB, 6);
            bitSet(PORTB, 7);
            break;

        case '1':
            bitClr(PORTB, 0);
            bitClr(PORTB, 1);
            bitClr(PORTB, 2);
            bitClr(PORTB, 3);
            bitClr(PORTB, 4);
            bitClr(PORTB, 5);
            bitClr(PORTB, 6);
            bitSet(PORTB, 7);
            break;

        case '0':
            bitClr(PORTB, 0);
            bitClr(PORTB, 1);
            bitClr(PORTB, 2);
            bitClr(PORTB, 3);
            bitClr(PORTB, 4);
            bitClr(PORTB, 5);
            bitClr(PORTB, 6);
            bitClr(PORTB, 7);
            break;
    }
}

// Função que imprime o pet negando algo
void petNao(void) {
    unsigned char i;

    unsigned char pet_nao1[48] = {0b00000, 0b00000, 0b00000, 0b00001, 0b00011, 0b00110, 0b01100, 0b01100,
        0b00000, 0b00000, 0b11111, 0b11111, 0b00000, 0b00000, 0b00011, 0b00011,
        0b00000, 0b00000, 0b00000, 0b10000, 0b11000, 0b01100, 0b00110, 0b00110,
        0b01100, 0b01100, 0b01100, 0b01100, 0b00110, 0b00011, 0b00001, 0b00000,
        0b00000, 0b00011, 0b00000, 0b00000, 0b00000, 0b11111, 0b11111, 0b00000,
        0b00110, 0b11110, 0b00110, 0b00110, 0b01100, 0b11000, 0b10000, 0b00000};

    unsigned char pet_nao2[48] = {0b00000, 0b00000, 0b00000, 0b00001, 0b00011, 0b00110, 0b01100, 0b01100,
        0b00000, 0b00000, 0b11111, 0b11111, 0b00000, 0b00000, 0b11000, 0b11000,
        0b00000, 0b00000, 0b00000, 0b10000, 0b11000, 0b01100, 0b00110, 0b00110,
        0b01100, 0b01111, 0b01100, 0b01100, 0b00110, 0b00011, 0b00001, 0b00000,
        0b00000, 0b11000, 0b00000, 0b00000, 0b00000, 0b11111, 0b11111, 0b00000,
        0b00110, 0b00110, 0b00110, 0b00110, 0b01100, 0b11000, 0b10000, 0b00000};

    lcdCommand(L_CLR);
    lcdCommand(0x40);

    for (i = 0; i < 48; i++) {
        lcdData(pet_nao1[i]);
    }
    lcdCommand(L_L2 + 6);
    lcdData(0);
    lcdData(1);
    lcdData(2);
    lcdCommand(L_L3 + 6);
    lcdData(3);
    lcdData(4);
    lcdData(5);

    atraso_ms(1000);
    lcdCommand(0x40);

    for (i = 0; i < 48; i++) {
        lcdData(pet_nao2[i]);
    }
    lcdCommand(L_L2 + 6);
    lcdData(0);
    lcdData(1);
    lcdData(2);
    lcdCommand(L_L3 + 6);
    lcdData(3);
    lcdData(4);
    lcdData(5);

    atraso_ms(1000);
    lcdCommand(0x40);

    for (i = 0; i < 48; i++) {
        lcdData(pet_nao1[i]);
    }
    lcdCommand(L_L2 + 6);
    lcdData(0);
    lcdData(1);
    lcdData(2);
    lcdCommand(L_L3 + 6);
    lcdData(3);
    lcdData(4);
    lcdData(5);

    atraso_ms(1000);
    lcdCommand(0x40);

    for (i = 0; i < 48; i++) {
        lcdData(pet_nao2[i]);
    }
    lcdCommand(L_L2 + 6);
    lcdData(0);
    lcdData(1);
    lcdData(2);
    lcdCommand(L_L3 + 6);
    lcdData(3);
    lcdData(4);
    lcdData(5);

    atraso_ms(1000);
    lcdCommand(L_CLR);
}

// Função que imprime a ação de fun
void petFun(void) {
    unsigned char i;

    unsigned char pet_fun1[64] = {0b00000, 0b00000, 0b00000, 0b00001, 0b00011, 0b00110, 0b01100, 0b01100,
        0b00000, 0b00000, 0b11111, 0b11111, 0b00000, 0b00000, 0b00000, 0b00000,
        0b00000, 0b00000, 0b00000, 0b10111, 0b01000, 0b00111, 0b01000, 0b00111,
        0b00000, 0b00000, 0b00110, 0b11001, 0b00000, 0b10000, 0b00000, 0b10000,
        0b01100, 0b01100, 0b01100, 0b01100, 0b01100, 0b00110, 0b00011, 0b00001,
        0b11011, 0b11011, 0b00000, 0b00000, 0b01110, 0b00000, 0b11111, 0b11111,
        0b01000, 0b00111, 0b01000, 0b00111, 0b00100, 0b01000, 0b11000, 0b10000,
        0b00000, 0b01000, 0b00000, 0b11111, 0b00000, 0b00000, 0b00000, 0b00000};

    unsigned char pet_fun2[64] = {0b00000, 0b00000, 0b00000, 0b00001, 0b00011, 0b00110, 0b01100, 0b01100,
        0b00000, 0b00000, 0b11111, 0b11111, 0b00000, 0b00000, 0b11011, 0b11011,
        0b00000, 0b00000, 0b00000, 0b10000, 0b01100, 0b00100, 0b00111, 0b01000,
        0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00110, 0b11001, 0b00000,
        0b01100, 0b01100, 0b01100, 0b01100, 0b01100, 0b00110, 0b00011, 0b00001,
        0b00000, 0b00000, 0b10001, 0b10001, 0b01110, 0b00000, 0b11111, 0b11111,
        0b00111, 0b01000, 0b00111, 0b01000, 0b00111, 0b01000, 0b10111, 0b10000,
        0b10000, 0b00000, 0b10000, 0b00000, 0b10000, 0b00000, 0b11111, 0b00000};

    pwmSet(90); // inicia o cooler
    lcdCommand(L_CLR);
    lcdCommand(0x40);

    for (i = 0; i < 64; i++) {
        lcdData(pet_fun1[i]);
    }
    lcdCommand(L_L2 + 6);
    lcdData(0);
    lcdData(1);
    lcdData(2);
    lcdData(3);
    lcdCommand(L_L3 + 6);
    lcdData(4);
    lcdData(5);
    lcdData(6);
    lcdData(7);

    atraso_ms(1500);
    lcdCommand(0x40);

    for (i = 0; i < 64; i++) {
        lcdData(pet_fun2[i]);
    }
    lcdCommand(L_L2 + 6);
    lcdData(0);
    lcdData(1);
    lcdData(2);
    lcdData(3);
    lcdCommand(L_L3 + 6);
    lcdData(4);
    lcdData(5);
    lcdData(6);
    lcdData(7);

    atraso_ms(2000);
    lcdCommand(L_CLR);

    for (i = 0; i < 2; i++) { // reseta os PORTS B e D para o funcionamento
        PORTB ^= 0xFF;        // do Teclado Matricial
        PORTD ^= 0xFF;
        atraso_ms(200);
    }
    pwmSet(0); // desliga o cooler
}

// Função que imprime a ação de fome
void petFome(void) {
    unsigned char i;

    unsigned char pet_fome1[48] = {0b00000, 0b00000, 0b00000, 0b00001, 0b00011, 0b00110, 0b01100, 0b01100,
        0b00000, 0b00000, 0b00000, 0b11111, 0b11111, 0b00000, 0b11011, 0b10010,
        0b00000, 0b00000, 0b00000, 0b10000, 0b11000, 0b01100, 0b00100, 0b00100,
        0b01100, 0b01100, 0b01100, 0b01100, 0b01100, 0b00110, 0b00011, 0b00001,
        0b00000, 0b00000, 0b01110, 0b11111, 0b01110, 0b00000, 0b11111, 0b11111,
        0b01110, 0b10101, 0b11111, 0b10111, 0b01110, 0b00000, 0b11000, 0b10000};

    unsigned char pet_fome2[48] = {0b00000, 0b00000, 0b00000, 0b00001, 0b00011, 0b00110, 0b01100, 0b01100,
        0b00000, 0b00000, 0b00000, 0b11111, 0b11111, 0b00000, 0b11011, 0b11011,
        0b00000, 0b00000, 0b00000, 0b10000, 0b11000, 0b01100, 0b00110, 0b00110,
        0b01100, 0b01100, 0b01100, 0b01100, 0b01100, 0b00110, 0b00011, 0b00001,
        0b00000, 0b10001, 0b10001, 0b01110, 0b00110, 0b00000, 0b11111, 0b11111,
        0b00110, 0b00110, 0b00110, 0b00110, 0b00110, 0b01100, 0b11000, 0b10000};

    pwmSet(50);

    lcdCommand(L_CLR);
    lcdCommand(0x40);

    for (i = 0; i < 48; i++) {
        lcdData(pet_fome1[i]);
    }
    lcdCommand(L_L2 + 6);
    lcdData(0);
    lcdData(1);
    lcdData(2);
    lcdCommand(L_L3 + 6);
    lcdData(3);
    lcdData(4);
    lcdData(5);

    atraso_ms(1500);
    lcdCommand(0x40);

    for (i = 0; i < 48; i++) {
        lcdData(pet_fome2[i]);
    }
    lcdCommand(L_L2 + 6);
    lcdData(0);
    lcdData(1);
    lcdData(2);
    lcdCommand(L_L3 + 6);
    lcdData(3);
    lcdData(4);
    lcdData(5);

    atraso_ms(2000);
    lcdCommand(L_CLR);

    for (i = 0; i < 2; i++) {
        PORTB ^= 0xFF;
        PORTD ^= 0xFF;
        atraso_ms(200);
    }
    pwmSet(0);
}

// Função que imprime strings no LCD
void imprime(const char* msg) {
    unsigned char i;

    while (msg[i] != 0) {
        lcdData(msg[i]);
        i++;
    }
}

// Função utilizada para checar status
void petX(unsigned char fome, unsigned char fun) {
    unsigned char i;

    unsigned char pet_X[48] = {0b00000, 0b00000, 0b00000, 0b00001, 0b00011, 0b00110, 0b01101, 0b01100,
        0b00000, 0b00000, 0b11111, 0b11111, 0b00000, 0b00000, 0b01010, 0b10001,
        0b00000, 0b00000, 0b00000, 0b10000, 0b11000, 0b01100, 0b10110, 0b00110,
        0b01101, 0b01100, 0b01100, 0b01100, 0b01100, 0b00110, 0b00011, 0b00001,
        0b00000, 0b00000, 0b01110, 0b10001, 0b10001, 0b00000, 0b11111, 0b11111,
        0b10110, 0b00110, 0b00110, 0b00110, 0b00110, 0b01100, 0b11000, 0b10000};

    if(fome == '0'){          // se fome = 0, o jogo irá acabar.
    lcdCommand(L_CLR);
    lcdCommand(0x40);
    lcdCommand(L_L1 + 2);
    imprime("Game - Over!");

    lcdCommand(0x40);       
    for (i = 0; i < 64; i++) {
        lcdData(pet_X[i]);
    }
    lcdCommand(L_L2 + 6);
    lcdData(0);
    lcdData(1);
    lcdData(2);
    lcdCommand(L_L3 + 6);
    lcdData(3);
    lcdData(4);
    lcdData(5);
    lcdCommand(L_L4 + 2);
    lcdData('C');
    lcdData('a');
    lcdData('u');
    lcdData('s');
    lcdData('a');
    lcdData(':');
    lcdData(' ');
    lcdData('F');
    lcdData('o');
    lcdData('m');
    lcdData('e');
    bitSet(PORTC, 1); // inicia o buzzer  
    atraso_ms(600000);
    }
    
    if(fun == '0'){          // se fome = 0, jogo irá acabar.
    lcdCommand(L_CLR);
    lcdCommand(0x40);
    lcdCommand(L_L1 + 2);
    imprime("Game - Over!");

    lcdCommand(0x40);
    for (i = 0; i < 64; i++) {
        lcdData(pet_X[i]);
    }
    lcdCommand(L_L2 + 6);
    lcdData(0);
    lcdData(1);
    lcdData(2);
    lcdCommand(L_L3 + 6);
    lcdData(3);
    lcdData(4);
    lcdData(5);
    lcdCommand(L_L4 + 2);
    lcdData('C');
    lcdData('a');
    lcdData('u');
    lcdData('s');
    lcdData('a');
    lcdData(':');
    lcdData(' ');
    lcdData('F');
    lcdData('u');
    lcdData('n');
    bitSet(PORTC, 1); // inicia o buzzer  
    atraso_ms(600000);
    }
}

// Main
void main(void) {
    unsigned char i, j, tecla;
    unsigned char fome = '8', fun = '7'; // fome máx = 8; fun máx = 7
    float tempo;
    int cont1, cont2;

    unsigned char pet[48] = {0b00000, 0b00000, 0b00000, 0b00001, 0b00011, 0b00110, 0b01100, 0b01100,
        0b00000, 0b00000, 0b11111, 0b11111, 0b00000, 0b00000, 0b00000, 0b00000,
        0b00000, 0b00000, 0b00000, 0b10000, 0b11000, 0b01100, 0b00110, 0b00110,
        0b01100, 0b01100, 0b01100, 0b01100, 0b01100, 0b00110, 0b00011, 0b00001,
        0b11011, 0b11011, 0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b11111,
        0b00110, 0b00110, 0b00110, 0b00110, 0b00110, 0b01100, 0b11000, 0b10000};

    lcdInit();
    
    lcdCommand(L_NCR);
    lcdCommand(L_L1);
    imprime("Simulador de Pet"); // imprime no LCD
    for (j = 0; j < 1; j++) {
        for (i = 0; i < 29; i++) {
            atraso_ms(100);
            lcdCommand(0x18); //move pra direita
        }
        for (i = 0; i < 29; i++) {
            atraso_ms(100);
            lcdCommand(0x1C); //move pra esquerda
        }
    }

    lcdCommand(L_CLR);
    for (i = 0; i < 3; i++) { // animação de inicio
        petInicio();
    }
    lcdCommand(L_CLR);

    kpInit();
    pwmInit();
    TRISC = 0x00;

    for (;;) {
        TRISB = 0x07;
        TRISD = 0x0f;
        cont1++;
        cont2++;
        fomeLed(fome);
        funLed(fun);

        lcdCommand(0x40);
        for (i = 0; i < 48; i++) {
            lcdData(pet[i]);
        }
        lcdCommand(L_L2 + 6);
        lcdData(0);
        lcdData(1);
        lcdData(2);
        lcdCommand(L_L3 + 6);
        lcdData(3);
        lcdData(4);
        lcdData(5);

        if (cont1 == 250) { // contador de tempo para Fome
            fome--;
            cont1 = 0;
        }
        if (cont2 == 350) { // contador de tempo para Fun
            fun--;
            cont2 = 0;
        }
        for (tempo = 0; tempo < 40; tempo++); // +- 10ms

        kpDebounce();

        if (kpRead() != tecla) {
            tecla = kpRead();

            if (bitTst(tecla, 3)) { // botão 1 - alimenta
                if (fome == '8') {
                    petNao();
                } else {
                    fome++;
                    petFome();
                }
            }

            if (bitTst(tecla, 2)) { // botão 4 - carinho
                if (fun == '7') {
                    petNao();
                } else {
                    fun++;
                    petFun();
                }
            }
        }
        
        petX(fome, fun);    // função para verificar os status de fome e fun  
       
    }
}