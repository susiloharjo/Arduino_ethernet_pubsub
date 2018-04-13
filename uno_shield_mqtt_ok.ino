#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

//MAC address of the Ethernet shield
byte mac[] = { 0x90, 0xA2, 0xD2, 0x0F, 0x97, 0xFF };
char macstr[] = "90a2d20f97ff";

//char servername[]= "test.mosquitto.org";
char servername[]= "10.80.1.82";
String clientName = "sensor1";
char topicName[] = "topic";
char username[] = "username";
char password[] = "passwd";

EthernetClient ethClient;
PubSubClient client(servername, 1883, 0, ethClient);

void setup(){  
  Serial.begin(9600);
  if( 0 == Ethernet.begin(mac) ){
    Serial.println("Failed to configue Ethernet using DHCP");
  }

  //print the local IP address
  Serial.print("My IP address:");
  for( byte thisByte = 0; thisByte < 4; thisByte++ ){
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Here");
}

void loop(){
  char clientStr[34];
  clientName.toCharArray(clientStr, 34);

  if (!client.connected()) {
    Serial.print("Trying to connect to: ");
    Serial.println(clientStr);
    Serial.print("Password: ");
    Serial.println(password);
    //client.connect(clientStr);
    client.connect(clientStr, username, password);
  }

  if (client.connected() ) {
    char message[] = "Hi, there";

    //publish data
    boolean pubresult = client.publish(topicName,message);

    Serial.print("attempt to send ");
    Serial.println(message);
    Serial.print("to ");
    Serial.println(topicName);

    if (pubresult){
      Serial.println("successfully sent");
    }else{
      Serial.println("unsuccessfully sent");
    }
  }
  delay(5000);
}
