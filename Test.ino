String roundTime = "07";
String difficulty;
String comb;
String allData;
String score;
int total;
int correct = 0;
int guess;
int rightAnswer = 3;
int roundTimeMils = 7000;

String real;
bool dataRecieved;
void setup() {
  Serial.begin(115200);  //initial the Serial
  Serial.setTimeout(0);
}

void loop() {
  //dataRecieved = false;
  if (Serial.available())  {

    allData = Serial.readString();
    roundTime = allData.substring(1, 3);
    difficulty = allData.charAt(3);
    dataRecieved = true; total = 0; correct = 0;
    roundTimeMils = roundTime.toInt()*1000;    
  }

guess = random(1, 6);
if (guess == rightAnswer) {
  correct+= 1;
}

    delay(roundTimeMils);
    ++total;
    //correct = 0;
    score = String(correct) + "/" + String(total);
   
      Serial.print(score);
    
   
}
