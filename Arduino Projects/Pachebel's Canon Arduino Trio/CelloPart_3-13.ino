const int violin1Pin = 8;
const int violin2Pin = 9;
const int celloPin = 10;

// Length must equal the total number of notes and spaces 
const int songLength = 226;
// 1000 = 1 second. Do the math.
int tempo = 990;
boolean playSong = false;
boolean repeat = false;


char song[] = {'D','7','9','4','5','0','5','7','D','7','9','4','5','0','5','7',
               'D','7','9','4','5','0','5','7','D','7','9','4','5','0','5','7', //32
               'D','7','9','4','5','0','5','7', //first section
                      
               'D','7','9','4','5','0','5','7','D','7','9','4','5','0','5','7', //96
               'D','7','9','4','5','0','5','7','D','7','9','4','5','0','5','7',
               'D','7','9','4','5','0','5','7','D','7','9','4','5','0','5','7', //128
               'D','7','9','4','5','0','5','7', 'R',//second repeat
                      
               'D','7','9','4','5','0','5','7','D','7','9','4','5','0','5','7','D'};


int beats[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
               1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
               1, 1, 1, 1, 1, 1, 1, 1, 
               
               
               1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
               1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
               1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
               1, 1, 1, 1, 1, 1, 1, 1, 0,
               
               1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
               



void setup() 
{
  pinMode(violin1Pin, INPUT);
  pinMode(violin2Pin, INPUT);
  pinMode(celloPin, OUTPUT);
  Serial.begin(9600);
  
}

void loop() 
{
  int buttonState = digitalRead(violin1Pin);
  int i, duration;
  
  if(buttonState = HIGH)
  {
    playSong = true;
  }
  
  if(playSong)
  {
    for (i = 0; i < songLength; i++) // step through the song arrays
    {
      if (beats[i] == 1)
      {
        duration = tempo;
      }
      else if (beats[i] == 0)
      {
        duration = 0;
      }
    
      if (song[i] == ' ')          // is this a rest? 
      {
        delay(duration);
        Serial.print("Resting");      // then pause for a moment
      }
      else if(song[i] == 'R' && repeat == false)
      {
        repeat = true;
        i = 47;
      }
      else                          // otherwise, play the note
      {
        tone(celloPin, frequency(song[i]), duration);
        delay(duration);            // wait for tone to finish
      }
      delay(10);              // brief pause between `
    }
  }
  // We only want to play the song once, so we'll pause forever:
 // while(true){}
  playSong = false;
}



char names[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'C', '#', 'D'};
int frequencies[] = {147, 156, 165, 175, 185, 196, 208, 220, 233, 247, 262, 277, 294};

 // This function takes a note character (a-g), and returns the
 // corresponding frequency in Hz for the tone() function.
int frequency(char note) 
{
  int i;
  const int numNotes = 13;  // number of notes we're storing
  
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
