void Setup_Main_Page(ControlFont font)
{
    d1 = cp5.addDropdownList("myList_d1")
          .setPosition(20, 50)
          .setSize(200, 100)
          .setHeight(210)
          .setItemHeight(40)
          .setBarHeight(40)
          .setFont(font)
          .setColorBackground(style.ControlBgcolor)
          .setColorForeground(style.ControlFgcolor)
          .setColorActive(style.ControlActiveColor);
          ;
 
      d1.getCaptionLabel().set("Port"); //set PORT before anything is selected
}

void Main_Page()
{
    d1.setPosition(grid.x(1),grid.y(2));  
  if(d1.isMouseOver()) 
  {
     d1.clear(); //Delete all the items
     for (int i=0;i<Serial.list().length;i++) 
     {
       d1.addItem(Serial.list()[i], i); //add the items in the list
     }
     if (d1.isOpen()&!d1isOpenOld)
      {
        d1.bringToFront();  
      }
      d1isOpenOld = d1.isOpen(); 
  }
}

public void myList_d1()
{
      try {
      myPort.clear(); //delete the port
      myPort.stop(); //stop the port
    } catch (Exception e) {
      //e.printStackTrace();
      //line = null;
    }
    if (d1.isMouseOver()) {
    portName = Serial.list()[int(d1.getValue())]; //port name is set to the selected port in the dropDownMeny
    myPort = new Serial(this, portName, Baudrate); //Create a new connection
    println("Serial index set to: " + d1.getValue());
    delay(2000); 
    myPort.clear(); //delete the port
  }
}
