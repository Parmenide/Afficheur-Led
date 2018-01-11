/*


   Afficheur Led - Recepteur

 
 TO DO
 - Changer les noms de variables
 - Corriger l'orthographe
 - Debug
 

*/

#include <VirtualWire.h>
//Broche du ATMEGA365 connectée au ST_CP du 74HC595
const int verrou = 11;
//Broche connectée au SH_CP du 74HC595
const int horloge = 12;
//Broche connectée au DS du 74HC595
const int data = 10;
// interval at which to blink (milliseconds)
const long interval_1 = 1000;
// interval at which to blink (milliseconds)
const long interval_2 = 5000;

void setup()
{
    
    // Initialisation de la bibliothèque VirtualWire
    vw_set_rx_pin(A0);
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
    byte Classe_prev[20];
    unsigned long prev_Millis_Classe;
    unsigned long prev_Millis_Cligno;
    //
    byte taille_Classe = sizeof(Classe);
    //
    vw_wait_rx();
    //
    if (vw_get_message((byte *) &Classe, &taille_Classe))
    {
        //
        for (byte i = 0; i < 20; i++)
        {
           /*
            Gestion du clognottement + affichage
          */
            //On active le verrou le temps de transférer les données ...
            digitalWrite(verrou, LOW);
            // on actualise une variable qui donne le temps présent
            unsigned long actu_Millis = millis();
            // Si on demande à afficher la led (Classe[i] = 1) alors ...
            if (Classe[i] = 1)
            {
                // Dans le cas ou Classe[i] etait precedement eteint, alors ...
                if (Classe_prev[i] = 0)
                {
                    // si l'ecart entre le temps présent et passé est superieur à 5 minutes, alors ...
                    if (actu_Millis - prev_Millis_Classe >= interval_2)
                    {
                        Classe_prev[i]=1;
                    }
                    else
                    {
                        //***** CLIGNO *****//
                        // si l'ecart entre le temps présent et passé est superieur à 1/2 seconde, alors ...
                        if (actu_Millis - prev_Millis_Cligno >= interval_1)
                        {
                            // on sauvegarde le temps présent comme temps passé, c-a-d on remet le compteur à zero :
                            prev_Millis_Cligno = actu_Millis;
                            // on inverse l'affichage de la led par rapport à son état précédent
                            // on envoie les informations au 74HC
                            envoi_74HC595(data, horloge, 1, !Classe[i]);
                        }
                        else
                        {
                            // on affiche la led
                            // on envoie les informations au 74HC
                            envoi_74HC595(data, horloge, 1, Classe[i]);
                        }
                    }
                }
                // Dans le cas ou Classe[i] etait precedement allumé (+ 5 min), alors ...
                else {
                    // on envoie directement les informations au 74HC
                    envoi_74HC595(data, horloge, 1, Classe[i]);
                }
            }
            // Si on demande à eteindre la led (Classe[i] = 0) alors ...
            else {
                // on indique que la classe precedente etait 0 (plutot que 1 pour préparer le clignotement futur)
                Classe_prev[i] = 0;
                // on enregistre la position temporel de classe actuelle qui sera la precedente lors d'un prochain allumage
                prev_Millis_Classe = actu_Millis;
                // on envoie les informations au 74HC
                envoi_74HC595(data, horloge, 1, Classe[i]);
            }
        // Dans tous les cas on renvoie les données reqceuillis dans le moniteur
        Serial.print(Classe[i]);
        digitalWrite(verrou, HIGH);
        }
    }
}

    


void envoi_74HC595(int dataPin, int clockPin, boolean sens, char donnee)
{
    //on va parcourir chaque bit de l'octet
    for(int i=0; i<24; i++)
    {
        //on met l'horloge à l'état bas
        digitalWrite(clockPin, LOW);
        //on met le bit de donnée courante en place
        if(sens) {
            digitalWrite(dataPin, donnee & 0x01 << i);
        }
        else {
            digitalWrite(dataPin, donnee & 0x8000 >> i);
        }
        //enfin on remet l'horloge à l'état haut pour faire prendre en compte cette dernière
        digitalWrite(clockPin, HIGH);
    }
}

 




 
 
 

