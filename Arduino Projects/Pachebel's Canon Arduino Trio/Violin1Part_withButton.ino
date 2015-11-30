
const int violin1Pin = 8;
const int buttonPin = 6;

// Length must equal the total number of notes and spaces 
const int songLength = 384;

double tempo = 1000;
boolean playSong = false;


//      0 1 2  3 4  5 6 7  8 9  a b  c d  e  f g  h i j  k l  m n  o
//      B c c# d d# e f f# g g# a a# b c1 c# d d# e f f# g g# a a# b

char song[] = {' ',' ',' ',' ',' ',' ',' ',' ','j','h','f','e','c','a','c','e',
               'f','e','c','a','8','7','8','5','3','7','a','8','7','3','7','5',
               '3','0','3','a','8','c','a','8','7','3','5','e','f','j','m','a',
               'c','8','a','7','3','f','f','e', //first section
                      
               'f','e','f','3','2','a','5','7','3','f','e','c','e','j','m','o','k','j','h','k','j','h','f','e','c','a','8','7','5','8','7','5',//two measures
               '3','5','7','8','a','5','a','8','7','c','a','8','a','8','7','5','3','0','c','e','f','e','c','a','8','7','5','c','a','c','a','a',//two measures
               'm','j','k','m','j','k','m','a','c','e','f','h','j','k','j','f','h','j','7','8','a','c','a','8','a','7','8','a',//one measure
               '8','c','a','8','7','5','7','5','3','5','7','8','a','c','8','c','a','c','e','f','a','c','e','f','h','j','k','m',//one measure
               'm','j','k','m','j','k','m','a','c','e','f','h','j','k','j','f','h','j','7','8','a','c','a','8','a','7','8','a',//one measure
               '8','c','a','8','7','5','7','5','3','5','7','8','a','c','8','c','a','c','e','f','a','c','e','f','h','j','k','m',
               'j','f','h','j','h','f','h','e','f','h','j','h','f','e','f','c','e','f','3','5','7','8','7','5','7','f','e','f',
               'c','f','e','c','a','8','a','8','7','8','a','c','e','f','c','f','e','f','e','c','e','f','h','f','e','f','c','e',
               'f','3','5','7','3','2','e','f','h','e','c','0','2','3','0','2','a','8','7','5',
               '3','8','7','5','8','7','3','5','7','a','8','c','a','8','7','5','a','8','7','5',
               '7','f','e','f','7','a','a','c','e','a','7','f','h','j','f','j','j','h','f','e',
               'c','c','a','c','e','f','j','h','f','j','k','f','e','c','c','a','5','a','a',//second repeat
           
                      
               'f','e','c','a','8','7','8','5','j','h','f','e','c','a','c','e','f'};
                
//      0 1 2  3 4  5 6 7  8 9  a b  c d  e  f g  h i j  k l  m n  o
//      B c c# d d# e f f# g g# a a# b c1 c# d d# e f f# g g# a a# b


//'','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','',

int beats[] = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
               4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 
               3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
               3, 3, 3, 3, 3, 3, 3, 3,//first section
               
               2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //32
               2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
               2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
               2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
               2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
               2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
               2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
               2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
               2, 1, 1, 2, 2, 2, 1, 1, 2, 2, 2, 1, 1, 2, 2, 2, 1, 1, 2, 2, 
               2, 1, 1, 2, 2, 2, 1, 1, 2, 2, 2, 1, 1, 2, 2, 2, 1, 1, 2, 2, 
               2, 1, 1, 2, 2, 2, 1, 1, 2, 2, 2, 1, 1, 2, 2, 2, 1, 1, 2, 2, 
               2, 1, 1, 2, 2, 2, 1, 1, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2,//second repeat
               
               
               4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
               



void setup() 
{
  pinMode(violin1Pin, OUTPUT);
  pinMode(buttonPin, INPUT);
 
}

void loop() 
{
  int buttonState;
  buttonState = digitalRead(buttonPin);
  
  
  if(buttonState == LOW)
  {
    playSong = false;
  }
  else if(buttonState == HIGH)
  {
    playSong = true;
    
  }
  
  
  
  if(playSong == false)
  {
   
  }
  else
  {
    playsong();
  }
  
}
void playsong(){
  int buttonState;
  int i;
  double duration;
  for (i = 0; i < songLength; i++) // step through the song arrays
    {
      buttonState = digitalRead(buttonPin);
      if (beats[i] == 4)
      {
        duration = tempo;
      }
      else if (beats[i] == 3)
      {
        duration = (tempo / 2) + .2;
      }
      else if (beats[i] == 2)
      {
        duration = (tempo / 4) + .4;
      }
      else if (beats[i] == 0)
      {
        duration = 0;
      }
      else
      {
        duration = tempo / 8 - .2;
      }

    
      if (song[i] == ' ')          // is this a rest? 
      {
        delay(duration);
      }
      else                          // otherwise, play the note
      {
        tone(violin1Pin, frequency(song[i]), duration);
        delay(duration);            // wait for tone to finish
      }
      
      if(buttonState == HIGH){
        delay(10);
      }
      else if(buttonState == LOW){
      }
      //delay(10);              // brief pause between 
    
  }
  // We only want to play the song once, so we'll pause forever:
 // while(true){}
  
  playSong = false;
}


char names[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o'};
int frequencies[] = {247,262,277,294,311,330,349,370,392,415,440,466,494,523,554,587,622,659,698,740,784,831,880,932,988};
 
 // This function takes a note character (a-g), and returns the
 // corresponding frequency in Hz for the tone() function.
int frequency(char note) 
{
  int i;
  const int numNotes = 25;  // number of notes we're storing

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
