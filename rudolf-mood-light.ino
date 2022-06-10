#include <DHT11.h>
#define dhtpin A0
DHT11 dht(dhtpin);
void setColor(int red, int blue);

int R = 11;
int G = 10;
int B = 9;

int cal;
int redValue;
int blueValue;
int last_redValue;
int last_blueValue;

float humidity;
float temperature;
float last_temperature;

void setup() {
Serial.begin(9600);
pinMode(R, OUTPUT);
pinMode(G, OUTPUT);
pinMode(B, OUTPUT);

//////////////// 초기값은 빨간코
last_redValue = 0;
last_blueValue = 255;
last_temperature = 20;
setColor(last_redValue, last_blueValue);
delay(200);
////////////////
}

void loop(){
dht.read(humidity, temperature);
Serial.print("temperature : ");
Serial.println(temperature);
delay(500);

////////////////////////// 온도 20 이상일 때 빨간불
if(temperature>=20){
  redValue = 0;
  blueValue = 255 - redValue;
}
////////////////////////// 온도 16 이하일 때 파란불
else if (temperature<16){
  redValue = 255;
  blueValue = 255 - redValue;
}

////////////////////////// 온도 16~20일 때 보라불
else if (temperature>=16 && temperature<16.5) {
  redValue = 224;
  blueValue = 255 - redValue;
}
else if (temperature>=16.5 && temperature<17) {
  redValue = 192;
  blueValue = 255 - redValue;
}
else if (temperature>=17 && temperature<17.5) {
  redValue = 160;
  blueValue = 255 - redValue;
}
else if (temperature>=17.5 && temperature<18) {
  redValue = 128;
  blueValue = 255 - redValue;
}
else if (temperature>=18 && temperature<18.5) {
  redValue = 96;
  blueValue = 255 - redValue;
}
else if (temperature>=18.5 && temperature<19) {
  redValue = 64;
  blueValue = 255 - redValue;
}
else if (temperature>=19 && temperature<20) {
  redValue = 32;
  blueValue = 255 - redValue;
}


////////////////////// 이전값과 다를 때
if (temperature != last_temperature){
Serial.print("temperature : ");
Serial.println(temperature);

if ( temperature < last_temperature){ // 점점 파래진다
while(1){
      if((redValue==last_redValue)||(blueValue==last_blueValue)) break;
      last_redValue++;
      last_blueValue--;
      setColor(last_redValue, last_blueValue);
      delay(10);
}
    Serial.println("I am blue");
}

else if(temperature > last_temperature){ // 점점 빨개진다
while(1){
      if((redValue==last_redValue)||(blueValue==last_blueValue)) break;
      last_redValue--;
      last_blueValue++;
      setColor(last_redValue, last_blueValue);
      delay(10);
}
    Serial.println("I am red");
}
}

last_temperature = temperature;
last_redValue = redValue;
last_blueValue = blueValue;
delay(100);
}

void setColor(int red, int blue)
{
  analogWrite(R, red);
  analogWrite(G, 255);
  analogWrite(B, blue); 
}
