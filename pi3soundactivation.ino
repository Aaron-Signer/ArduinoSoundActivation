
#define LIN_OUT 1 // use the log output function
#define FFT_N 256 // set to 256 point fft
#include <FFT.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  
  sound();  
  Serial.println("Sound");
}

void sound() {
//  Serial.println("here");
  read_sound();
  int low_frequency_counter = 0;
  while(low_frequency_counter < 10) {
//    Serial.print("ggodfgfgdf");
    //Serial.println();
    if (low_frequency_sum() > 140)
      low_frequency_counter++;
    
    else
      low_frequency_counter = 0;
    read_sound();
  }
}

void read_sound() {
  for(int i=0; i < 512; i += 2) 
  {

    fft_input[i] = analogRead(A0)-512;
//    Serial.println(fft_input[i]);
    fft_input[i+1] = 0;
  }
  // window data, then reorder, then run, then take output
  fft_window(); // window the data for better frequency response
  fft_reorder(); // reorder the data before doing the fft
  fft_run(); // process the data in the fft
  fft_mag_lin(); // take the output of the fft
}

int low_frequency_sum() {
  int sum = 0;

  for(int i = 90; i<125; i++)
    sum+=fft_lin_out[i];
    
  return (sum);
}

void display_sound() {
  for(int i=0; i < 512; i += 2) {
    Serial.println(fft_input[i]);
  }
}
