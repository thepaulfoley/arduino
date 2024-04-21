#include <Servo.h>
Servo myservoA;

int i, pos, myspeed, myshow;
int sea, seb, sec, sed, see, sef;
static int v = 0;

String mycommand = ""; //捕捉串口发来的指令  #auto：自动运行   #com：计算机串口控制     #stop：静止状态
static int mycomflag = 2; // #auto：2 自动运行  , #com： 1  计算机控制    #stop：0 静止状态


void myservosetup()  //舵机初始化到等待状态
{
  sea = myservoA.read();

  myspeed = 500;
  for (pos = 0; pos <= myspeed; pos += 1)
  {
    myservoB.write(int(map(pos, 1, myspeed, seb, 66)));
    delay(2);
  }
}

void setup()
{
  pinMode(13, INPUT);
  pinMode(12, INPUT);
  Serial.begin(9600);
  myshow = 0;
  mycomflag = 2; // 机械臂默认上电状态为：2  自动运行
  myservoA.attach(3);  // 控制腰部（A）的端口是~3号
  myservoA.write(66);

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
    if (mycommand == "#auto")
    {
      mycomflag = 2;
      Serial.println("auto station");
      mycommand = "";
    }
    if (mycommand == "#com")
    {
      mycomflag = 1;
      Serial.println("computer control station");
      mycommand = "";
      myservosetup();
    }
    if (mycommand == "#stop")
    {
      mycomflag = 0;
      Serial.println("stop station");
      mycommand = "";
    }

  }


  if (mycomflag == 1) //如果是计算机串口控制 1
  {

    for (int m = 0; m < mycommand.length(); m++) //
    {
      char ch = mycommand[m];   //读取串口数据
      switch (ch)
      {
        case '0'...'9':
          v = v * 10 + ch - '0'; //字符转换成十进制
          break;



        case 'a':   //如果数据后带a，则表示是一号舵机的数据，比如串口发送85a
          if (v >= 5 || v <= 175 ) myservoA.write(v); //用于设定舵机旋转角度的语句，可设定的角度范围是0°到180°，“V”得到所输入的值而改变角度，比如85a为85度角
          v = 0;
          break;

        case 'b':   //如果数据后带b，则表示是二号舵机的数据，比如串口发送85a

          myservoB.write(v);   //用于设定舵机旋转角度的语句，可设定的角度范围是0°到180°，“V”得到所输入的值而改变角度，比如90b为90度角
          v = 0;
          break;
        case 'c':
          if (v >= 20 ) myservoC.write(v);
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
    mycommand = "";
  }  // end if(mycomflag=2)

  if (mycomflag == 2) //如果是自动运行状态2
  {
    delay(3000);
    //Serial.println("auto station");
    myservosetup();
    myspeed = 500;
    for (pos = 0; pos <= myspeed; pos += 1)
    {
      myservoA.write(int(map(pos, 1, myspeed, 66, 90))); // 让A从66度旋转到90度 （可修改角度）
      delay(1);
    }
    delay(5000);
  }

  if (mycomflag == 0) //如果是静止状态0
  {
    myservosetup();
  }
}
