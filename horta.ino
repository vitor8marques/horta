//Carrega a biblioteca do RTC DS1307
#include <DS1307.h>

//Modulo RTC DS1307 ligado as portas A4 e A5 do Arduino 
DS1307 rtc(A4, A5);

#include <Servo.h>

Servo myservo;  // cria o objeto para controle do servo
// twelve servo objects can be created on most boards

int pos = 0; //variavel para armazenar a posição do servo
int regado=0;
int menu=1;//variavel da tela do menu
String R1="10:00:00",R2="16:00:00";
void setup()
{
  //Aciona o relogio
  rtc.halt(false);
  
  //As linhas abaixo setam a data e hora do modulo
  //e podem ser comentada apos a primeira utilizacao
  
  //rtc.setDOW(FRIDAY);      //Define o dia da semana
  //rtc.setTime(18,37, 25);     //Define o horario
 // rtc.setDate(6, 7, 2018);   //Define o dia, mes e ano
  
  //Definicoes do pino SQW/Out
  rtc.setSQWRate(SQW_RATE_1);
  rtc.enableSQW(true);
  
  Serial.begin(9600);
  pinMode(A0,OUTPUT);

}

void loop()
{
  //Mostra as informações no Serial Monitor
  
  /*Serial.print("Hora : ");
  Serial.print(rtc.getTimeStr());
  Serial.print(" ");
  Serial.print("Data : ");
  Serial.print(rtc.getDateStr(FORMAT_SHORT));
  Serial.print(" ");
  Serial.println(rtc.getDOWStr(FORMAT_SHORT));
  */
  String hora= rtc.getTimeStr();
  //Serial.println(hora);
  if(((hora==R1)|| (hora==R2) )&& regado==0){

    molhar(3);
   Serial.println("plantas regadas");
  }else{regado=0;}

    //Aguarda e repete o processo
  delay (100);

  exibir_menu();
}

void exibir_menu(){
  if(menu==1){
  Serial.println("ferramenta para automaizaçao de rega de hortas");  
  Serial.print("Hora do sistema : ");
  Serial.print(rtc.getTimeStr());
  Serial.print(" ");
  Serial.print("Data do sistema : ");
  Serial.print(rtc.getDateStr(FORMAT_SHORT));
  Serial.print(" ");
  Serial.println(rtc.getDOWStr(FORMAT_SHORT));
  Serial.print("Proximas regas: ");
  Serial.print(R1);
  Serial.print(" e ");
  Serial.println(R2);
  Serial.println("Opçoes :");
  Serial.println("r -> efetua a rega das pantas");
  Serial.println("o -> exibe este menu");
  menu=0;
  }
  if (Serial.available())  //verifica se tem dados diponível para leitura
  {
    byte byteRead = Serial.read(); //le bytwe mais recente no buffer da serial
    switch (byteRead) {
      case 'r':
        {molhar(3);Serial.println("Plantas regadas");menu=1;}
      break;
      case 'h':
        {Serial.println("Ajuste de horas ainda nao disponivel");menu=1;}
      break;
       case 't':
        {Serial.println("Modo teste, plantas serão regadas em 5s");//delay(5000);
delay(5000);

     myservo.attach(9);
    myservo.write(0);
   myservo.detach();
    digitalWrite(A0,1);
    delay(3000);
   digitalWrite(A0,0); 
        Serial.println("Plantas regadas");menu=1;}
      break;
      case 'o':
        {menu=1;}
      break;
      default:
      {Serial.println("comnado inválido"); menu=1;}
}
    

  }
  }
void molhar(int ciclos){

    digitalWrite(A0,1);//liga a agua
  myservo.attach(9);

 int j=0;
 for(j=0;j<ciclos;j++){

  for (pos = 20; pos <= 90; pos += 1) { // faz o servo girar para molhar as plantas
    // in steps of 1 degree
    myservo.write(pos);              
    delay(23);                       
  }
  
  for (pos = 90; pos >= 20; pos -= 1) { // faz o servo girar para molhar as plantas
    myservo.write(pos);              
    delay(23);                      
  }

  
 

 }
   myservo.detach();//desliga o servo
  regado=1;//indica qeu as plantas foram regadas
   digitalWrite(A0,0); //desliga a água
}
