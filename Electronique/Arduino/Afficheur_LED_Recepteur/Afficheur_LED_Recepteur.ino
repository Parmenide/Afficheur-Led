/*
 
 
 Afficheur Led - Recepteur
 
 
 TO DO
 - Changer les noms de variables
 - Corriger l'orthographe
 - Debug
 
 
 */

#include <VirtualWire.h>
//Broche du ATMEGA365 connectée au ST_CP du 74HC595
const int verrou = 3;
//Broche connectée au SH_CP du 74HC595
const int horloge = 4;
//Broche connectée au DS du 74HC595
const int data = 2;
// interval at which to blink (milliseconds)
const long interval_1 = 500;
// interval at which to blink (milliseconds)
const long interval_2 = 300000;

void setup()
{
    
    // Initialisation de la bibliothèque VirtualWire
    vw_set_rx_pin(7);
    vw_setup(2000);
    vw_rx_start();
    //On met les broches en sortie du 74HC595
    pinMode(verrou, OUTPUT);
    pinMode(horloge, OUTPUT);
    pinMode(data, OUTPUT);
    //
    Serial.begin(9600);
    // Message de bienvenue
    Serial.println();
    Serial.println("-------------------------------------");
    Serial.println("---------- Afficheur Led ------------");
    Serial.println("------- Panneau d'Affichage ---------");
    Serial.println("------------ Recepteur --------------");
    Serial.println("-------------------------------------");
    Serial.println("-------------- V 1.0 ----------------");
    Serial.println("-------------------------------------");
    Serial.println();
    
}


void loop()
{
    //
    byte Classe[20];
    byte ClasseZ[20];
    byte Classe_prev[20];
    byte Classe_env[20];
    unsigned long prev_Millis_Classe[20];
    unsigned long prev_Millis_Cligno[20];
    // on actualise une variable qui donne le temps présent
    unsigned long actu_Millis = millis();
    //
    byte taille_Classe = sizeof(ClasseZ);
    //
    // On recupère les inforation recu par le recepteur RF dans la variable Classe[*]
    //vw_wait_rx();
    if (vw_get_message((byte *) &ClasseZ, &taille_Classe)){
      for (byte i = 0; i < 20; i++)
        {
            Classe[i]=ClasseZ[i];
        }
      }
    /*
     Gestion du clognottement + affichage
     */
    for (byte i = 0; i < 20; i++)
    {
        // Si on demande à afficher la led (Classe[i] = 1) alors ...
        if (Classe[i] == 0) {
            // Dans le cas ou Classe[i] etait precedement eteint, alors ...
            if (Classe_prev[i] == 1)
            {
                // si l'ecart entre le temps présent et passé est superieur à 5 minutes, alors ...
                if (actu_Millis - prev_Millis_Classe[i] >= interval_2)  {
                    Classe_prev[i]=0;
                }
                else
                {
                    //***** CLIGNO *****//
                    // si l'ecart entre le temps présent et passé est superieur à 1/2 seconde, alors ...
                    if (actu_Millis - prev_Millis_Cligno[i] >= interval_1)  {
                        // on sauvegarde le temps présent comme temps passé, c-a-d on remet le compteur à zero :
                        prev_Millis_Cligno[i] = actu_Millis;
                        // on eteint la led
                        Classe_env[i] = 0;
                    }
                    else    {
                        // on affiche la led
                        Classe_env[i] = 1;
                    }
                }
            }
            // Dans le cas ou Classe[i] etait precedement allumé (+ 5 min), alors ...
            else {
                //La classe envoyé est la classe recu
                Classe_env[i] = Classe[i];
            }
        }
        // Si on demande à eteindre la led (Classe[i] = 1) alors ...
        else {
            // on indique que la classe precedente etait 1 (plutot que 0 pour préparer le clignotement futur)
            Classe_prev[i] = 1;
            // on enregistre la position temporel de classe actuelle qui sera la precedente lors d'un prochain allumage
            prev_Millis_Classe[i] = actu_Millis;
            //La classe envoyé est la classe recu
            Classe_env[i] = Classe[i];
            
        }
    }
    /*
     Envoi du signal apres traitement
     */
    // Pour chaque 74HC595, on envoi un signal de 8 octés. On regroupe donc ici les données de "Classe[*]" en 3 serie de 8 octés
    // donneA
    byte donneA = 0;
    for(int i = 0; i < 8; i++) {
        if(Classe_env[i]) {
            donneA = donneA | (1 << i); // A chaque octé on décale les données d'un cran
        }
    }
    // donneB
    byte donneB = 0;
    for(int i = 8; i < 16; i++) {
        if(Classe_env[i]) {
            donneB = donneB | (1 << (i-8));
        }
    }
    // donneC
    byte donneC = 0;
    for(int i = 16; i < 20; i++) {
        if(Classe_env[i]) {
            donneC = donneC | (1 << (i-16));
        }
    }
    // on ouvre le verrou
    digitalWrite(verrou, LOW);
    // on envoi les series d'octés en commancant par la dernière
    shiftOut(data, horloge, MSBFIRST, ~(donneC));
    shiftOut(data, horloge, MSBFIRST, ~(donneB));
    shiftOut(data, horloge, MSBFIRST, ~(donneA));
    // On ferme le verrou
    digitalWrite(verrou, HIGH);
    
    
    // Affichage sur le moniteur
    // Message recu
 //   Serial.print("message recu :");
    for (byte i = 0; i < 20; i++)   {
        Serial.print(ClasseZ[i]);
    }
    Serial.println();
    //Serial.print("message recu :");
    for (byte i = 0; i < 20; i++)   {
        Serial.print(Classe[i]);
    }
    Serial.println();
//    Serial.println();
//    // Classe precedante (-5min)
//    Serial.print("classe prev :");
//    for (byte i = 0; i < 20; i++)   {
//        Serial.print(Classe_prev[i]);
//    }
//    Serial.println();
//    // Message envoyé
//    Serial.print("message envoyé :");
//    for (byte i = 0; i < 20; i++)   {
//        Serial.print(Classe_env[i]);
//    }
    Serial.println();
} // Void
