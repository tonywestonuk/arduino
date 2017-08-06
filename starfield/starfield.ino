 #include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
 #include "math.h"
 #define stars 800

 SSD1306  display(0x3c, 5, 4);


float x[stars],y[stars],z[stars];

float vx=0,vy=0,vz=-.5;

float lookups[1000]; 

void setup() {
  for (int i=0; i<stars ; i++){
    z[i]=random(1000)/10.0-50;
     x[i]=random(1000)/10.0-50;
     y[i]=random(1000)/10.0-50;
  }
  display.init();

}

void loop() {
  createStars();
  display.clear();
   vx=vx+.005;
   vy=vy+.006;
   vz=vz+.001;

   float bx=(sin(vz)*cos(vx))*2;
   float by=(sin(vy)*cos(vz))*2;
   float bz=(cos(vx)*sin(vy))*2;
   
  for (int i=0; i<stars ; i++){
  

    
    
    z[i]=z[i]+bx;
    y[i]=y[i]+by;
    x[i]=x[i]+bz;

    // normalize 50 to displayWidth/
   
  if (z[i]>1 && (z[i]<40 || random(2)==1)){
      int xx=(.3*x[i] * DISPLAY_WIDTH /z[i]) +DISPLAY_WIDTH/2;
      int yy=(.3*y[i] * DISPLAY_WIDTH/z[i] ) +DISPLAY_HEIGHT/2 ;
      int ss=20/z[i]+1;
      
      display.fillRect(xx,yy,ss,ss);
      }
  }
  display.display();
  delay(30);
}

void createStars(){
  // recreate all stars that have fallen out of range.
  for (int i=0; i<stars; i++){
    long dist=x[i]*x[i]+y[i]*y[i]+z[i]*z[i];
    if (dist>7500) {
      x[i]=-x[i]*random(90)/100;
      y[i]=-y[i]*random(90)/100;
      z[i]=-z[i]*random(90)/100;

    }
  }
}



