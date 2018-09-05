/*
UERJ - Software Embarcado (Professor Francisco Sant'Anna)
Thalita de Almeida Cannavezes
Data: 03/09/2018
*/
const int but1 = 2; //declara constante do botao 1 para pino 2
const int but2 = 4; //declara constante do botao 2 para pino 4
const int ledPin = 12; //declara constante do led
int ledState = 0; // estado do led
int stopBlink = 0; //define a parada do led
int loop1 = 0; // utilizada para congelar atualização do button1Millis
int loop2 = 0; // utilizada para congelar atualização do button2Millis
unsigned long previousMillis = 0; // tempo inicial
unsigned long button1Millis = 0; // tempo do pressionamento do botao 1
unsigned long button2Millis = 0; // tempo do pressionamento do botao 2
int interval = 1000; // intervalo do blink
int button1State = 0; // estado do botao 1
int button2State = 0;// estado do botao 2
unsigned long lastDebounceTime = 0;  // a ultima vez que o pino de saida foi alterado
unsigned long debounceDelay = 50;    // o tempo de debounce aumenta se a saida piscar

 void setup()
 {
  pinMode(ledPin, OUTPUT); // define led como output
  pinMode(but1, INPUT); // define botao do pino 2 como input
  pinMode(but2, INPUT); // define botao do pino 4 como input
  Serial.begin(9600);
 }
 void loop() {
  unsigned long currentMillis = millis(); // guarda tempo atual
  int button1State = digitalRead(but1); // le pino 2 para saber se botao 1 foi pressionado
  int button2State = digitalRead(but2); // le pino 4 para saber se botao 2 foi pressionado

  if ((button1State != button1State) || (button2State != button2State)) // Se o interruptor mudou, devido a ruído ou pressão

    {
    // reseta o tempo da variavel de registro da ultima vez que ocorreu o debounce
    lastDebounceTime = millis();
   }
   if ((millis() - lastDebounceTime) > debounceDelay) {
    // Seja qual for a leitura, esta la ha mais tempo que o debounce
  
  if (stopBlink == 0 && currentMillis - previousMillis >= interval){ // teste do intervalo de tempo para definir se pisca ou nao
     previousMillis = currentMillis; // registra tempo inicial
     
    // inverte estado do led
    if (ledState == LOW) {
     ledState = HIGH;
    } else {
    ledState = LOW;
    }
    digitalWrite(ledPin, ledState); // escreve estado do led na saida correspondente
  }
  }    
   //acelera pisca-pisca e guarda o tempo do pressionamento do botao
    if (button1State == HIGH){
      if (loop1 == 0){
        button1Millis = millis();
        loop1 = 1;
      if (interval >= 200){
        interval = interval - 100;
      }
      }
    }
 
      else{
        loop1 = 0;
        button1Millis = 0;
      }
          
 // desacelera pisca-pisca e guarda o tempo do pressionamento do botao
    if (button2State == HIGH){
      if (loop2 == 0){
        button2Millis = millis();
        loop2 = 1;
      if (interval <= 900){
        interval = interval + 100 ;
      }
      }
    }
        else{
          loop2 = 0;
          button2Millis = 0;
        }
  //Serial.println (interval);
 
 // para o pisca-pisca se o intervalo entre o pressionamento dos botoes for menor de 500ms
    if (button1State == HIGH && button2State == HIGH ){
      if (button1Millis - button2Millis < 500 || button2Millis - button1Millis < 500){
        if (stopBlink == 0){
          stopBlink = 1; // inibe o pisca-pisca
          button1Millis = 0;
          button2Millis = 0;
          digitalWrite(ledPin, HIGH);
        }
          else{
          stopBlink = 0; // habilita o pisca-pisca
          digitalWrite(ledPin, HIGH);
          }
      }

//delay(10);
  
}
}
