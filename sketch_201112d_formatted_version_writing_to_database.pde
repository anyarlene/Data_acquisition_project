import processing.serial.*;
import de.bezier.data.sql.*;
MySQL db;
Serial myPort ; // The serial port
String myString = null;
float counter;
String direction;

void setup () {
  myPort = new Serial (this, "COM6", 9600) ;
  myPort.clear();
  // Throw out the first reading , in case we started reading
  // in the middle of a string from the sender .
  myString = myPort.readStringUntil ('\n');
  myString = null;

  frameRate(1); // 1 frame per second
  size (200 , 200) ;
  String server = "10.50.202.242";
  String user = "user01";
  String pass = "theteam246";
  String database = "user01";
  db = new MySQL (this, server, database, user, pass );
}

void draw () {
  while ( myPort.available () > 0) {
    myString = myPort.readStringUntil ('\n');
    if ( myString != null ){ // if received string is non empty
      String [] myStringList = split(myString, ':'); // split the String into two substrings separated by ';'
    if ( myStringList.length == 2) { // if there are 2 Strings in myStringList
      counter = float(myStringList[1]);
      direction = myStringList[0];
    if (db.connect ()) {
      db.query("INSERT INTO person_counter(counter, direction, date, time) VALUES('%s', '%s', CURRENT_DATE(), CURRENT_TIME())", counter, direction);
      //println (myString);
      //print (distance1);
      //println (distance2); 
      }
     }
    }
  }
}
