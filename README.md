
# AFFICHEUR-LED

Un afficheur à diodes électroluminescentes pour faciliter l'appel et la consultation de classes dans une cour d'établissement scolaire.


## Description :

Cet afficheur à diodes electroluminescentes a pour fonction de fournir au service de vie scolaire d'un collège un support de communication simplifié avec les élèves, en particulier pour l'appel des classes à la cantine ou au réfectoire. Celui-ci par ailleurs, offre aux élèves un moyens aisé de se rapporter aux informations communiquées.
L'appareil affiche alors les classes souhaitées relativement à un tableau de commande qui transmet par radio-fréquences l'appel effectué.
Les classes appelées sont affichées en rouge et clignotent pendant 5 minutes avant de se stabiliser. Cela afin de distinguer les classes les plus recemments appelées.

## Périphériques :

* Afficheur à diodes electroluminescentes
* Tableau de commande


## Caractéristiques techniques :

 • | Afficheur | Tableau de commande
------------ | ------------ | -------------
Tension de fonctionnement | 220v             | 220v
Consommation minimal      | 3 A              | 1 A
Consommation maximal      | 4 A              | 2 A
Dimensions                | 1300mm/60mm/30mm | 200mm/150mm/50mm
Emission/réception min.   | 100m             | 100m
Emission/réception max    | 100m             | 100m


## Composition matérielle :

* Afficheur
	* 777x leds 620\~625nm, 150~200mcd, 1.8\~2.2v, 20mA. 
	* 5x Panneaux MDF, A3, épaisseur : 3mm.
	* 1x L7805
	* 2x SN74HC595
	* 20x P2N2222A
	* 10x Connecteur xxxxxxx
	* 1x PCB prototype 90mm/40mm
	* 1x Cable étamé 26 AWG ≈20m
	* 1x Arduino-pro-mini 5V (ATMEGA 328)
	* 1x Récepteur RF 440mhz(HCN67)
	* 1x Antenne (170mm)
	* 200x Resistances 220Ω
	* 1x Transformateur AC/DC, 12V, 5A

* Tableau de commandes
	* 20x led 620~625nm, 150\~ 200mcd, 1.8\~ 2.2v, 20mA. 
	* 1x Arduino-pro-mini 5V (ATMEGA 328)
	* 2x Panneaux MDF, A3, épaisseur : 3mm.
	* 1x L7805
	* 2x CD4051
	* 20x Interupteur (MTS 101)
	* 1x PCB prototype 90mm/40mm
	* 1x Cable étamé 26 AWG ≈1m
	* 1x Récepteur RF 440mhz(HCN67)
	* 1x Antenne (170mm)
	* 1x Transformateur AC/DC, 5V, 500mA


## Procédure d'utilisation : 


## Sécurité et normes :

## Notes complementaires :
Cet afficheur fut concu avec les moyens techniques à disposition, à savoir une decoupeuse laser Trotec XXXXX pour le recouvrement qui contraint à une surface de découpe de la taille d'un A3 maximum.
Du coté electronique, là aussi le manque de moyens ont conduit à des choix specifiques. Ainsi, par manque de moyens de gravure de plaque de cuivre, le choix d'utiliser des cartes de prototypage et des modules plutôt que des composants pour ce qui est de l'AT-MEGA et des radios-transmeteurs.
L'afficheur serait alors surement d'autant mieux concu s'il pouvait ne pas etre soumis aux contraintes precedement evoquées et donc permettre la decoupe d'une pieces des faces de l'afficheurs, ainsi que de proposer un circuit ou typon plus aboutit pour l'electronique.

Pour plusieurs autres raisons diverses, il fut choisis de composer des lettres et chiffres par plusieurs leds juxtaposées. Ce choix conduit à de lourdes opperations de fabrication. De plus, il n'est pas sans augmenter le risque de defaillance du systeme complet puisque, chaque led (777 au total) est portentiellement sujette à un risque de defaillance. Reflexhir à un systeme moins complexe mais tout aussi efficace serait alors surement souhaitable avant quelconque reproduction.
