#include <Arduino.h>
#include <U8x8lib.h>


#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
//fonction pour i2c (reset,SDA,SCL)
U8X8_SSD1309_128X64_NONAME2_HW_I2C u8x8(9, A4, A5);

///////// Bouton/LED///////////
int bouton = 2;
int lastState = LOW;  // the previous state from the input pin
int etatBouton;    // the current reading from the input pin
unsigned long pressedTime  = 0;
unsigned long releasedTime = 0;
long pressDuration;
int led = 12;
int etatLed;

///////////Vitesse//////////////////

int sensor = 4;
int etatCapteur;
unsigned long start_time = 0;
unsigned long end_time = 0;
int nb_trous =1 ;// 1 aimant 
int steps=0;
float steps_old=0;
float temp=0;
int compt=0; // comptage initialisé à 0
float rps=0; // vitesse intialisée à 0
double rpm = 0;
double rpmmoyen = 0;
double somme;
int compteurTemps = 0;
char tab[9];
char tab2[9];
double rayonRoue=0.254;//metre
double kmh =0;
double kmhmoy = 0;

//déclaration des entrées 
void setup() 
{
  u8x8.begin();
  pinMode(bouton,INPUT_PULLUP); //en pullup interne à l'arduino 
  pinMode(sensor,INPUT_PULLUP); 
  pinMode(led,OUTPUT);
  Serial.begin(9600);
  //temps = millis(); // mesure du temps
}

//Fonction d'affichage de la barre ECOMET
//On définit la police on inverse les pixels 
void draw(void)
{
 u8x8.setFont(u8x8_font_amstrad_cpc_extended_f);
 u8x8.inverse(); // inverse les pixel voyant 
 u8x8.setCursor(0,0);
 u8x8.print("     ECOMET     ");
 u8x8.noInverse();
}

//Fonction de calcul de la vitesse 
void vitesse()
{
 etatCapteur = digitalRead(sensor);
 start_time=millis();
 end_time=start_time+1000;
 while(millis()<end_time)//reste dans la boucle pdt 1 seconde
 {
   if(digitalRead(sensor)==0)//compte le nombre de passage devant l'aimant
   {
    steps=steps+1; 
    while(digitalRead(sensor)==0)
    {
    }
   }
 }
    temp=steps-steps_old;//difference des passages 
    steps_old=steps;
    rps=(temp/nb_trous);//diviser par le nombre de passage pour un tour
    rpm = rps*60;
    kmh = rpm*2*3.1415*rayonRoue*60/1000;
}
//Fonction de calule vitesse moyenne
void vitesseMoy()
{
 somme = somme + rpm;
 compteurTemps = compteurTemps + 1;
 rpmmoyen = somme/(compteurTemps);
 kmhmoy = rpmmoyen*2*3.1415*rayonRoue*60/1000;
}

//Fonction de reset vitesse moyenne
//permet de remettre à zero la vitesse moyenne avant le départ en maintenant le bouton 1.5 secondes + signal LED quand c est bien reinitialise
void resetVmoy()
{
 etatBouton = digitalRead(bouton);

  if(lastState == 1 && etatBouton == 0)      //stockage du temps entre on et off pour faire la difference 
    pressedTime = millis();
  else if(lastState == 0 && etatBouton == 1) { 
    releasedTime = millis();

    pressDuration = releasedTime - pressedTime;
  }
  lastState = etatBouton;
  if(pressDuration >1500)//temps de pressage
  {
    somme = 0;
    compteurTemps = 0;
    pressDuration = 0;
    digitalWrite(led,HIGH);
    while(rpm == 0.0) // tant que la vitesse est nulle on ne recalcule pas la vitesse moyenne
    {
      somme = 0;
      compteurTemps = 0;
      rpmmoyen = 0;
      affichage();
      vitesse();
    }
    digitalWrite(led,LOW);
  }
}

//Fonction d'affichage sur l'écran
void affichage()
{   
    u8x8.setCursor(0,2);
    u8x8.print("Vit:");
    tab[8] = '\0'; // formatage
    dtostrf(rpm,8,2,tab);
    //dtostrf(kmh,8,2,tab);
    u8x8.print(tab);
    
    u8x8.setCursor(0,5);
    u8x8.print("Vmoy:");
    tab2[8] = '\0'; // formatage
    dtostrf(rpmmoyen,7,2,tab2);
    //dtostrf(kmhmoy,7,2,tab2);
    u8x8.print(tab2);
}
//main
void loop()
{
 draw();
 vitesse(); 
 resetVmoy();
 vitesseMoy();
 affichage();
}
