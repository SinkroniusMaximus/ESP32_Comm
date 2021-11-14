public void TheSetupFunction() {
  println("ok");
  try{
    c = new Client(this, "192.168.4.1", 80);  // Connect to server on port 80 
  } catch(Exception e){}
  cp5 = new ControlP5(this);
  PFont pfont = createFont("Calibri Light",20);
  Label.setUpperCaseDefault(false);
  ControlFont font = new ControlFont(pfont,20); //font, font-size
  Setup_Main_Page(font);
  for(ListInterface ob : Interfacelist)
  {
      ob.display(font);
  }
  //background(color(9,105,121));
  try
  {
    String portName = Serial.list()[0];
    println(portName);
    myPort = new Serial(this, portName, 256000);
  }
  catch(Exception e)
  {
  }
}
