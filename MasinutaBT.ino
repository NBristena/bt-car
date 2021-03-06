int thr, dir;
char cmd[100];
int cmdIndex;
int x,y,d1,d2;

int stgFront = 3;
int stgBack = 5;
int drFront = 9;
int drBack = 6;

void setup() {
    delay(500);
    Serial.begin(115200);
  
    pinMode(stgFront,OUTPUT); //Motor1
    pinMode(stgBack,OUTPUT); //Motor1
    pinMode(drFront,OUTPUT); //Motor2
    pinMode(drBack,OUTPUT); //Motor2
}

void loop() {
    BT();
}

/**************************************************************************************
 * Functia cmdStartsWith compara comanda transmisa prin bluetooth cu un string dat st *
 **************************************************************************************/
boolean cmdStartsWith(char *st) {
    for(int i = 0; ; i++) {
        if(st[i] == 0) return true;
        if(cmd[i] == 0) return false;
        if(cmd[i] != st[i]) return false;
    }
    return false;
}

/*********************************************************************************
 * Functia BT foloseste functiile de citire si interpretare a comenzilor primite *
 *********************************************************************************/
void BT(){
    btRead();
    d2 = x + y;
    d1 = x - y;
    viteza( d1, d2);
}

/****************************************************************************************
 * Functia btRead citeste caractere de la bluetooth si interpreteaza directia comandata *
 ****************************************************************************************/
void btRead(){
    if(Serial.available()) {
        char c = (char)Serial.read();
        if(c == '\n') {
            cmd[cmdIndex] = 0;
                  
            if( cmdStartsWith("x ") ){
                x = atoi(cmd + 2);
                Serial.print("$");
            }
            if( cmdStartsWith("y ") )
                y = atoi(cmd + 2);
            cmdIndex = 0;
        }
        else {      
            cmd[cmdIndex] = c;
            if(cmdIndex < 99) 
                cmdIndex++;
        }
    }
}

/**************************************************************************
 * Functia viteza seteaza directa in care motoarele trebuie sa se invarta *
 **************************************************************************/
void viteza(int dr, int stg){
    if(dr >= 0){
        digitalWrite(drBack,0);
        analogWrite(drFront,dr);
    }
    else{
        digitalWrite(drFront,0);
        analogWrite(drBack,-dr);
    }
    if(stg >= 0){
        digitalWrite(stgBack,0);
        analogWrite(stgFront,stg);
    }
    else{
        digitalWrite(stgFront,0);
        analogWrite(stgBack,-stg);
    }
}
