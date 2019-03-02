#include <SoftwareSerial.h>

/*
int mp[8][3] = { //motor_pin each motor need 3 signal (PWM, Digital, Digital)
  {2, 22, 24},
  {6, 38, 40}, 
  {3, 26, 28},
  {7, 42, 44}, 
  {4, 30, 32}, 
  {8, 46, 48},
  {5, 34, 36},
  {9, 50, 52}}; 
*/

int mp[8][3] = { //motor_pin each motor need 3 signal (PWM, Digital, Digital)
  {2, 22, 24},
  {4, 30, 32},
  {6, 38, 40}, 
  {8, 46, 48},
  {3, 26, 28},
  {5, 34, 36},
  {7, 42, 44},  
  {9, 50, 52}}; 

  
int len;
char comm[100];
char ch;

int str2int(char *a, int len) {
   int sig  = 1, idx = 0, tmp = 0;
   if(a[0] == '-') sig = -1, idx = 1;
   while(idx < len && isDigit(a[idx])) tmp*=10, tmp+=(a[idx]-48), idx++;
   return sig*tmp;
}
void spset(int motor, int val) {
  Serial.println(String(motor)+String(" ")+String(val));
  if(val > 256) return;
  else if(val > 0) {
    digitalWrite(mp[motor][1], 1);
    digitalWrite(mp[motor][2], 0);
    analogWrite(mp[motor][0], val);
  }
  else if(val == 0) {
    analogWrite(mp[motor][0], 0);
    digitalWrite(mp[motor][1], 1);
    digitalWrite(mp[motor][2], 1);
    
  }
  else if(val > -256) {
    digitalWrite(mp[motor][1], 0);
    digitalWrite(mp[motor][2], 1);
    analogWrite(mp[motor][0], -val);
  }
  else return;
  
}

void deco() {
  if(comm[0] != '/') return;
  if(comm[1] == 'Z') { //control one by one
    spset(comm[2]-48, str2int(comm+3, len-4));
  }
  if(comm[1] == 'S') { //stop
    spset(0, 0);
    spset(1, 0);
    spset(2, 0);
    spset(3, 0);
    spset(4, 0);
    spset(5, 0);
    spset(6, 0);
    spset(7, 0);
    
  }
  if(comm[1] == 'W') {
    int mm = comm[2] - 48;
    spset(0, 80*mm);
    spset(2, 80*mm);
    
  }
  if(comm[1] == 'E') {
    int mm = comm[2] - 48;
    spset(1, -80*mm);
    spset(3, -80*mm);
    
  }
  if(comm[1] == 'X') {
    int mm = comm[2] - 48;
    spset(0, -80*mm);
    spset(2, -80*mm);
    
  }
  if(comm[1] == 'C') {
    int mm = comm[2] - 48;
    spset(1, 80*mm);
    spset(3, 80*mm);
    
  }
 if(comm[1] == 'A') { //left
    spset(0, 130);
    spset(1, 130);
    spset(2, -100);
    spset(3, -100);
  }
  if(comm[1] == 'F') { //right
    spset(0, -130);
    spset(1, -130);
    spset(2, 100);
    spset(3, 100);
  }
}

void setup() {
  Serial.begin(9600); //mega <=> computer
  Serial1.begin(38400); //mega <= NodeMCU
  pinMode(13, OUTPUT); //check signal 
  for(int i = 0; i < 8; i++) { //init motor digital pin
    pinMode(mp[i][1], OUTPUT);
    pinMode(mp[i][2], OUTPUT);
  }
  len = 0;
}

void loop() {
  if(Serial1.available()) {
    ch = Serial1.read();
    //Serial.print(ch);
    if(ch != 'b' && ch != '\'') {
      comm[len] = ch;
      len++;
      //Serial.print(ch);
    }
    if(ch == '<') {
      for(int i = 0; i < len; i++) Serial.print(comm[i]);
      Serial.println();
      deco();
      len = 0;

    }
  }
  delay(3);
}
