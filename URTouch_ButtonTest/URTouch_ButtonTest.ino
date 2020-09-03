

#include <UTFT.h>
#include <URTouch.h>
// Пример простого интерфейса при помощи TFT дисплея с резистивным экраном. 
// А.Б. Колкер Микропроцессорные усторйства автоматики НГТУ 2020
// текст программы лицензия GPL



// Инициализация дисплея
UTFT    myGLCD(ITDB24E_8,A5,A4,A3,A2);
// Инициализация тачскрина 
URTouch  myTouch( A1, 10, A0, 8, 9);

// Объявление шрифта
extern uint8_t BigFont[];

int x, y;
char stCurrent[20]="";
int stCurrentLen=0;
char stLast[20]="";


// Рисуем две кнопки
void drawButtons()
{

// зеленая кнопка "On"
  myGLCD.setColor(0, 255, 0);
  myGLCD.fillRoundRect (10, 130, 150, 180);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (10, 130, 150, 180);
  myGLCD.print("ON", 40, 147);
 
// Фиолетовая кнопка OFF  
  myGLCD.setColor(255, 0, 255);
  myGLCD.fillRoundRect (160, 130, 300, 180);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (160, 130, 300, 180);
  myGLCD.print("OFF", 190, 147);
  myGLCD.setBackColor (0, 0, 0);
}


// Риуем красную рамку, пока кнопка нажата
void waitForIt(int x1, int y1, int x2, int y2)
{
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  while (myTouch.dataAvailable())
    myTouch.read();
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
}

/*************************
**  Стандартные функции  **
*************************/

void setup()
{
// Инициализация
  myGLCD.InitLCD();
  myGLCD.clrScr();

  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);

  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(0, 0, 255);
  drawButtons();  
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  while (true)
  {
    if (myTouch.dataAvailable()) // проверка есть ли  события от тачскрина
    {
      myTouch.read();  // получение координат
      x=myTouch.getX(); 
      y=myTouch.getY();
      
      if ((x>=10) && (x<=150))  // Нажата кнопка ВКЛ
        {
          waitForIt(10, 130, 150, 180);
          digitalWrite(LED_BUILTIN, HIGH);

        }
        if ((x>=160) && (x<=300))  // Нажата кнопка ВЫКЛ
        {
          waitForIt(160, 130, 300, 180);
          digitalWrite(LED_BUILTIN, LOW);
        }
    }
  }

}
