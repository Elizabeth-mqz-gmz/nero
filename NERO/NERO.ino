#define AIN1 4 //LLANTA derecha (ADELANTE)
#define AIN2 2 //ATRÁS
#define PWMA 3
#define STBY 5
#define BIN1 7 //LLANTA IZQUIERDAOO
#define BIN2 6
#define PWMB 9
#define SENSOR0 A0 //DERECHO
#define SENSOR1 A1 //IZQUIERDO
int valorInfra1=0, valorInfra2=0, velocidad1=500, velocidad=0; //VARIABLES PARA GUARDAR LECTURAS DE SENSORES

void carroEstado (int a1, int a2, int b1, int b2){
  digitalWrite(AIN1, a1);
  digitalWrite(AIN2, a2); 
  digitalWrite(BIN1, b1); 
  digitalWrite(BIN2, b2);
}

void setup() {
  for(int i=3; i<=10; i++)
    pinMode(i,OUTPUT);

}

void loop() {
      digitalWrite(STBY, HIGH); //ACTIVAR MOTORES
  
      //ASIGNAR LECTURAS DE SENSORES A VARIABLES
      valorInfra1 = (analogRead(SENSOR0) > 150)? 1 : 0 ;
      valorInfra2 = (analogRead(SENSOR1) > 150)? 1 : 0 ;
      
      velocidad = (valorInfra1 == valorInfra2) ? velocidad1 : 65; //LA VELOCIDAD CAMBIA CUANDO DEBE GIRAR 
      analogWrite(PWMA, velocidad);// Velocidad A
      analogWrite(PWMB, velocidad);//Velocidad B7
      
      if (valorInfra1 == 0 && valorInfra2 == 0){ //AMBOS ESTÁN EN NEGRO
        carroEstado (0,0,0,0);
      } else if (valorInfra1 == 1 && valorInfra2 == 0){
        while (valorInfra1 == 1 && valorInfra2 == 0){
          analogWrite(PWMA, 100);
          analogWrite(PWMB, 65);
          carroEstado (1,0,0,1);
          valorInfra2 = (analogRead(SENSOR1) > 100)? 1 : 0 ;
        }//GIRA IZQUIERDA
      } else if (valorInfra1 == 0 && valorInfra2 == 1){
          while (valorInfra1 == 0 && valorInfra2 == 1){
            analogWrite(PWMA, 65);
            analogWrite(PWMB, 100);
            carroEstado (0,1,1,0);
            valorInfra1 = (analogRead(SENSOR0) > 100)? 1 : 0 ;
          } //GIRA DERECHA 
      } else //AVANZA
        carroEstado (1,0,1,0); 
      delay(100);
  }
