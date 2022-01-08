#define RMA 5   
#define RMR 3   
#define LMA 11  
#define LMR 6   

#define capG 4 
#define capM 7 
#define capD 8 

int zoneR = 0 ; 
int cG ;
int cD ;
int cM ;
int etat_prec ;

void setup() {

  pinMode(LMA, OUTPUT);
  pinMode(LMR, OUTPUT);
  pinMode(RMA, OUTPUT);
  pinMode(RMR, OUTPUT);
  pinMode(capG, INPUT);
  pinMode(capD, INPUT);
  pinMode(capM, INPUT);
  Serial.begin(9600);
   
}

void CheckCaps () {
  cG=digitalRead(capG);
  cD=digitalRead(capD);
  cM=digitalRead(capM);
}

void Forward(){
  analogWrite (LMA,85);
  analogWrite (LMR,0);
  analogWrite (RMA,80);
  analogWrite (RMR,0);

}

void ForwardVeryFast() { 
  analogWrite (LMA,140);
  analogWrite (LMR,0);
  analogWrite (RMA,125);
  analogWrite (RMR,0);
  delay(50);

}

void Backward() {
  analogWrite (LMA,0);
  analogWrite (LMR,80);
  analogWrite (RMA,0);
  analogWrite (RMR,70);

}

void Left () {
  analogWrite (LMA,0);
  analogWrite (LMR,20);
  analogWrite (RMA,55);
  analogWrite (RMR,0);
}

void Right () {
  analogWrite (LMA,65);
  analogWrite (LMR,0);
  analogWrite (RMA,0);
  analogWrite (RMR,0);

}

void Stop () {
  analogWrite (LMA,0);
  analogWrite (LMR,0);
  analogWrite (RMA,0);
  analogWrite (RMR,0);

}


void loop() {
  CheckCaps();
  Serial.print(cD);
  Serial.println(cM);
  Serial.print(cG);
  
  int a=0;
  

  Forward();

  if (!cG && !cM && !cD) {
    switch(etat_prec) {
    case 1: Left(); break;
    case 2: Right(); break;
}
}
  

  else if (!cG && !cM && cD) {
    Right();
    etat_prec=2;
  }

  else if (!cG && cM && !cD) {
    Forward();
  }
  
  else if (!cG && cM && cD) {
    Right();
    etat_prec=2;
  }
  else if (cG && !cM && !cD) {
    Left();
    etat_prec=1;
  }

  else if (cG && !cM && cD) {
    Backward();
    etat_prec=2;

  }

  else if (cG && cM && !cD) {
    Left();
    etat_prec=1;
  }
  else if (cG && !cM && !cD) {
    Left();
    etat_prec=1;
  }

  else if (cG && cM && cD) {
    if (a<2)
    {ForwardVeryFast();
    a++;}
    else 
      Forward();
  }
/*
  // If Middle = Black && Left = White && Right = White ==> Advance
  if (!cG && cM && !cD) {
    Forward();
  }
  // If Middle = White && Left = White && Right = White && Forward zone Red ==> Backward
  else if (!cG && !cM && !cD && !zoneR) {
    Stop();
  }
  // If Middle = White && Left = White && Right = White && After Red zone ==> Discontinuous line ==> Fast forward
  else if (!cG && !cM && !cD && zoneR) {
    ForwardVeryFast();
  }
  // If Middle = Black && Left = Black && Right = Black && Before red zone ==> Donkey back ==> Fast forward
  else if (cG && cM && cD && !zoneR) {
    ForwardVeryFast();
  }
  // If Middle = Black && Left = Black && Right = Black && After red zone ==> Donkey back ==> Fast forward
  else if (cG && cM && cD && zoneR) {
    Left();
   }
  // If Middle = White && Left = White && Right = Black ==> Turn right
  // If Middle = Black && Left = White && Right = Black ==> Turn Left
  else if ((!cG && !cM && cD) || (!cG && cM && cD)) {
    Right();
  }
    // If Middle = White && Left = Black && Right = White ==> Turn Left
    // If Middle = Black && Left = Black && Right = White ==> Turn Left
  else if ((cG && !cM && !cD) || (cG && cM && !cD)) {
    Left();
  }

}