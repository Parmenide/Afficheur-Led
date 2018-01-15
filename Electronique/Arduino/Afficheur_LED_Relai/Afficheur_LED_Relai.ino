/*
 * 
 * 
 * Afficheur Led - Relai
 * 
 * 
 */

#include <VirtualWire.h>


void setup(){
  
    // Initialisation de VirtualWire
    vw_set_rx_pin(A0);  // RX
    vw_set_tx_pin(A3);  // TX
    vw_setup(2000);

    // Message de bienvenue
    Serial.begin(9600);
    Serial.println();
    Serial.println("-------------------------------------");
    Serial.println("---------- Afficheur Led ------------");
    Serial.println("------- Panneau de Commande ---------");
    Serial.println("-------------- Relai ----------------");
    Serial.println("-------------------------------------");
    Serial.println("-------------- V 1.0 ----------------");
    Serial.println("-------------------------------------");
    Serial.println();
} 
 

void loop(){

    // RECEPTION //
    
    vw_rx_start();
    //
    byte Classe[20];
    //
    byte taille_Classe = sizeof(Classe);
    //
    vw_wait_rx(); // attendre l’arrivée d’un nouveau message
    //
    vw_get_message((byte *) &Classe, &taille_Classe);
    //
    // Affichage des données recu par RF
    Serial.println();
    Serial.print("Signal recu par RF 433mhz : ");
    for(byte i = 0; i < 20; i++)
    {
        Serial.print(Classe[i]);
    }
    //
    vw_rx_stop();
    
    // EMISSION //
    
    // Envoi des données par RF à l'aide de VirtualWire
    vw_send((byte *) &Classe, sizeof(Classe)); // On envoie le message
    vw_wait_tx(); // On attend la fin de l'envoi
    
    // Affichage des données envoyées par RF
    Serial.println();
    Serial.print("Signal envoyé par RF 433mhz : ");
    for(byte i = 0; i < 20; i++)
    {
        Serial.print(Classe[i]);
    }
    Serial.println("---------------------------------------------");
    
    // Delai
    delay(1000);
}

 
