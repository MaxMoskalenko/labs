bool isCharInArray(char symb, char array[], int arrayLength){
	for(int i =0; i< arrayLength; i++){
    	if(array[i] == symb)
          return true;
    }
  return false;
}

int resolve(char line[]){
	char alph[] = {'A', 'B', 'C', 'E', 'H', 'K', 'M', 'O', 'P', 'T', 'X', 'Y'};
  	char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7','8', '9'};
  	bool isExists = true;

  	if(!isCharInArray(line[0], *alph, 12))
      isExists = false;
    if(!isCharInArray(line[1], *digits, 10))
      isExists = false;
    if(!isCharInArray(line[2], digits, 10))
      isExists = false;
    if(!isCharInArray(line[3], digits, 10))
      isExists = false;
    if(!isCharInArray(line[4], alph, 12))
      isExists = false;
    if(!isCharInArray(line[5], alph, 12))
      isExists = false;

    if(isExists)
      return 100;
  	
  	int numberOfLetters = 0;
  	for(int i =0; i<6; i++){
      if(line[i] <= 132 || line[i] >= 101)
        numberOfLetters++;
    }
  return numberOfLetters;
}

