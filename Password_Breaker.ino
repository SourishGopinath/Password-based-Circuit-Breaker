
#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
 
#include <Keypad.h> 
 
int Lock = A0;

const byte numRows= 4;
const byte numCols= 3;
 
char keymap[numRows][numCols]= 
{
{'1', '2', '3'}, 
{'4', '5', '6'}, 
{'7', '8', '9'},
{'*', '0', '#'}
};
 
char keypressed;                
char code[]= {'2','6','0','8'};
 
char check1[sizeof(code)];
char check2[sizeof(code)];
 
short a=0,i=0,s=0,j=0;
 
byte rowPins[numRows] = {0,1,2,3};
byte colPins[numCols]= {4,5,6};  
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);
 
void setup()
{
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
  lcd.print("  Password Breaker");
  lcd.setCursor(0, 1);
  lcd.print("Assignment");
  lcd.setCursor(0,2);
  lcd.print("Press: ");
  lcd.setCursor(0,3);
  lcd.print("* To ON & # To OFF");
  pinMode(Lock, OUTPUT);
}
 
void loop()
{
  keypressed = myKeypad.getKey(); 
  if(keypressed == '*') 
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter Code");
    ReadCode();
    if(a==sizeof(code))
    {
      OpenDoor();
    }
    else
    {
      lcd.clear();
      lcd.print("Wrong Password");
      lcd.setCursor(0,1);
      lcd.print("Try again");
      lcd.setCursor(0,2);
      lcd.print("Press *");
    }
  }

  if(keypressed == '#')
  {
    lcd.clear();
    digitalWrite(Lock, LOW);
    lcd.print("Breaker is switched OFF:");
    lcd.setCursor(0,1);
    lcd.print("Press * To Switch ONN");
  }
}


void ReadCode()
{
  lcd.setCursor(0,2);
  lcd.print("and Press '#'");
  i=0;
  a=0;
  j=0;
  
  while(keypressed != '#')  {
    keypressed = myKeypad.getKey();                         
    if(keypressed != NO_KEY && keypressed != '#' )
    {
      lcd.setCursor(j,1);
      lcd.print("*");
      j++;
      
      if(keypressed == code[i]&& i<sizeof(code))
      {
        a++;
        i++;
      }
      else
      a--;
    }
  }
  
  keypressed = NO_KEY;
}

void OpenDoor()
{
  lcd.clear();
  lcd.print("Password correct");
  digitalWrite(Lock,HIGH);
  delay(2000);
  lcd.clear();
  lcd.print("Circuit is switched onn");
  lcd.setCursor(0,2);
  lcd.print("Press # To Switch off");
  lcd.setCursor(0,3);
  lcd.print("The Breaker"); 
 }

 
