//ArrayList<text_int> text_intlist = new ArrayList<text_int>();
//ArrayList<dropdown_int> dropdown_intlist = new ArrayList<dropdown_int>();
ArrayList<ListInterface> Interfacelist = new ArrayList<ListInterface>();

class Style
{
  int ControlBgcolor;
  int ControlFgcolor;
  int ControlActiveColor;
  int ControlLightColor;
  Style()
  {
    ControlBgcolor = color(9,44,65,255);
    ControlFgcolor = color(9,122,105,255);
    ControlActiveColor = color(9,131,129,255);
    ControlLightColor = color(50,251,114,255);
  }
}
Style style = new Style();

class Grid
{
  int NrofRows;
  int NrofColumns;
  int Posx;
  int Posy;
  int Gwidth;
  int Gheight;
  int OGwidth;
  int OGheight;
  boolean UseWindowSize;
  Grid(int row, int column, int Posx, int Posy, int Gwidth, int Gheight)
  {
    NrofRows = row;
    NrofColumns = column;
    this.Posx = Posx;
    this.Posy = Posy;
    this.Gwidth = Gwidth;
    this.Gheight = Gheight;
    OGwidth = Gwidth;
    OGheight = Gheight;
    UseWindowSize = false;
  }
  Grid(int row, int column)
  {
    NrofRows = row;
    NrofColumns = column;
    Posx = 0;
    Posy = 0;
    this.Gwidth = width;
    this.Gheight = height;
    UseWindowSize = true;
    OGwidth = Gwidth;
    OGheight = Gheight;
  }
  void Resize(int row, int column)
  {
    NrofRows = row;
    NrofColumns = column;
    if(UseWindowSize)
    {
      Posx = 0;
      Posy = 0;
      this.Gwidth = width;
      this.Gheight = height;
    }
  }
  void Begin()
  {
    OGwidth = Gwidth;
    OGheight = Gheight;
  }
  int x(int gridx)
  {
    if(UseWindowSize)
    {
      Gwidth = width;
    }
    return (Posx + (gridx * (Gwidth / NrofRows)));
  }
  int y(int gridy)
  {
    if(UseWindowSize)
    {
      Gheight = height;
    }
    return (Posy + (gridy * (Gheight / NrofColumns)));
  }
}
 
public interface ListInterface {
   void display(ControlFont font);
   void update();
}


class text_string extends Xstring implements ListInterface
{
  Textfield txtfld;
  int Posx;
  int Posy; 
  String HMI_Name;
  String label;
  String old_txt;
  
  text_string(int x, int y, String HMI_Name, String label)
  {
    super(HMI_Name);
    Interfacelist.add(this);
    Posx = x;
    Posy = y;
    this.HMI_Name = HMI_Name;
    this.label = label;
    old_txt = "";
  }
  void display(ControlFont font)
  {
    txtfld = cp5.addTextfield(HMI_Name)
   .setPosition(Posx,Posy)
   .setFont(font)
   .setSize(200,40)
   .setAutoClear(false)
   .setLabel(label)
   .setColorBackground(style.ControlBgcolor)
   .setColorForeground(style.ControlFgcolor)
   .setColorActive(style.ControlActiveColor);
   ;
  }
  void update()
  {
    txtfld.setPosition(grid.x(Posx),grid.y(Posy));
    if(grid.UseWindowSize)
    {
      txtfld.setSize(200*grid.Gwidth/grid.OGwidth,40*grid.Gheight/grid.OGheight);
    }
    if(txt!=old_txt)
    {
      txtfld.setText(this.txt);
    } 
    this.txt = txtfld.getText();
    old_txt=this.txt;
  }
}

class text_int extends Xint implements ListInterface
{
  Textfield txtfld;
  int Posx;
  int Posy; 
  String HMI_Name;
  String label;
  String old_txt;
  text_int(int x, int y, String HMI_Name, String label)
  {
    super(HMI_Name);
    Interfacelist.add(this);
    Posx = x;
    Posy = y;
    this.HMI_Name = HMI_Name;
    this.label = label;
    old_txt = "";
  }
  void display(ControlFont font)
  {
    txtfld = cp5.addTextfield(HMI_Name)
   .setPosition(Posx,Posy)
   .setFont(font)
   .setSize(200,40)
   .setAutoClear(false)
   .setLabel(label)
   .setColorBackground(style.ControlBgcolor)
   .setColorForeground(style.ControlFgcolor)
   .setColorActive(style.ControlActiveColor)
   ;
  }
  void update()
  {
    txtfld.setPosition(grid.x(Posx),grid.y(Posy));
    if(grid.UseWindowSize)
    {
      txtfld.setSize(200*grid.Gwidth/grid.OGwidth,40*grid.Gheight/grid.OGheight);
    }
    if(val!=int(old_txt))
    {
      txtfld.setText(str(this.val));
    } 
    this.val = int(txtfld.getText());
    old_txt=txtfld.getText();
  }
}

class dropdown_int extends Xint implements ListInterface
{
  ScrollableList scrllist;
  int Posx;
  int Posy; 
  String HMI_Name;
  String label;
  int old_int;
  List l;
  dropdown_int(int x, int y, List l, String HMI_Name, String label)
  {
   super(HMI_Name); 
   Interfacelist.add(this);
    Posx = x;
    Posy = y;
    this.l = l;
    this.HMI_Name = HMI_Name;
    this.label = label;
    old_int = 0;
  }
  
  void display(ControlFont font)
  {
     scrllist = cp5.addScrollableList(HMI_Name)
     .setPosition(Posx, Posy)
     .setSize(200, 200)
     .setFont(font)
     .setBarHeight(40)
     .setItemHeight(40)
     .setHeight(200)
     .addItems(l)
     .setType(ScrollableList.LIST) // currently supported DROPDOWN and LIST
     .setLabel(label)
     .setColorBackground(style.ControlBgcolor)
     .setColorForeground(style.ControlFgcolor)
     .setColorActive(style.ControlActiveColor)
     .setScrollSensitivity(5);
     scrllist.close();
     scrllist.bringToFront();
  }
  void update()
  {
    scrllist.setPosition(grid.x(Posx),grid.y(Posy));
    if(grid.UseWindowSize)
    {
      scrllist.setSize(200*grid.Gwidth/grid.OGwidth,200);
    }
    if(val!=old_int)
    {
      try
      {
        scrllist.setLabel(scrllist.getItem(this.val).get("name").toString());
        scrllist.setValue(val);
      }
      catch(Exception e)
      {    
      }
    }
    else
    {
      val = int(scrllist.getValue());
      if (val!=old_int)
      {
        //println(val);
        scrllist.setLabel(scrllist.getItem(this.val).get("name").toString());
        scrllist.close();
        println(this.val);
      }
    }
    old_int=val;
  } 
}

class knob_int extends Xint implements ListInterface
{
  Knob knob;
  int Posx;
  int Posy; 
  String HMI_Name;
  String label;
  int old_int;
  knob_int(int x, int y, String HMI_Name, String label)
  {
   super(HMI_Name); 
   Interfacelist.add(this);
    Posx = x;
    Posy = y;
    this.HMI_Name = HMI_Name;
    this.label = label;
    old_int = 0;
  }
  
  void display(ControlFont font)
  {
     knob = cp5.addKnob(HMI_Name)
           .setRange(0,1024)
           .setPosition(Posx,Posy)
           .setRadius(50)
           //.setNumberOfTickMarks(1024)
           //.hideTickMarks()
           //.snapToTickMarks(true)
           .setDecimalPrecision(0) 
           .setDragDirection(Knob.VERTICAL)
           .setFont(font)
           .setLabel(label)
           .setColorBackground(style.ControlBgcolor)
           .setColorForeground(style.ControlFgcolor)
           .setColorActive(style.ControlActiveColor);
           ;
  }
  void update()
  {
    knob.setPosition(grid.x(Posx),grid.y(Posy));
    if(grid.UseWindowSize)
    {
      knob.setRadius((50*grid.Gheight/grid.OGheight));
    }
    if(val!=old_int)
    {
      try
      {
        knob.setValue(this.val);
      }
      catch(Exception e)
      {    
      }
    } 
    val = int(knob.getValue());
    if (val!=old_int)
    {
      //println(val);
      knob.setValue(int(this.val));
    }
    old_int=val;
  } 
}

class slider_int extends Xint implements ListInterface
{
  Slider slider;
  int Posx;
  int Posy; 
  String HMI_Name;
  String label;
  int old_int;
  slider_int(int x, int y, String HMI_Name, String label)
  {
   super(HMI_Name); 
   Interfacelist.add(this);
    Posx = x;
    Posy = y;
    this.HMI_Name = HMI_Name;
    this.label = label;
    old_int = 0;
  }
  
  void display(ControlFont font)
  {
    slider = cp5.addSlider(HMI_Name)
         .setPosition(Posx,Posy)
         .setSize(200,30)
         .setRange(0,1024)
         .setDecimalPrecision(0) 
         .setFont(font)
         .setLabel(label)
         .setColorBackground(style.ControlBgcolor)
         .setColorBackground(style.ControlBgcolor)
         .setColorForeground(style.ControlFgcolor)
         .setColorActive(style.ControlActiveColor);
         slider.getValueLabel().align(ControlP5.LEFT, ControlP5.BOTTOM_OUTSIDE).setPaddingX(0);
         slider.getCaptionLabel().align(ControlP5.RIGHT, ControlP5.BOTTOM_OUTSIDE).setPaddingX(0);
  }
  void update()
  {
    slider.setPosition(grid.x(Posx),grid.y(Posy));
    if(grid.UseWindowSize)
    {
      slider.setSize(200*grid.Gwidth/grid.OGwidth,30*grid.Gheight/grid.OGheight);
    }
     slider.getValueLabel().align(ControlP5.LEFT, ControlP5.BOTTOM_OUTSIDE).setPaddingX(0);
     slider.getCaptionLabel().align(ControlP5.RIGHT, ControlP5.BOTTOM_OUTSIDE).setPaddingX(0);
    if(val!=old_int)
    {
      try
      {
        slider.setValue(this.val);
      }
      catch(Exception e)
      {    
      }
    } 
    val = int(slider.getValue());
    if (val!=old_int)
    {
      //println(val);
      slider.setValue(this.val);
    }
    old_int=val;
  } 
}


class Nrbox_int extends Xint implements ListInterface
{
  Numberbox numberbox;
  int Posx;
  int Posy; 
  String HMI_Name;
  String label;
  int old_int;
  Nrbox_int(int x, int y, String HMI_Name, String label)
  {
   super(HMI_Name); 
   Interfacelist.add(this);
    Posx = x;
    Posy = y;
    this.HMI_Name = HMI_Name;
    this.label = label;
    old_int = 0;
  }
  
  void display(ControlFont font)
  {
      numberbox = cp5.addNumberbox(HMI_Name)
     .setPosition(Posx,Posy)
     .setSize(200,30)
     .setDecimalPrecision(0) 
     .setFont(font)
     .setLabel(label)
     .setScrollSensitivity(1.1)
     .setColorBackground(style.ControlBgcolor)
     .setColorForeground(style.ControlFgcolor)
     .setColorActive(style.ControlActiveColor);
  }
  void update()
  {
    numberbox.setPosition(grid.x(Posx),grid.y(Posy));
    if(grid.UseWindowSize)
    {
      numberbox.setSize(200*grid.Gwidth/grid.OGwidth,30*grid.Gheight/grid.OGheight);
    }
    if(val!=old_int)
    {
      try
      {
        numberbox.setValue(this.val);
      }
      catch(Exception e)
      {    
      }
    } 
    val = int(numberbox.getValue());
    if (val!=old_int)
    {
      //println(val);
      numberbox.setValue(this.val);
    }
    old_int=val;
  } 
}



class toggle_bool extends Xbool implements ListInterface
{
  Toggle toggle;
  int Posx;
  int Posy; 
  String HMI_Name;
  String label;
  boolean old_bool;
  toggle_bool(int x, int y, String HMI_Name, String label)
  {
   super(HMI_Name); 
   Interfacelist.add(this);
    Posx = x;
    Posy = y;
    this.HMI_Name = HMI_Name;
    this.label = label;
    old_bool = false;
  }
  
  void display(ControlFont font)
  {
    toggle = cp5.addToggle(HMI_Name)
             .setPosition(Posx,Posy)
             .setSize(60,30)
             .setMode(ControlP5.SWITCH)
             .setFont(font)
             .setLabel(label)
             .setColorBackground(style.ControlBgcolor)
             .setColorForeground(style.ControlFgcolor)
             .setColorActive(style.ControlActiveColor);
  }
  void update()
  {
    toggle.setPosition(grid.x(Posx),grid.y(Posy));
    if(grid.UseWindowSize)
    {
      toggle.setSize(60*grid.Gwidth/grid.OGwidth,30*grid.Gheight/grid.OGheight);
    }
    if(x!=old_bool)
    {
      try
      {
        toggle.setValue(this.x);
      }
      catch(Exception e)
      {    
      }
    } 
    x = toggle.getState();
    if (x!=old_bool)
    {
      //println(val);
      toggle.setValue(this.x);
    }
    old_bool=x;
  } 
}

class lamp_bool extends Xbool implements ListInterface
{
  Textlabel Customlabel;
  int Posx;
  int Posy; 
  String HMI_Name;
  String label;
  boolean old_bool;
  boolean UseLabel;
  lamp_bool(int x, int y, String HMI_Name)
  {
   super(HMI_Name); 
   Interfacelist.add(this);
    Posx = x;
    Posy = y;
    this.HMI_Name = HMI_Name;
    old_bool = false;
    label = "";
    UseLabel=false;
  }
  lamp_bool(int x, int y, String HMI_Name, String Label)
  {
    super(HMI_Name); 
    Interfacelist.add(this);
    Posx = x;
    Posy = y;
    this.HMI_Name = HMI_Name;
    old_bool = false;
    label = Label;
    UseLabel = true;
  }
  void display(ControlFont font)
  {
    //display lamp happens in update
    fill(0);
    ellipse(grid.x(Posx),grid.y(Posy)+15,40,40); 
    if (UseLabel)
    {
      String customlabelstring = "T_" + HMI_Name;
      Customlabel = cp5.addTextlabel(customlabelstring)
        .setPosition(grid.x(Posx)+ 25, grid.y(Posy))
        .setFont(font)
        .setText(label)
        ;
    }
  }
  void update()
  {
    if (x)
    {
      fill(style.ControlLightColor);
    }
    else
    {
      fill(style.ControlBgcolor);
    }
    if(grid.UseWindowSize)
    {
      ellipse(grid.x(Posx),grid.y(Posy)+15,40*grid.Gwidth/grid.OGwidth,40*grid.Gheight/grid.OGheight);
    }
    else
    {
      ellipse(grid.x(Posx),grid.y(Posy)+15,40, 40);
    }
    if (UseLabel)
    {
      Customlabel.setPosition(grid.x(Posx)+25, grid.y(Posy));
    }
  } 
}
