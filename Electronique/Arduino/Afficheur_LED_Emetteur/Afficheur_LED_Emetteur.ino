/*
 * 
 * 
 * Afficheur Led - Emetteur
 * 
 * 
 */

#include <VirtualWire.h>



// Broches d'adresse du CD4051B #1
const byte PIN_ENABLE = 2;
const byte PIN_ADDR_A = 3;
const byte PIN_ADDR_B = 4;
const byte PIN_ADDR_C = 5;
// Broches d'adresse du CD4051B #2
const byte PIN_2_ENABLE = 6;
const byte PIN_2_ADDR_A = 7;
const byte PIN_2_ADDR_B = 8;
const byte PIN_2_ADDR_C = 9;
// Broche de signal du CD4051B #1
const byte PIN_SIG = A0;
// Broche de signal  du CD4051B #2
const byte PIN_2_SIG = A1;
 


void setup(){
  
    //  Initialisation des broches du CD4051B #1
    pinMode(PIN_ADDR_A, OUTPUT);
    pinMode(PIN_ADDR_B, OUTPUT);
    pinMode(PIN_ADDR_C, OUTPUT);
    digitalWrite(PIN_ADDR_A, LOW);
    digitalWrite(PIN_ADDR_B, LOW);
    digitalWrite(PIN_ADDR_C, LOW);
    //  Initialisation des broches du CD4051B #2
    pinMode(PIN_2_ADDR_A, OUTPUT);
    pinMode(PIN_2_ADDR_B, OUTPUT);
    pinMode(PIN_2_ADDR_C, OUTPUT);
    digitalWrite(PIN_2_ADDR_A, LOW);
    digitalWrite(PIN_2_ADDR_B, LOW);
    digitalWrite(PIN_2_ADDR_C, LOW);
    // Active le CD4051B #1
    pinMode(PIN_ENABLE, OUTPUT);
    digitalWrite(PIN_ENABLE, LOW);
    // Active le CD4051B #2
    pinMode(PIN_2_ENABLE, OUTPUT);
    digitalWrite(PIN_2_ENABLE, LOW);

    // Initialisation de VirtualWire
    vw_set_tx_pin(A3);
    vw_setup(2000);

    // Message de bienvenue
    Serial.begin(9600);
    Serial.println();
    Serial.println("-------------------------------------");
    Serial.println("---------- Afficheur Led ------------");
    Serial.println("------- Panneau de Commande ---------");
    Serial.println("------------ Emetteur ---------------");
    Serial.println("-------------------------------------");
    Serial.println("-------------- V 1.0 ----------------");
    Serial.println("-------------------------------------");
    Serial.println();
} 
 

void loop(){

  // Récuperation des valeurs du tableau de commande dans une variable
  byte Classe [20];
    Classe [0] = readAnalogMuxA(0);
    Classe [1] = readAnalogMuxA(1);
    Classe [2] = readAnalogMuxA(2);
    Classe [3] = readAnalogMuxA(3);
    Classe [4] = readAnalogMuxA(4);
    Classe [5] = readAnalogMuxA(5);
    Classe [6] = readAnalogMuxA(6);
    Classe [7] = readAnalogMuxA(7);
    // Note : Un manque d'entrées sur l'Arduino à conduit ici à utiliser des entrées analogiques. Il faudrait dans l'ideal rajouter un CD4051B pour uniformiser le code.
    Classe [8] = analogRead(A2) < 400 ? 0 : 1;
    Classe [9] = digitalRead(11);
    Classe [10] = readAnalogMuxB(0);
    Classe [11] = readAnalogMuxB(1);
    Classe [12] = readAnalogMuxB(2);
    Classe [13] = readAnalogMuxB(3);
    Classe [14] = readAnalogMuxB(4);
    Classe [15] = readAnalogMuxB(5);
    Classe [16] = readAnalogMuxB(6);
    Classe [17] = readAnalogMuxB(7);
    Classe [18] = digitalRead(12);
    Classe [19] = analogRead(A7) < 400 ? 0 : 1;
    
    // Affichage des valeurs (0 ou 1) pour chaque classe 
    for(byte i = 0; i < 20; i++)
    {
        Serial.print("Classe ");
        Serial.print(i+1);
        Serial.print(" : ");
        Serial.println(Classe[i]);
    }
    // Affichage des données envoyées par RF
    Serial.println();
    Serial.print("Signal envoyé par RF 433mhz : ");
    for(byte i = 0; i < 20; i++)
    {
      Serial.print(Classe[i]);
    }
    Serial.println();
    Serial.println("--------------------------------------------------------");
    Serial.println();

  // Envoi des données par RF à l'aide de VirtualWire
  vw_send((byte *) &Classe, sizeof(Classe)); // On envoie le message
  vw_wait_tx(); // On attend la fin de l'envoi
  
  // Delai
  delay(2000);
}

 
/* Fonction pour le CD4051B #1 */
int readAnalogMuxB(byte channel) {
   // On sélectionne la voie
  digitalWrite(PIN_ADDR_A, bitRead(channel, 0));
  digitalWrite(PIN_ADDR_B, bitRead(channel, 1));
  digitalWrite(PIN_ADDR_C, bitRead(channel, 2));
  return digitalRead(PIN_SIG);
}


/* Fonction pour le CD4051B #2 */
int readAnalogMuxA(byte channel) {
   // On sélectionne la voie
  digitalWrite(PIN_2_ADDR_A, bitRead(channel, 0));
  digitalWrite(PIN_2_ADDR_B, bitRead(channel, 1));
  digitalWrite(PIN_2_ADDR_C, bitRead(channel, 2));
  return digitalRead(PIN_2_SIG);
}


