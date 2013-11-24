#include <SerialTools.h>
#include <WStringExt.h>



SerialTools serialTools(32,50);


void setup() 
{  
  Serial.begin(9600); 
}

void loop() 
{
  String serialString = serialTools.getSerialString();
  if(serialString.length()>0)
  {
    Serial.println("--- start ---");
    Serial.println();
    
    
    Serial.print("as String: ");
    Serial.println(serialString);
    
    
    Serial.print("as char[]: ");
    Serial.println(((StringExt)serialString).asCharArray());
    
    
    Serial.print("as double*2: ");
    Serial.println(((StringExt)serialString).asDouble()*2);
    
    
    Serial.print("split by ',': ");
    String stringArray [8];
    ((StringExt)serialString).split(',',stringArray);
    for(int i=0;i<8;i++)
    {
      Serial.print(stringArray[i]);
      Serial.print(" ");
    }
    Serial.println();
   
    
  }
}
