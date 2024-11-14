void setup(){
  
  // This is a simple program
  int countSimpleProgram = 0;
  int startSimpleProgram = millis();
  
  for(int i = 2; i < pow(10, 6); i++){
    if(isPrimeNumber(i)){
      countSimpleProgram++;
    }
  }

  int endSimpleProgram = millis();
  
  println("This is a simple program");
  println("Number of prime number from 2 to 1 million is " + countSimpleProgram);
  println("Calculate time is " + (endSimpleProgram - startSimpleProgram) + " ms");
  println("");
  
  // This is a program using the sieve of Eratosthenes
  int countEratosthenesProgram = 0;
  boolean[]checkPrimeNumberArray = new boolean[1000001];
  int num  = 2;
  int startEratosthenesProgram = millis();
  
  for(int i = 0; i < 1000000 + 1; i++){
    checkPrimeNumberArray[i] = true;
  }
  
  while(num <= 1000000){
    if(checkPrimeNumberArray[num] == true){
      countEratosthenesProgram++;
    
      for(int j = 2; num* j <= 1000000; j++){
        checkPrimeNumberArray[num * j] = false;
      }
    }
    num++;
  }
  
  int endEratosthenesProgram = millis();
  
  println("This is a Eratosthenes program");
  println("Number of prime number from 2 to 1 million is " + countEratosthenesProgram);
  println("Calculate time is " + (endEratosthenesProgram - startEratosthenesProgram) + " ms");
  
}

boolean isPrimeNumber(int num){
  for(int i = 2; i < num; i++){
    if(num % i == 0){
      return false;
    }
  }
  
  return true;
}
