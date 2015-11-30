const int violin1Pin = 8;
const int violin2Pin = 9;
const int celloPin = 10;

// Length must equal the total number of notes and spaces 
const int songLength = 411; //manually counting size....
// 1000 = 1 second. Do the math.
int tempo = 990;
boolean playSong = true;
boolean repeat = false;


// p q  0 1 2  3 4  5 6 7  8 9  a b  c d  e  f g  h i j  k l  m n  o
// A A# B c c# d d# e f f# g g# a a# b c1 c# d d# e f f# g g# a a# b

char song[] = {' ','7','a','f',' ','5','a','e',' ','3','7','c',' ','2','7','a',' ','0','3','8',' ','3','7','a',' ','3','8','c',' ','5','a','e',//2 measures
               ' ','7','a','f',' ','5','a','e',' ','3','7','c',' ','2','7','a',' ','0','3','8',' ','3','7','a',' ','3','8','c',' ','5','a','e',
               ' ','7','a','f',' ','5','a','e',' ','3','7','c',' ','2','7','a',' ','0','3','8',' ','3','7','a',' ','3','8','c',' ','5','a','e',
               ' ','7','a','f',' ','5','a','e',' ','3','7','c',' ','2','7','a',' ','0','3','8',' ','3','7','a',' ','3','8','c',' ','5','a','e',
               ' ','7','a','f',' ','5','a','e',' ','3','7','c',' ','2','7','a',' ','0','3','8',' ','3','7','a',' ','3','8','c','a','5','2',' ',//2 measures, end of first section
               
               '3','7','a','8','7','3','7','5','3','0','3','a','8','c','a','8',
               '7','3','5','e','f','j','m','a','c','8','a','7','3','f','f','e',
               'f','e','f','3','2','a','5','7','3','f','e','c','e','j','m','o','k','j','h','k','j','h','f','e','c','a','8','7','5','8','7','5',//two measures
               '3','5','7','8','a','5','a','8','7','c','a','8','a','8','7','5','3','0','c','e','f','e','c','a','8','7','5','c','a','c','a','8',
               '7','5','7','8','a','5','a','8','7','c','a','8','a','8','7','5','3','0','c','e','f','e','c','a','8','7','5','c','a','c','a','a',
               '3','7','a','8','7','3','7','5','3','0','3','a','8','c','a','8',//two
               'f','3','5','7','3','2','e','f','h','e','c','0','2','3','0','2','a','8','7','5',//one measure
               '3','8','7','5','8','7','3','5','7','a','8','c','a','8','7','5','a','8','7','5','R',//repeat'','','','','','','','','','','','','','','','','','','','','','','','',
               
               ' ','7','a','f',' ','5','a','e',' ','3','7','c',' ','2','7','a',' ','0','3','8',' ','3','7','a',' ','3','8','c',' ','5','a','e',
               ' ','7','a','f',' ','5','a','e',' ','3','7','c',' ','2','7','a',' ','0','3','8',' ','3','7','a',' ','3','8','c','a','5','2','p','3'};
                
//      0 1  2 3 4  5 6  7 8 9  a b  c d  e f  g  h i  j k l  m n  o p  q
//      a a# B c c# d d# e f f# g g# a a# b c1 c# d d# e f f# g g# a a# b


//'','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','',

int beats[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //2 measures
               2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
               2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
               2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
               2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,//end of first section
               
               3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
               3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
               2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,//two measures
               2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
               2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
               3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, //two
               2, 1, 1, 2, 2, 2, 1, 1, 2, 2, 2, 1, 1, 2, 2, 2, 1, 1, 2, 2,
               2, 1, 1, 2, 2, 2, 1, 1, 2, 2, 2, 1, 1, 2, 2, 2, 1, 1, 2, 2, 0,//repeat
               
               2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
               2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
               


void setup() 
{
  pinMode(violin2Pin, OUTPUT);
  pinMode(celloPin, OUTPUT);
  pinMode(violin1Pin, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  int buttonState;
  buttonState = digitalRead(violin1Pin);
  
  if(buttonState == LOW)
  {
    playSong = true;
  }
  else if(buttonState == HIGH)
  {
    playSong = false;
  }
  else if(buttonState == 0)
  {
    playSong = true;
  }

  if(playSong == false){
    playsong();
  }
  else{
    Serial.print(" ");
  }
  

}

void playsong(){
  int i, duration;
  for (i = 0; i < songLength; i++) // step through the song arrays
    {
      if (beats[i] == 4)
      {
        duration = tempo;
      }
      else if (beats[i] == 3)
      {
        duration = tempo / 2;
      }
      else if (beats[i] == 2)
      {
        duration = tempo / 4;
      }
      else if (beats[i] == 0)
      {
        duration = 0;
      }
      else
      {
        duration = tempo / 8;
      }

    
      if (song[i] == ' ')          // is this a rest? 
      {
        delay(duration);
        Serial.print("Resting");      // then pause for a moment
      }
      else if(song[i] == 'R' && repeat == false)
      {
        repeat = true;
        i = 159;
      }
      else                          // otherwise, play the note
      {
        tone(violin2Pin, frequency(song[i]), duration);
        Serial.println(i);
        delay(duration);            // wait for tone to finish
      }
      delay(10);              // brief pause between 
    
  }
  // We only want to play the song once, so we'll pause forever:
 // while(true){}
  
  playSong = false;
}



char names[] = {'p','q','0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o'};
int frequencies[] = {220,233,247,262,277,294,311,330,349,370,392,415,440,466,494,523,554,587,622,659,698,740,784,831,880,932,988};

 // This function takes a note character (a-g), and returns the
 // corresponding frequency in Hz for the tone() function.
int frequency(char note) 
{
  int i;
  const int numNotes = 27;  // number of notes we're storing

  for (i = 0; i < numNotes; i++)  // Step through the notes
  {
    if (names[i] == note)         // Is this the one?
    {
      return(frequencies[i]);     // Yes! Return the frequency
    }
  }
  return(0);  // We looked through everything and didn't find it,
              // but we still need to return a value, so return 0.
}
