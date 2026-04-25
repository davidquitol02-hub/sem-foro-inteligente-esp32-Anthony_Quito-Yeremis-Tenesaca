
const int ledRojo = 25;
const int ledAmarillo = 26;
const int ledVerde = 27;
const int boton = 4;

volatile int contador = 0;
int estado = 0;

hw_timer_t *timer = NULL;

void IRAM_ATTR onTimer() {
  contador++;
}

void setup() {
  pinMode(ledRojo, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledVerde, OUTPUT);

  pinMode(boton, INPUT); 

  timer = timerBegin(1000000);
  timerAttachInterrupt(timer, &onTimer);
  timerAlarm(timer, 1000000, true, 0);
}

void loop() {

  int vehiculo = digitalRead(boton); 

  if (estado == 0) { 

    digitalWrite(ledRojo, LOW);
    digitalWrite(ledAmarillo, LOW);

    int tiempoVerde;

    if (vehiculo == HIGH) {  
      analogWrite(ledVerde, 255);
      tiempoVerde = 8;
    } else {                  
      analogWrite(ledVerde, 127);
      tiempoVerde = 5;
    }

    if (contador >= tiempoVerde) {
      contador = 0;
      estado = 1;
    }

  } else if (estado == 1) { 

    analogWrite(ledVerde, 0);
    digitalWrite(ledRojo, LOW);
    digitalWrite(ledAmarillo, HIGH);

    if (contador >= 2) {
      contador = 0;
      estado = 2;
    }

  } else if (estado == 2) { 

    analogWrite(ledVerde, 0);
    digitalWrite(ledAmarillo, LOW);
    digitalWrite(ledRojo, HIGH);

    if (contador >= 5) {
      contador = 0;
      estado = 0;
    }
  }
}