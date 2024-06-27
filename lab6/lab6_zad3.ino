#define LED_RED 11
#define LED_BLUE 10
#define LED_GREEN 9


void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
}
// Tablice z wartościami odpowiadającymi kolejnym kolorom tęczy
int red_color[7] = {0, 0, 0, 255, 255, 128, 0};
int green_color[7] = {255, 128, 0, 0, 255, 255, 255};
int blue_color[7] = {255, 255, 255, 255, 0, 0, 128};
int i = 0;

void loop() {
  analogWrite(LED_RED, red_color[i]);
  analogWrite(LED_BLUE, blue_color[i]);
  analogWrite(LED_GREEN, green_color[i]);
  delay(100);
  i = (i+1)%7;
  delay(1000);
}
