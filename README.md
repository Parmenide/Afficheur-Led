
# AFFICHEUR-LED



## Description :

Cet afficheur à led à pour fonction de fournir au service de vie scolaire d'un collège un support de communication simplifié avec les élèves, en particulier pour l'appelle des classes à la cantine ou au réfectoire. Celui-ci par ailleurs, offre aux élèves un moyens aisé de se rapporter aux informations communiquées.
L'appareil affiche alors les classes souhaité relativement à un tableau de commande qui transmet par radio-fréquence l'appelle effectué.
Les classes appelées sont affichées en rouge et clignotent pendant 5 minutes avant de se stabiliser. Cela afin de distinguer les classes appelées en dernières des classes déjà appelées depuis un certain temps.

## Périphériques :

* Afficheur à led (+ transformateur AC/DC)
* Tableau de commande


## Caractéristiques techniques :

                          | Afficheur        | Tableau de commande
------------ | ------------ | -------------
Tension de fonctionnement | 220v             | 220v
Consommation minimal      | 3 A              | 1 A
Consommation maximal      | 4 A              | 2 A
Dimensions                | 1300mm/60mm/30mm | 200mm/150mm/50mm
Emission/réception min.   | 100m             | 100m
Emission/réception max    | 100m             | 100m


## Composition matériel :

* Afficheur
	* 777x leds 620~625nm, 150~200mcd, 1.8~2.2v, 20mA. 
	* 5x Panneaux MDF, A3, épaisseur : 3mm.
	* 1x L7805
	* 2x SN74HC595
	* 20x P2N2222A
	* 10x Connecteur xxxxxxx
	* 1x PCB prototype 90mm/40mm
	* 1x Cable étamé 26 AWG ~20m
	* 1x Arduino-pro-mini 5V (ATMEGA 328)
	* 1x Récepteur RF 440mhz(HCN67)
	* 1x Antenne (170mm)
	* 200x Resistances 220Ω
	* 1x Transformateur AC/DC, 12V, 5A

* Tableau de commande
	* 20x leds 620~625nm, 150~200mcd, 1.8~2.2v, 20mA. 
	* Arduino-pro-mini 5V (ATMEGA 328)
	* 2x Panneaux MDF, A3, épaisseur : 3mm.
	* 1x L7805
	* 2x CD4051
	* 20x Interupteur (MTS 101)
	* 1x PCB prototype 90mm/40mm
	* 1x Cable étamé 26 AWG ~1m
	* 1x Récepteur RF 440mhz(HCN67)
	* 1x Antenne (170mm)
	* 1x Transformateur AC/DC, 5V, 500mA


## Procédure d'utilisation : 


## Sécurité et normes :


## Sources et liens externes :

	L'enssemble de ces documents sont en acces libre sur une plateforme communautaire : http://github.com/Parmenide/Afficheur-Led-Collège
