#include <Servo.h>  
Servo myservoA;  
Servo myservoB;
Servo myservoC;
Servo myservoD;
Servo myservoE;
Servo myservoF;
int i,pos,myspeed,myshow;
int sea,seb,sec,sed,see,sef;
static int v=0;

String mycommand="";  //捕捉串口发来的指令  #auto：自动运行   #com：计算机串口控制     #stop：静止状态
static int mycomflag=2; // #auto：2 自动运行  , #com： 1  计算机控制    #stop：0 静止状态   


void myservosetup()  //舵机初始化到等待状态
{
   sea=myservoA.read();
   seb=myservoB.read();
   sec=myservoC.read();
   sed=myservoD.read();
   see=myservoE.read();
   sef=myservoF.read();
   
   myspeed=500;
   for(pos=0;pos<=myspeed;pos+=1)
   {
    myservoA.write(int(map(pos,1,myspeed,sea,66)));
    myservoB.write(int(map(pos,1,myspeed,seb,90)));
    myservoC.write(int(map(pos,1,myspeed,sec,50)));
    myservoD.write(int(map(pos,1,myspeed,sed,90)));
    myservoE.write(int(map(pos,1,myspeed,see,120)));
    myservoF.write(int(map(pos,1,myspeed,sef,90)));    
    delay(1);
   }
}

void setup() 
{ 
  pinMode(13,INPUT);
  pinMode(12,INPUT);  
  Serial.begin(9600);
  myshow=0;
  mycomflag=2; // 机械臂默认上电状态为：2  自动运行
  myservoA.attach(3);  // 控制腰部（A）的端口是~3号
  myservoB.attach(5); // 控制大臂（B）的端口是~5号
  myservoC.attach(6); // 控制小臂（C）的端口是~6号
  myservoD.attach(9); // 控制小臂旋转（D）的端口是~9号
  myservoE.attach(10); // 控制腕部（E）的端口是~10号
  myservoF.attach(11); // 控制腕部旋转（F）的端口是~11号
  
  myservoA.write(66);
  myservoB.write(90);
  myservoC.write(50);
  myservoD.write(90);
  myservoE.write(120);
  myservoF.write(90);    

}

void loop() 
{ 
  while (Serial.available() > 0)  
    {
        mycommand += char(Serial.read());
        delay(2);
    }
    if (mycommand.length() > 0)
    {
        if(mycommand=="#auto")
        {
          mycomflag=2;
          Serial.println("auto station");
          mycommand="";
        }
        if(mycommand=="#com")
        {
          mycomflag=1;
          Serial.println("computer control station");
          mycommand="";
          myservosetup();
        }
        if(mycommand=="#stop")
        {
          mycomflag=0;
          Serial.println("stop station");
          mycommand="";
        }
        
    }
  
  
  if(mycomflag==1)  //如果是计算机串口控制 1
  {      
 
   for(int m=0;m<mycommand.length();m++) // 
  {
    char ch = mycommand[m];   //读取串口数据
    switch(ch)
    {
      case '0'...'9':
      v = v*10 + ch - '0';   //字符转换成十进制
      break;
      
      
      
      case 'a':   //如果数据后带a，则表示是一号舵机的数据，比如串口发送85a
      if(v >= 5 || v <= 175 ) myservoA.write(v); //用于设定舵机旋转角度的语句，可设定的角度范围是0°到180°，“V”得到所输入的值而改变角度，比如85a为85度角
      v = 0;
      break;

      case 'b':   //如果数据后带b，则表示是二号舵机的数据，比如串口发送85a

      myservoB.write(v);   //用于设定舵机旋转角度的语句，可设定的角度范围是0°到180°，“V”得到所输入的值而改变角度，比如90b为90度角
      v = 0;
      break;
      case 'c':   
      if(v >= 20 ) myservoC.write(v);   
      v = 0;
      break;
      case 'd':  
      myservoD.write(v);   
      v = 0;
      break;
      case 'e':  
      myservoE.write(v);   
      v = 0;
      break;
      case 'f':  
      myservoF.write(v);   
      v = 0;
      break;
    }
   
    }  
   mycommand="";
  }  // end if(mycomflag=2)
  
  if(mycomflag==2)  //如果是自动运行状态2 
  {    
   delay(3000); 
   //Serial.println("auto station"); 
   myservosetup();
   myspeed=500;
    for(pos = 0; pos <=myspeed; pos += 1)  
  {                                
    myservoA.write(int(map(pos,1,myspeed,66,90))); // 让A从66度旋转到90度 （可修改角度）
    myservoB.write(int(map(pos,1,myspeed,90,40))); //让B从90度旋转到40度 （可修改角度）
    delay(1);                       
  }
   delay(1000);
   myspeed=500;
  for(pos = 0; pos <=myspeed; pos += 1)  
  {                                
    myservoC.write(int(map(pos,1,myspeed,50,65))); // 
    myservoD.write(int(map(pos,1,myspeed,90,170))); //
    myservoE.write(int(map(pos,1,myspeed,90,5))); 
    delay(1);                       
   }
  myspeed=1000;
  for(pos = 0; pos <=myspeed; pos += 1)  
  {                                
    myservoB.write(int(map(pos,1,myspeed,40,70))); // 
    myservoC.write(int(map(pos,1,myspeed,65,50))); //
    delay(1);                       
   }
   myspeed=500;
  for(pos = 0; pos <=myspeed; pos += 1)  
  {                                
    myservoC.write(int(map(pos,1,myspeed,50,45))); // 
    myservoD.write(int(map(pos,1,myspeed,170,90))); //
    myservoE.write(int(map(pos,1,myspeed,5,27)));
    myservoF.write(int(map(pos,1,myspeed,90,40)));
    delay(1);                       
   }
   myspeed=1000;
  for(pos = 0; pos <=myspeed; pos += 1)  
  {                                
    myservoA.write(int(map(pos,1,myspeed,90,140))); // 
    myservoF.write(int(map(pos,1,myspeed,40,130)));    
    delay(1);                       
   }  
    myspeed=500;
    for(pos = 0; pos <=myspeed; pos += 1)  
  {                                
    myservoA.write(int(map(pos,1,myspeed,140,90))); // 
    myservoC.write(int(map(pos,1,myspeed,45,50))); // 
    myservoB.write(int(map(pos,1,myspeed,70,50))); //
    myservoE.write(int(map(pos,1,myspeed,27,120))); //
    delay(1);                       
  } 
  }
  
  if(mycomflag==0) //如果是静止状态0
  {
   myservosetup();
  }
}
