var CAR_DEBUGINFO=false;
var GAME_DEBUGINFO=true;

function setup(){
  createCanvas(1400,700);
  frameRate(30);

  car_blue = loadImage("scripts/standalone/car_blue.png")
  car_red = loadImage("scripts/standalone/car_red.png")
  car_teal = loadImage("scripts/standalone/car_teal.png")
  car_yellow = loadImage("scripts/standalone/car_yellow.png")

  Stoplichten.push(new Stoplicht("left"))
  Stoplichten.push(new Stoplicht("down"))
  Stoplichten.push(new Stoplicht("right"))
  Stoplichten.push(new Stoplicht("up"))
}

function removefromCarsArray(user_entry){
  console.log("Removing "+user_entry+" from Cars")
  if(Cars.length > -1){
    for(var x=0; x<Cars.length; x++){
      if(Cars[x].id==user_entry){
        var index=x;
      }
    }
    if(index > -1){
      Cars.splice(index,1);
    }
  }
}
function generateRandomCar(){
  var car_x = [1350,-50,625,725]
  var car_y = [275,375,-50,700]
  var car_start = ["right","left","up","down"]
  var car_direction = ["right","left","up","down"]
  var car_outfit = [car_blue,car_red,car_teal,car_yellow]
  var car_outfit_names = ["blue","red","teal","yellow"]
  var car_outfit_facing= ["left","right","down","up"]


  for(var x=0; x<10; x++){
    var rand_int_begin = int(random(0,3))
    var rand_int_end = int(random(0,3))
    var rand_int_outfit = int(random(0,3))

    if(rand_int_begin != rand_int_end){
      console.log("New spawned car will start from ["+car_start[rand_int_begin]+"] and will turn ["+car_direction[rand_int_end]+"] color of this car is ["+car_outfit_names[rand_int_outfit]+"] will look to ["+car_outfit_facing[rand_int_begin]+"] side")
      Cars.push(new Car(car_x[rand_int_begin],car_y[rand_int_begin],car_start[rand_int_begin],car_direction[rand_int_end],car_outfit[rand_int_outfit],car_outfit_facing[rand_int_begin]))
      return;
    }
  }
}
var Cars = [];
var CarId=0;
var Stoplichten=[];
var stoplichtTime=0;
var stoplichtTrigger=0;
var spawnTime=0;
var spawnTrigger=0;
var frames=0;
function draw(){
  background("GREEN");
  //debugLines();
  drawRoads();

  if(stoplichtTime == stoplichtTrigger){
    StoplichtStateChange();
    stoplichtTime=0;
    stoplichtTrigger=int(random(10,100))
  }
  if(spawnTime == spawnTrigger){
    generateRandomCar();
    spawnTime=0;
    spawnTrigger=int(random(50,200))
  }
  if(GAME_DEBUGINFO){
    push();
    fill(33,33,33)
    stroke(0,0,255)
    rect(5,5,345,195);
    fill(255,255,255)
    stroke(0,0,0)
    textSize(16);
    text("Cars:"+Cars.length+"\nStoplichten:"+Stoplichten.length+"\n---",10,20)
    text("spawnTime:"+spawnTime+"\nstoplichtTime:"+stoplichtTime+"\nTotal Frames:"+frames+"\n---",10,80)
    text("Frames left to:\nspawnTime:"+(spawnTrigger-spawnTime)+"\nStoplicht change:"+(stoplichtTrigger-stoplichtTime)+"\n---",150,80)
    text("Kacper Serewis, H4C @Mondriaan",10,160)
    pop();
  }
  spawnTime++
  stoplichtTime++

  for(var x=0; x<Stoplichten.length; x++){
    Stoplichten[x].display();
  }
  for(var x=0; x<Cars.length; x++){
    Cars[x].display();
    Cars[x].move();
  }

  frames++
}
var lastState=0;
function StoplichtStateChange(){
  var r = "RED"; var g = "GREEN"; var y = "YELLOW";
  if(lastState==0){StoplichtenSet(r,r,g,g);lastState=1;}
  else if(lastState==1){StoplichtenSet(y,y,g,g);lastState=2;}
  else if(lastState==2){StoplichtenSet(r,g,g,g);lastState=3;}
  else if(lastState==3){StoplichtenSet(r,g,g,y);lastState=4;}
  else if(lastState==4){StoplichtenSet(g,g,y,r);lastState=5;}
  else if(lastState==5){StoplichtenSet(g,g,r,r);lastState=6;}
  else if(lastState==6){StoplichtenSet(g,y,r,y);lastState=7;}
  else if(lastState==7){StoplichtenSet(g,r,y,g);lastState=8;}
  else if(lastState==8){StoplichtenSet(y,y,g,g);lastState=9;}
  else if(lastState==9){StoplichtenSet(r,g,g,g);lastState=10;}
  else if(lastState==10){StoplichtenSet(r,g,y,g);lastState=11;}
  else if(lastState==11){StoplichtenSet(y,g,r,y);lastState=12;}
  else if(lastState==12){StoplichtenSet(g,y,r,r);lastState=13;}
  else if(lastState==13){StoplichtenSet(g,r,r,r);lastState=14;}
  else if(lastState==14){StoplichtenSet(g,r,y,y);lastState=15;}
  else if(lastState==15){StoplichtenSet(y,y,g,g);lastState=0;}


}
function StoplichtenSet(left,down,right,up){
  Stoplichten[0].setColor(left);
  Stoplichten[1].setColor(down);
  Stoplichten[2].setColor(right);
  Stoplichten[3].setColor(up);
}
function Stoplicht(location){
  this.takenPlaces=0;
  this.greenfield = "WHITE"
  this.yellowfield= "WHITE"
  this.redfield="WHITE"
  this.lastcolor="WHITE"
  this.action="GO"
  if(location=="left"){
    this.x =475
    this.y =475
    this.rectsizex=100
    this.rectsizey=50
    this.lightx =[25,50,75]
    this.lighty =[25,25,25]
    this.palex=this.x-25
    this.paley=this.y+12
    this.palesizex=25
    this.palesizey=24
  }
  if(location=="down"){
    this.x =825
    this.y =475
    this.rectsizex=50
    this.rectsizey=100
    this.lightx =[25,25,25]
    this.lighty =[75,50,25]
    this.palex=this.x+12
    this.paley=this.y+100
    this.palesizex=24
    this.palesizey=25
  }
  if(location=="right"){
      this.x =825
      this.y =175
      this.rectsizex=100
      this.rectsizey=50
      this.lightx=[75,50,25]
      this.lighty=[25,25,25]
      this.palex=this.x+100
      this.paley=this.y+12
      this.palesizex=25
      this.palesizey=24
  }
  if(location=="up"){
    this.x =525
    this.y =125
    this.rectsizex=50
    this.rectsizey=100
    this.lightx=[25,25,25]
    this.lighty=[25,50,75]
    this.palex=this.x+12
    this.paley=this.y-25
    this.palesizex=24
    this.palesizey=25
  }
  this.display = function(){
    push();
    fill(33,33,33);
    rect(this.x,this.y,this.rectsizex,this.rectsizey)
    rect(this.palex,this.paley,this.palesizex,this.palesizey)
    ellipse(this.x+this.lightx[0],this.y+this.lighty[0],25,25)
    fill(this.greenfield)
    ellipse(this.x+this.lightx[0],this.y+this.lighty[0],25,25) //green

    fill(this.yellowfield)
    ellipse(this.x+this.lightx[1],this.y+this.lighty[1],25,25) //yellow

    fill(this.redfield)
    ellipse(this.x+this.lightx[2],this.y+this.lighty[2],25,25) //green
    pop();
  }
  this.resetColors = function(){
    this.greenfield = "WHITE"
    this.yellowfield= "WHITE"
    this.redfield="WHITE"
  }
  this.setColor = function(color){
    this.resetColors();
    if(color == "GREEN"){ this.action="GO"; this.greenfield=color};
    if(color == "YELLOW"){ this.yellowfield=color};
    if(color == "RED"){ this.action="STOP"; this.redfield=color};
  }
  this.takePlace = function(number){
    this.takenPlaces=number;
  }
}
function Car(x,y,startpos,destination,outfit,outfit_facing){
  this.x =x;
  this.y =y;
  this.id=CarId; CarId++;
  this.speed = 5;
  this.startpos = startpos;
  this.destination = destination;
  this.size  = 50;
  this.outfit = outfit;
  this.outfit_facing=outfit_facing;
  this.stopped=false;
  this.display = function(){
    push();
    if(this.outfit_facing=="right"){translate(this.x,this.y);}
    if(this.outfit_facing=="left"){translate(this.x+this.size,this.y+this.size); rotate(radians(180));}
    if(this.outfit_facing=="down"){translate(this.x+this.size,this.y); rotate(radians(90));}
    if(this.outfit_facing=="up"){translate(this.x,this.y+this.size); rotate(radians(270));}
    image(outfit,0,0)
    pop();
    push();
    if(CAR_DEBUGINFO){
      noStroke();
      fill("RED");
      fill("WHITE");
      text("x:"+this.x+"\ny:"+this.y+"\n"+this.startpos+"\n"+this.destination,this.x,this.y+10);
    }
    pop();
  }
  this.move = function(){
    if((this.x>1500 || this.x<-100)||(this.y>800 || this.y<-100)){removefromCarsArray(this.id)} //remove cars outside canvas
    if(this.startpos=="right"){
      if((Stoplichten[2].action=="STOP"&&this.x<1250&&this.x>800&&this.stopped==false)){
        if((Stoplichten[2].takenPlaces==0&&this.x<850&&this.x>800)){Stoplichten[2].takePlace(1);this.stopped=true;}
        if((Stoplichten[2].takenPlaces==1&&this.x<950&&this.x>900)){Stoplichten[2].takePlace(2);this.stopped=true;}
        if((Stoplichten[2].takenPlaces==2&&this.x<1050&&this.x>1000)){Stoplichten[2].takePlace(3);this.stopped=true;}
        if((Stoplichten[2].takenPlaces==3&&this.x<1150&&this.x>1100)){Stoplichten[2].takePlace(4);this.stopped=true;}
        if((Stoplichten[2].takenPlaces==4&&this.x<1250&&this.x>1200)){Stoplichten[2].takePlace(5);this.stopped=true;}

      }
      if(Stoplichten[2].action=="GO"){this.stopped=false; Stoplichten[2].takePlace(0);}
      if(this.stopped==false){
        if(this.destination=="left") {this.x-=this.speed;}
        else if(this.destination=="up"&&this.x==725){this.y-=this.speed; this.outfit_facing="up";}
        else if(this.destination=="down"&&this.x==625){this.y+=this.speed; this.outfit_facing="down";}
        else {this.x-=this.speed;}
      }
    }

    if(this.startpos=="left") {
      console.log(Stoplichten[0].action);
      if((Stoplichten[0].action=="STOP"&&this.x>150&&this.x<600&&this.stopped==false)){
        if((Stoplichten[0].takenPlaces==0&&this.x<550&&this.x>500)){Stoplichten[0].takePlace(1);this.stopped=true;}
        if((Stoplichten[0].takenPlaces==1&&this.x<450&&this.x>400)){Stoplichten[0].takePlace(2);this.stopped=true;}
        if((Stoplichten[0].takenPlaces==2&&this.x<350&&this.x>300)){Stoplichten[0].takePlace(3);this.stopped=true;}
        if((Stoplichten[0].takenPlaces==3&&this.x<250&&this.x>200)){Stoplichten[0].takePlace(4);this.stopped=true;}
        if((Stoplichten[0].takenPlaces==4&&this.x<150&&this.x>100)){Stoplichten[0].takePlace(5);this.stopped=true;}
      }
      if(Stoplichten[0].action=="GO"){this.stopped=false; Stoplichten[0].takePlace(0);}
      if(this.stopped==false){
        if(this.destination=="right") {this.x+=this.speed;}
        else if(this.destination=="up"&&this.x==725) {this.y-=this.speed; this.outfit_facing="up";}
        else if(this.destination=="down"&&this.x==625) {this.y+=this.speed; this.outfit_facing="down";}
        else this.x+=this.speed
      }
    }
    if(this.startpos=="up") {
      if((Stoplichten[3].action=="STOP"&&this.y>50&&this.y<250&&this.stopped==false)){
        if((Stoplichten[3].takenPlaces==0&&this.y<200&&this.y>180)){Stoplichten[3].takePlace(1);this.stopped=true;}
        if((Stoplichten[3].takenPlaces==1&&this.y<130&&this.y>110)){Stoplichten[3].takePlace(2);this.stopped=true;}
        if((Stoplichten[3].takenPlaces==2&&this.y<60&&this.y>40)){Stoplichten[3].takePlace(3);this.stopped=true;}
      }

      if(Stoplichten[3].action=="GO"){this.stopped=false; Stoplichten[3].takePlace(0);}
      if(this.stopped==false){
        if(this.destination=="down") {this.y+=this.speed;}
        else if(this.destination=="left"&&this.y==275) {this.x-=this.speed; this.outfit_facing="left";}
        else if(this.destination=="right"&&this.y==375) {this.x+=this.speed; this.outfit_facing="right";}
        else this.y+=this.speed;
      }
    }
    if(this.startpos=="down"){
      if((Stoplichten[1].action=="STOP"&&this.y>450&&this.y<650&&this.stopped==false)){
        if((Stoplichten[1].takenPlaces==0&&this.y<470&&this.y>450)){Stoplichten[1].takePlace(1);this.stopped=true;}
        if((Stoplichten[1].takenPlaces==1&&this.y<540&&this.y>520)){Stoplichten[1].takePlace(2);this.stopped=true;}
        if((Stoplichten[1].takenPlaces==2&&this.y<610&&this.y>590)){Stoplichten[1].takePlace(3);this.stopped=true;}
      }

      if(Stoplichten[1].action=="GO"){this.stopped=false; Stoplichten[1].takePlace(0);}
      if(this.stopped==false){
        if(this.destination=="up") {this.y-=this.speed}
        else if(this.destination=="left"&&this.y==275) {this.x-=this.speed; this.outfit_facing="left";}
        else if(this.destination=="right"&&this.y==375) {this.x+=this.speed; this.outfit_facing="right";}
        else this.y-=this.speed;
      }
     }
  }
}

function drawRoads(){
  push();
  fill(33,33,33);
  noStroke();
  rect(0,250,600,100); //leftUP
  rect(0,350,600,100); //LeftDOWN
  rect(800,250,700,100); //RightUp
  rect(800,350,700,100); //RightDown
  rect(600,0,100,250); //UpLeft
  rect(700,0,100,250); //UpRight
  rect(600,450,100,250); //DownLeft
  rect(700,450,100,250); //DownRight
  rect(600,250,200,200); //Center 600,250 to 800,450
  stroke(255,255,255)
  for(var x=0; x<600; x=x+200){
    line(x,350,x+100,350);
    line(x+900,350,x+900+100,350)
  }
  for(var x=0; x<250; x=x+100){
    line(700,x,700,x+50)
    line(700,x+450,700,x+450+50)
  }
  pop();
}
function debugLines(){
  textSize(12);
  for(var i=0; i<1400;i+=50){
    stroke(250,0,0);
    line(i,0,i,700)
    stroke(0,0,0);
    text(i+"x",i,10);
  }
  for(var i=0; i<700;i+=50){
    stroke(250,0,0);
    line(0,i,1400,i);
    stroke(0,0,0);
    text(i+"y",0,i);
  }
}
