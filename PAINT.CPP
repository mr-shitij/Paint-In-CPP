#include<stdio.h>
#include<math.h>
#include<string.h>
#include<conio.h>
#include<dos.h>
#include<graphics.h>
#include<iostream.h>
void showWindow(char []);
void saveWindow(char []);
int saveLogo(char [], int, int ,int, int);
int showLogo(char [],int, int);
void crop(char []);
class Widgets{
    public:
	Widgets();
	char opValue[30];
	int getXY(int *,int *);
	int Button(char [],int ,int ,int ,int ,int ,int ,int ,int ,int ,int, int);
	int Entry(char [],int ,int ,int ,int ,int ,int ,int ,int ,int ,int, int, int, int);
	int TextButton(char [],char [],int ,int ,int ,int ,int ,int ,int ,int, int, int, int);
	void clearPart(int, int, int, int);
	static int fontMain;
	int colorButton(int, int, int, int, int, int);
	int counter;
	static int controler;
	static int gloableColor;
	void Property(char [],int ,int ,int ,int ,int ,int ,int ,int ,int ,int, int);
};
int Widgets::gloableColor=15;
int Widgets::controler=0;
int Widgets::fontMain=0;

Widgets::Widgets(){
     fontMain=0;
     counter=0;
}
int Widgets::colorButton(int x, int y, int length, int breath, int color, int border){
    int i,j;
    int mouseX,mouseY;
    if(counter==0){
       for(i=x;i<=(x+length);i++){
	  for(j=y;j<=(y+breath);j++){
	      putpixel(i,j,color);
	  }
       }
       counter++;
    }

    setcolor(border);
    rectangle(x,y,(x+length),(y+breath));
    if(getXY(&mouseX, &mouseY)==1){
	if(mouseX >= x && mouseX <= (x+length) && mouseY >= y && mouseY <= (y+breath) ){
		setcolor(border+1);
		rectangle(x,y,(x+length),(y+breath));
		delay(50);
		setcolor(border);
		rectangle(x,y,(x+length),(y+breath));
		gloableColor=color;
		return 1;
	}
    }
    return 0;
}
int Widgets::TextButton(char valueText[], char Buttontext[], int x, int y, int length, int breath, int bStartingX, int bLength, int border,int fillInside, int fillStyle, int font, int fontSize){

    int mouseX,mouseY;
    int textX=x+(((x+length)-x)/4);
    int textY=y+(((y+breath)-y)/4);
    if(counter==0){
	Property(Buttontext,bStartingX,y,bLength,breath,border,fillInside,fillStyle,15,font,0,fontSize);
	rectangle(x, y, (length+x), (breath+y));
	counter++;
    }
    settextstyle(fontMain,0,1);
    setcolor(15);
    outtextxy(textX,textY,valueText);
    if(getXY(&mouseX, &mouseY)==1){
	if(mouseX >= bStartingX && mouseX <= (bStartingX+bLength) && mouseY >= y && mouseY <= (y+breath) ){
		setcolor(border+1);
		rectangle(bStartingX,y,(bStartingX+bLength),(y+breath));
		delay(50);
		setcolor(border);
		rectangle(bStartingX,y,(bStartingX+bLength),(y+breath));
		if(fontMain<12)
		{
		      fontMain++;
		      clearPart(x, y, bStartingX, (y+breath));
		      rectangle(x, y, (length+x), (breath+y));

		}
		else
		     fontMain=0;
		return 1;
	}
    }
    return 0;
}
int Widgets::Entry(char text[], int x, int y, int ipx, int ipy, int length, int breath, int border,int fillInside, int fillStyle, int fontColor, int font, int direction, int fontSize){

    int mouseX,mouseY;
    if(counter==0){
	Property(text,x,y,length,breath,border,fillInside,fillStyle,fontColor,font,direction,fontSize);
	counter++;
     }
     if(getXY(&mouseX, &mouseY)==1){
	if(mouseX >= x && mouseX <= (x+length) && mouseY >= y && mouseY <= (y+breath) ){
	    setcolor(border-1);
	    rectangle(x,y,(x+length),(y+breath));
	    delay(50);
	    setcolor(border);
	    rectangle(x,y,(x+length),(y+breath));
	    gotoxy(ipx,ipy);
	    scanf("%s",opValue);
	    return 1;
	}
     }
     return 0;
}
void Widgets::Property(char text[], int x, int y, int length, int breath, int border,int fillInside, int fillStyle, int fontColor, int font, int direction, int fontSize){

    int textX=x+(((x+length)-x)/4);
    int textY=y+(((y+breath)-y)/4);
    setcolor(border);
    rectangle(x, y, (length+x), (breath+y));
    setfillstyle(fillStyle,fillInside);
    floodfill(length/2+x, breath/2+y,border);
    settextstyle(font,direction,fontSize);
    setcolor(fontColor);
    outtextxy(textX,textY,text);

}
int Widgets::Button(char text[], int x, int y, int length, int breath, int border,int fillInside, int fillStyle, int fontColor, int font, int direction, int fontSize){

    int mouseX,mouseY;
    if(counter==0){
	Property(text,x,y,length,breath,border,fillInside,fillStyle,fontColor,font,direction,fontSize);
	counter++;
    }
    if(getXY(&mouseX, &mouseY)==1){
	if(mouseX >= x && mouseX <= (x+length) && mouseY >= y && mouseY <= (y+breath) ){
		setcolor(border-1);
		rectangle(x,y,(x+length),(y+breath));
		delay(50);
		setcolor(border);
		rectangle(x,y,(x+length),(y+breath));
		return 1;
	}
    }
    return 0;
}
int Widgets::getXY(int *x,int *y){
     union REGS i,o;
     i.x.ax=1;
     int86(0x33,&i,&o);
     i.x.ax=3;
     int86(0x33,&i,&o);
     *x=o.x.cx;
     *y=o.x.dx;
     return o.x.bx;
}
void Widgets::clearPart(int x1, int y1, int x2, int y2){
     int i,j;
     for(i=x1;i<=x2;i++){
	for(j=y1;j<=y2;j++){
	     putpixel(i,j,getbkcolor());
	}

     }
}
class Drawing:public Widgets{
      public:
	    int DrawRectangle(int, int, int, int, int, int, int, int);
	    int DrawLine(int, int, int, int, int, int, int, int);
	    int DrawCircle(int, int, int, int, int, int, int, int);
	    int DrawEllipse(int, int, int, int, int, int, int, int);
	    int DrawText(int, int, int, int, int, int, int, int);
	    int DrawEreaser(int, int, int, int, int, int, int, int);
	    int DrawDotedLine(int, int, int, int, int, int, int, int);
	    int DrawFill(int, int, int, int, int, int, int, int);
	    static int size;
	    int FillShape(int, int, int, int, int, int, int, int);
	    int SizeButton(char [],int ,int ,int ,int ,int ,int ,int ,int, int, int, int);

      private:
	    void myRectangle();
	    void myLine();
	    void myCircle();
	    void myEllipse();
	    void hideMouse();
	    void myText();
	    void myEreaser();
	    void drawDotedLine(int);
	    void fillColor(int);
	    void Fill();
};
int Drawing::size=30;
int Drawing::SizeButton(char Buttontext[], int x, int y, int length, int breath, int bStartingX, int bLength, int border,int fillInside, int fillStyle, int font, int fontSize){

    int mouseX,mouseY;
    int textX=x+(((x+length)-x)/4);
    int textY=y+(((y+breath)-y)/4);
    char text[5];
    if(counter==0){
	Property(Buttontext,bStartingX,y,bLength,breath,border,fillInside,fillStyle,15,font,0,fontSize);
	rectangle(x, y, (length+x), (breath+y));
	counter++;
    }
    setcolor(15);
    sprintf(text,"%d",size);
    settextstyle(font,0,fontSize);
    moveto(textX,textY);
    outtext(text);
    if(getXY(&mouseX, &mouseY)==1){
	if(mouseX >= bStartingX && mouseX <= (bStartingX+bLength) && mouseY >= y && mouseY <= (y+breath) ){
		setcolor(border+1);
		rectangle(bStartingX,y,(bStartingX+bLength),(y+breath));
		delay(50);
		setcolor(border);
		rectangle(bStartingX,y,(bStartingX+bLength),(y+breath));
		if(size<=30)
		{
		      size++;
		      clearPart(x, y, bStartingX, (y+breath));
		      rectangle(x, y, (length+x), (breath+y));

		}
		else
		     size=0;
		return 1;
	}
    }
    return 0;
}
int Drawing::DrawEreaser(int x, int y, int length, int breath, int border,int fillInside, int fillStyle, int shapeColor){
    int mouseX,mouseY;
    if(counter==0){
	Property("", x, y, length, breath, border, fillInside, fillStyle, fillInside, 1, 0, 1);
	setcolor(shapeColor);
	outtextxy(x+(length/4),y+(breath/4)-5,"E");
	counter++;
    }
    if(getXY(&mouseX, &mouseY)==1){
	if(mouseX >= x && mouseX <= (x+length) && mouseY >= y && mouseY <= (y+breath) ){
		setcolor(13);
		rectangle(x,y,(x+length),(y+breath));
		delay(50);
		setcolor(border);
		rectangle(x,y,(x+length),(y+breath));
		controler=5;
		return 1;
	}
	if(controler==5)
	{
	   myEreaser();
	}
    }
    return 0;

}
void Drawing::myEreaser(){

     int x=0,y=0;
     while(getXY(&x, &y)==1 && (y-size)>140){
	 setcolor(15);
	 hideMouse();
	 setfillstyle(SOLID_FILL, 0);
	 rectangle(x-size,y-size,x+size,y+size);
	 floodfill(x,y,15);
	 delay(1);
	 setcolor(0);
	 rectangle(x-size,y-size,x+size,y+size);
     }
}

int Drawing::FillShape(int x, int y, int length, int breath, int border,int fillInside, int fillStyle, int shapeColor){

    int mouseX,mouseY;
    if(counter==0){
	Property("", x, y, length, breath, border, fillInside, fillStyle, fillInside, 1, 0, 1);
	setcolor(shapeColor);
	outtextxy(x+(length/4),y+(breath/4)-5,"F");
	counter++;
    }
    if(getXY(&mouseX, &mouseY)==1){
	if(mouseX >= x && mouseX <= (x+length) && mouseY >= y && mouseY <= (y+breath) ){
		setcolor(13);
		rectangle(x,y,(x+length),(y+breath));
		delay(50);
		setcolor(border);
		rectangle(x,y,(x+length),(y+breath));
		controler=8;

		return 1;
	}
	if(controler==8)
	{
	      Fill();
	}
    }
    return 0;
}
void Drawing::Fill()
{
     int x,y,i;
     int colorBorder,bk;
     bk=getbkcolor();
     while(getXY(&x,&y)==1 && y>140)
     {
	 for(i=y;i>=140;i--){
	     if((colorBorder=getpixel(x,i))!=bk){
		  break;
	     }
	 }
	 setcolor(gloableColor);
	 hideMouse();
	 setfillstyle(SOLID_FILL, gloableColor);
	 floodfill(x,y,colorBorder);
     }
}

int Drawing::DrawFill(int x, int y, int length, int breath, int border,int fillInside, int fillStyle, int shapeColor){

    int mouseX,mouseY;
    if(counter==0){
	Property("", x, y, length, breath, border, fillInside, fillStyle, fillInside, 1, 0, 1);
	setcolor(shapeColor);
	setfillstyle(SOLID_FILL, shapeColor);
	circle(x+(length/2),y+(breath/2),5);
	floodfill(x,y,shapeColor);
	counter++;
    }
    if(getXY(&mouseX, &mouseY)==1){
	if(mouseX >= x && mouseX <= (x+length) && mouseY >= y && mouseY <= (y+breath) ){
		setcolor(13);
		rectangle(x,y,(x+length),(y+breath));
		delay(50);
		setcolor(border);
		rectangle(x,y,(x+length),(y+breath));
		controler=7;
		return 1;
	}
	if(controler==7)
	{
	      fillColor(gloableColor);
	}
    }
    return 0;
}
void Drawing::fillColor(int color)
{
     int x,y;
     while(getXY(&x,&y)==1 && y>140)
     {
	 setcolor(color);
	 hideMouse();
	 setfillstyle(SOLID_FILL, color);
	 circle(x,y,5);
	 floodfill(x,y,color);
     }

}
int Drawing::DrawDotedLine(int x, int y, int length, int breath, int border,int fillInside, int fillStyle, int shapeColor){    int mouseX,mouseY;
    if(counter==0){
	Property("", x, y, length, breath, border, fillInside, fillStyle, fillInside, 1, 0, 1);
	setcolor(shapeColor);
	outtextxy(x+(length/4), y+(breath/4)-5,"....");
	counter++;
    }
    if(getXY(&mouseX, &mouseY)==1){
	if(mouseX >= x && mouseX <= (x+length) && mouseY >= y && mouseY <= (y+breath) ){
		setcolor(13);
		rectangle(x,y,(x+length),(y+breath));
		delay(50);
		setcolor(border);
		rectangle(x,y,(x+length),(y+breath));
		controler=6;
		return 1;
	}
	if(controler==6)
	{
	      drawDotedLine(gloableColor);
	}
    }
    return 0;
}
void Drawing::drawDotedLine(int color)
{
     int x,y;
     if(getXY(&x,&y)==1 && y>140)
	putpixel(x-2,y,color);
}
int Drawing::DrawText(int x, int y, int length, int breath, int border,int fillInside, int fillStyle, int shapeColor){

    int mouseX,mouseY;
    if(counter==0){
	Property("", x, y, length, breath, border, fillInside, fillStyle, fillInside, 1, 0, 1);
	setcolor(shapeColor);
	outtextxy(x+(length/4),y+(breath/4)-5,"T");
	counter++;
    }
    if(getXY(&mouseX, &mouseY)==1){
	if(mouseX >= x && mouseX <= (x+length) && mouseY >= y && mouseY <= (y+breath) ){
		setcolor(13);
		rectangle(x,y,(x+length),(y+breath));
		delay(50);
		setcolor(border);
		rectangle(x,y,(x+length),(y+breath));
		controler=9;
		return 1;
	}
	if(controler==9)
	{
	   myText();
	   controler++;
	}
    }
    return 0;

}
void Drawing::myText(){
     int x=0,y=0;
     char ch,str[30];
     int a=0;
     getXY(&x, &y);
     while((ch=getch())!=13)
     {
	a=(a<0) ? 0 : a;
	if(ch==8)
	{
	    a--;
	    continue;
	}
	str[a]=ch;
	a++;
     }
     str[a]='\0';
     while(getXY(&x, &y)!=1){
     }
     hideMouse();
     setcolor(gloableColor);
     settextstyle(fontMain,0,1);
     outtextxy(x,y,str);
     getXY(&x,&y);
}
void Drawing::hideMouse(){
     union REGS i,o;
     i.x.ax=2;
     int86(0x33,&i,&o);
}
int Drawing::DrawEllipse(int x, int y, int length, int breath, int border,int fillInside, int fillStyle, int shapeColor){    int mouseX,mouseY;
    if(counter==0){
	setlinestyle(SOLID_LINE,1,1);
	Property("", x, y, length, breath, border, fillInside, fillStyle, fillInside, 1, 0, 1);
	setcolor(shapeColor);
	ellipse(x+(length/2),y+(breath/2),0,360,5,10);
	counter++;
    }
    if(getXY(&mouseX, &mouseY)==1){
	if(mouseX >= x && mouseX <= (x+length) && mouseY >= y && mouseY <= (y+breath) ){
		setlinestyle(SOLID_LINE,1,1);
		setcolor(13);
		rectangle(x,y,(x+length),(y+breath));
		delay(50);
		setcolor(border);
		rectangle(x,y,(x+length),(y+breath));
		controler=4;
		return 1;
	}
	if(controler==4)
	myEllipse();
    }
    return 0;

}
void Drawing::myEllipse(){

     int x=0,y=0,x1=0,y1=0;
     int c=0,length,breath,xr1=0,yr1=0,xr2=0,yr2=0;
     union REGS i,o;
     while(getXY(&x,&y)==1 && y>135)
     {
	  if(c==0)
	  {
	       x1=x;
	       y1=y;
	       c++;
	  }
	  setcolor(gloableColor);
	  xr1=x-x1,xr2=x1-x;
	  yr1=y-y1,yr2=y1-y;
	  ellipse(x1, y1, 0, 360, (x>x1)? xr1:xr2, (y>y1)? yr1:yr2);
	  setcolor(getbkcolor());
	  ellipse(x1, y1, 0, 360, (x>x1)? xr1:xr2, (y>y1)? yr1:yr2);
	  if((y-(y-y1))<140 || (y1-yr1)< 140 ||(y1-yr2)< 140)
		break;
	  else
		continue;

     }
     if(c==1)
     {
	setcolor(gloableColor);
	hideMouse();
	ellipse(x1, y1, 0, 360, (x>x1)? xr1:xr2, (y>y1)? yr1:yr2);
	getXY(&x,&y);
     }
}
int Drawing::DrawCircle(int x, int y, int length, int breath, int border,int fillInside, int fillStyle, int shapeColor){

    int mouseX,mouseY;
    if(counter==0){
	setlinestyle(SOLID_LINE,1,1);
	Property("", x, y, length, breath, border, fillInside, fillStyle, fillInside, 1, 0, 1);
	setcolor(shapeColor);
	circle(x+(length/2),y+(breath/2),5);
	counter++;
    }
    if(getXY(&mouseX, &mouseY)==1){
	if(mouseX >= x && mouseX <= (x+length) && mouseY >= y && mouseY <= (y+breath) ){
		setlinestyle(SOLID_LINE,1,1);
		setcolor(13);
		rectangle(x,y,(x+length),(y+breath));
		delay(50);
		setcolor(border);
		rectangle(x,y,(x+length),(y+breath));
		controler=3;
		return 1;
	}
	if(controler==3)
	myCircle();
    }
    return 0;
}
void Drawing::myCircle(){

     int x=0,y=0,x1=0,y1=0;
     int c=0,r=0;
     union REGS i,o;
     while(getXY(&x,&y)==1 && y>135)
     {
	  if(c==0)
	  {
	       x1=x;
	       y1=y;
	       c++;
	  }
	  r=x-x1;
	  setcolor(gloableColor);
	  circle(x1,y1,r);
	  setcolor(getbkcolor());
	  circle(x1,y1,r);
	  if((y1-r)< 140)
		break;
	  else
		continue;
     }
     if(c==1)
     {
	hideMouse();
	setcolor(gloableColor);
	circle(x1,y1,r);
	getXY(&x,&y);
     }
}

int Drawing::DrawLine(int x, int y, int length, int breath, int border,int fillInside, int fillStyle, int shapeColor){

    int mouseX,mouseY;
    if(counter==0){
	Property("", x, y, length, breath, border, fillInside, fillStyle, fillInside, 1, 0, 1);
	setcolor(shapeColor);
	line(x+5, y+(breath/2), (x+length)-5, y+(breath/2));
	counter++;
    }
    if(getXY(&mouseX, &mouseY)==1){
	if(mouseX >= x && mouseX <= (x+length) && mouseY >= y && mouseY <= (y+breath) ){
		setcolor(13);
		rectangle(x,y,(x+length),(y+breath));
		delay(50);
		setcolor(border);
		rectangle(x,y,(x+length),(y+breath));
		controler=2;
		return 1;
	}
	if(controler==2)
	myLine();
    }
    return 0;
}
void Drawing::myLine(){

     int x=0,y=0,x1=0,y1=0;
     int c=0;
     union REGS i,o;
     while(getXY(&x,&y)==1 && y>135)
     {
	  if(c==0)
	  {
	       x1=x;
	       y1=y;
	       c++;
	  }
	  setcolor(gloableColor);
	  line(x1,y1,x,y);
	  setcolor(getbkcolor());
	  line(x1,y1,x,y);
     }
     if(c==1)
     {
	setcolor(gloableColor);
	line(x1,y1,x,y);
     }
}

int Drawing::DrawRectangle(int x, int y, int length, int breath, int border,int fillInside, int fillStyle, int shapeColor){

    int mouseX,mouseY;
    if(counter==0){
	Property("", x, y, length, breath, border, fillInside, fillStyle, fillInside, 1, 0, 1);
	setcolor(shapeColor);
	rectangle(x+5, y+5, (x+length)-5, (y+breath-5));
	counter++;
    }
    if(getXY(&mouseX, &mouseY)==1){
	if(mouseX >= x && mouseX <= (x+length) && mouseY >= y && mouseY <= (y+breath) ){
		setcolor(13);
		rectangle(x,y,(x+length),(y+breath));
		delay(50);
		setcolor(border);
		rectangle(x,y,(x+length),(y+breath));
		controler=1;
		return 1;
	}
	if(controler==1)
	myRectangle();
    }
    return 0;
}
void Drawing::myRectangle()
{
     int x=0,y=0,x1=0,y1=0;
     int c=0;
     union REGS i,o;
     while(getXY(&x,&y)==1 && y>135)
     {
	  if(c==0)
	  {
	       x1=x;
	       y1=y;
	       c++;
	  }
	  setcolor(gloableColor);
	  rectangle(x1,y1,x,y);
	  setcolor(getbkcolor());
	  rectangle(x1,y1,x,y);
     }
     if(c==1)
     {
	hideMouse();
	setcolor(gloableColor);
	rectangle(x1,y1,x,y);
	getXY(&x,&y);
     }
}
void crop(char logoName[])
{
     int x,y,x1=0,y1=0,x2=0,y2=0;
     int c=0;
     union REGS i,o;
     while(x2==0 & y2==0)
     {
	i.x.ax=1;
	int86(0x33,&i,&o);
	i.x.ax=3;
	int86(0x33,&i,&o);
	x=o.x.cx;
	y=o.x.dx;
	if(o.x.bx==1)
	{
	    if(c==0)
	    {
	       x1=x;
	       y1=y;
	       delay(50);
	       c++;
	    }
	    else
	    {
	       x2=x;
	       y2=y;
	       delay(50);
	       saveLogo(logoName,x1,y1,x2,y2);
	       x1=y1=c=0;
	    }
	    delay(500);
	}
     }
}
int showLogo(char logoName[], int x, int y)
{
    FILE *fp = fopen(logoName, "rb");
    if(fp == NULL){
	return 0;
    }
    char temp[255];
    int length, breath;
    fscanf(fp, "%s", &temp);
    fscanf(fp, "%d %d", &length, &breath);
    fscanf(fp, "%s", &temp);
    for(int i=0;i<breath;i++){
	  for(int j=0;j<length;j++){
	    int r, g, b;
	    fscanf(fp, "%d %d %d ", &r, &g, &b);
	    if(r==0 && b==0 && g==0)
		putpixel(x+j, y+i, BLACK);

	    else if(r==0 && g==0 && b==255)
		putpixel(x+j, y+i, BLUE);

	    else if(r==0 && g==200 && b==0)
		putpixel(x+j, y+i, GREEN);

	    else if(r==0 && g==255 && b==255)
		putpixel(x+j, y+i, CYAN);

	    else if(r==255 && g==0 && b==0)
		putpixel(x+j, y+i, RED);

	    else if(r==255 && g==0 && b==255)
		putpixel(x+j, y+i, MAGENTA);

	    else if(r==165 && g==42 && b==42)
		putpixel(x+j, y+i, BROWN);

	    else if(r==56 && g==93 && b==56)
		putpixel(x+j, y+i, LIGHTGRAY);

	    else if(r==169 && g==169 && b==169)
		putpixel(x+j, y+i, DARKGRAY);

	    else if(r==135 && g==206 && b==250)
		putpixel(x+j, y+i, LIGHTBLUE);

	    else if(r==50 && g==205 && b==50)
		putpixel(x+j, y+i, LIGHTGREEN);

	    else if(r==88 && g==100 && b==100)
		putpixel(x+j, y+i, LIGHTCYAN);

	    else if(r==220 && g==20 && b==60)
		putpixel(x+j, y+i, LIGHTRED);

	    else if(r==231 && g==139 && b==231)
		putpixel(x+j, y+i, LIGHTMAGENTA);

	    else if(r==255 && g==255 && b==0)
		putpixel(x+j, y+i, YELLOW);

	    else if(r==255 && g==255 && b==255)
		putpixel(x+j, y+i, WHITE);

	    else
		putpixel(x+j, y+i, BLACK);
	}
    }
    fclose(fp);
    return 1;
}
int saveLogo(char nameOfLogo[], int x1, int y1, int x2, int y2)
{
     FILE *pgmimg=fopen(nameOfLogo,"wb");
     if(pgmimg==NULL)
		return 0;
     int length=x2-x1;
     int breath=y2-y1;
     fprintf(pgmimg, "P3\n");
     fprintf(pgmimg, "%d %d\n", length , breath);
     fprintf(pgmimg, "255\n");
     for(int i=0; i < breath;i++){
	 for(int j=0; j < length;j++){
	     int temp = getpixel(x1+j,y1+i);
	     if(temp==BLACK)
		  fprintf(pgmimg, "%d %d %d ", 0,0,0);

	     else if(temp==BLUE)
		  fprintf(pgmimg, "%d %d %d ", 0,0,255);

	     else if(temp==GREEN)
		  fprintf(pgmimg, "%d %d %d ",0,200,0);

	     else if(temp==CYAN)
		  fprintf(pgmimg, "%d %d %d ",0,255,255);

	     else if(temp==RED)
		  fprintf(pgmimg, "%d %d %d ",255,0,0);

	     else if(temp==MAGENTA)
		  fprintf(pgmimg, "%d %d %d ",255,0,255);

	     else if(temp==BROWN)
		  fprintf(pgmimg, "%d %d %d ",165,42,42);

	     else if(temp==LIGHTGRAY)
		  fprintf(pgmimg, "%d %d %d ",56,93,56);

	     else if(temp==DARKGRAY)
		  fprintf(pgmimg, "%d %d %d ",169,169,169);

	     else if(temp==LIGHTBLUE)
		  fprintf(pgmimg, "%d %d %d ",135,206,250);

	     else if(temp==LIGHTGREEN)
		  fprintf(pgmimg, "%d %d %d ",50,205,50);

	     else if(temp==LIGHTCYAN)
		  fprintf(pgmimg, "%d %d %d ", 88,100,100);

	     else if(temp==LIGHTRED)
		  fprintf(pgmimg, "%d %d %d ", 220,20,60);

	     else if(temp==LIGHTMAGENTA)
		  fprintf(pgmimg, "%d %d %d ",231, 139, 231);

	     else if(temp==YELLOW)
		  fprintf(pgmimg, "%d %d %d ",255,255,0);

	     else if(temp==WHITE)
		  fprintf(pgmimg, "%d %d %d ",255,255,255);
	  }
     }
     fprintf(pgmimg, "\n");
     fclose(pgmimg);
     return 1;
}
void saveWindow(char fileName[])
{
     FILE *pgmimg = fopen(fileName,"wb");
     if (pgmimg == NULL)
       return ;
     int length=639;
     int breath=339;
     fprintf(pgmimg, "P3\n");
     fprintf(pgmimg, "%d %d\n", length , breath);
     fprintf(pgmimg, "255\n");
     for(int i=0; i < 479;i++){
	 for(int j=0; j < 639;j++){
	     int temp = getpixel(j,i);
	     if(temp==BLACK)
		  fprintf(pgmimg, "%d %d %d ", 0,0,0);

	     else if(temp==BLUE)
		  fprintf(pgmimg, "%d %d %d ", 0,0,255);

	     else if(temp==GREEN)
		  fprintf(pgmimg, "%d %d %d ",0,200,0);

	     else if(temp==CYAN)
		  fprintf(pgmimg, "%d %d %d ",0,255,255);

	     else if(temp==RED)
		  fprintf(pgmimg, "%d %d %d ",255,0,0);

	     else if(temp==MAGENTA)
		  fprintf(pgmimg, "%d %d %d ",255,0,255);

	     else if(temp==BROWN)
		  fprintf(pgmimg, "%d %d %d ",165,42,42);

	     else if(temp==LIGHTGRAY)
		  fprintf(pgmimg, "%d %d %d ",56,93,56);

	     else if(temp==DARKGRAY)
		  fprintf(pgmimg, "%d %d %d ",169,169,169);

	     else if(temp==LIGHTBLUE)
		  fprintf(pgmimg, "%d %d %d ",135,206,250);

	     else if(temp==LIGHTGREEN)
		  fprintf(pgmimg, "%d %d %d ",50,205,50);

	     else if(temp==LIGHTCYAN)
		  fprintf(pgmimg, "%d %d %d ", 88,100,100);

	     else if(temp==LIGHTRED)
		  fprintf(pgmimg, "%d %d %d ", 220,20,60);

	     else if(temp==LIGHTMAGENTA)
		  fprintf(pgmimg, "%d %d %d ",231, 139, 231);

	     else if(temp==YELLOW)
		  fprintf(pgmimg, "%d %d %d ",255,255,0);

	     else if(temp==WHITE)
		  fprintf(pgmimg, "%d %d %d ",255,255,255);
	  }
     }
     fprintf(pgmimg, "\n");
     fclose(pgmimg);
}
void showWindow(char fileName[])
{

    FILE *fp = fopen(fileName, "rb");
    if(fp == NULL){
	return;
    }
    char temp[255];
    int length, breath, x=0, y=140;
    fscanf(fp, "%s", &temp);
    fscanf(fp, "%d %d", &length, &breath);
    fscanf(fp, "%s", &temp);
    for(int i=0;i<breath;i++){
	  for(int j=0;j<length;j++){
	    int r, g, b;
	    fscanf(fp, "%d %d %d ", &r, &g, &b);
	    if(r==0 && b==0 && g==0)
		putpixel(x+j, y+i, BLACK);

	    else if(r==0 && g==0 && b==255)
		putpixel(x+j, y+i, BLUE);

	    else if(r==0 && g==200 && b==0)
		putpixel(x+j, y+i, GREEN);

	    else if(r==0 && g==255 && b==255)
		putpixel(x+j, y+i, CYAN);

	    else if(r==255 && g==0 && b==0)
		putpixel(x+j, y+i, RED);

	    else if(r==255 && g==0 && b==255)
		putpixel(x+j, y+i, MAGENTA);

	    else if(r==165 && g==42 && b==42)
		putpixel(x+j, y+i, BROWN);

	    else if(r==56 && g==93 && b==56)
		putpixel(x+j, y+i, LIGHTGRAY);

	    else if(r==169 && g==169 && b==169)
		putpixel(x+j, y+i, DARKGRAY);

	    else if(r==135 && g==206 && b==250)
		putpixel(x+j, y+i, LIGHTBLUE);

	    else if(r==50 && g==205 && b==50)
		putpixel(x+j, y+i, LIGHTGREEN);

	    else if(r==88 && g==100 && b==100)
		putpixel(x+j, y+i, LIGHTCYAN);

	    else if(r==220 && g==20 && b==60)
		putpixel(x+j, y+i, LIGHTRED);

	    else if(r==231 && g==139 && b==231)
		putpixel(x+j, y+i, LIGHTMAGENTA);

	    else if(r==255 && g==255 && b==0)
		putpixel(x+j, y+i, YELLOW);

	    else if(r==255 && g==255 && b==255)
		putpixel(x+j, y+i, WHITE);

	    else
		putpixel(x+j, y+i, BLACK);
	}
    }
    fclose(fp);
}

int main(){
    int gd=DETECT,gm,x=0,y=0;
    char str[30];
    Widgets w1,file[10],color[16],about,border,clear,ShowXY;
    Drawing d1[9],w2;
    initgraph(&gd,&gm,"C:\\TC\\BGI");
    line(0,125,645,125);
    line(0,130,645,130);
    while(1){

	setcolor(border.gloableColor);
	rectangle(0,130,630,450);
	if(1==(file[0].Button("Open logo",5,5,95,25,3,12,1,4,2,0,4))){
		while(1!=(file[6].Entry("", 5, 95, 3, 7, 210, 20, 8, 0, 1, 15, 1, 0, 2))){
		}
		showLogo(file[6].opValue, 10, 160);
		file[6].clearPart(5, 95, 215, 115);
	}
	if(file[1].Button("Open window",110,5,110,25,3,12,1,4,2,0,4)==1){
		while(1!=(file[7].Entry("", 5, 95, 3, 7, 210, 20, 8, 0, 1, 15, 1, 0, 2))){
		}
		showWindow(file[7].opValue);
		file[7].clearPart(5, 95, 215, 115);
	}
	if(file[2].Button("Save logo",5,35,95,25,3,12,1,4,2,0,4)==1){
		while(1!=(file[8].Entry("", 5, 95, 3, 7, 210, 20, 8, 0, 1, 15, 1, 0, 2))){
		}
		crop(file[8].opValue);
		file[8].clearPart(5, 95, 215, 115);
	}
	if(file[3].Button("Save window",110,35,110,25,3,12,1,4,2,0,4)==1){
		while(1!=(file[9].Entry("", 5, 95, 3, 7, 210, 20, 8, 0, 1, 15, 1, 0, 2))){
		}
		saveWindow(file[9].opValue);
		file[9].clearPart(5, 95, 215, 115);
	}
	if(file[4].Button("Exit",5,65,40,25,3,12,1,4,2,0,4)==1){
	      closegraph();
	      return(0);
	}
	if(file[5].Button("About Developer",50,65,170,25,3,12,1,4,2,0,4)==1){
	      about.clearPart(0,140,600,440);
	      setcolor(1);
	      rectangle(70,180,600,390);
	      settextstyle(3,0,4);
	      setcolor(15);
	      outtextxy(80,200,"This Program is Developded By : ");
	      settextstyle(2,0,4);
	      outtextxy(100,300,"Master: Shitij Shailendra Agrawal");
	      getch();
	}
	if(1==(w1.TextButton("font","Next", 225, 5, 235, 55, 375, 85, 15, 12, 1, 2, 4))){
	}
	if(1==(w2.SizeButton("Next", 465, 90, 150, 25, 550, 65, 5, 12, 1, 1, 1))){
	}
	//color

	if(1==(color[0].colorButton(225,65,25,25,0,15))){
	}
	if(1==(color[1].colorButton(255,65,25,25,1,15))){
	}
	if(1==(color[2].colorButton(285,65,25,25,2,15))){
	}
	if(1==(color[3].colorButton(315,65,25,25,3,15))){
	}
	if(1==(color[4].colorButton(345,65,25,25,4,15))){
	}
	if(1==(color[5].colorButton(375,65,25,25,5,15))){
	}
	if(1==(color[6].colorButton(405,65,25,25,6,15))){
	}
	if(1==(color[7].colorButton(435,65,25,25,7,15))){
	}
	if(1==(color[8].colorButton(225,95,25,25,8,15))){
	}
	if(1==(color[9].colorButton(255,95,25,25,9,15))){
	}
	if(1==(color[10].colorButton(285,95,25,25,10,15))){
	}
	if(1==(color[11].colorButton(315,95,25,25,11,15))){
	}
	if(1==(color[12].colorButton(345,95,25,25,12,15))){
	}
	if(1==(color[13].colorButton(375,95,25,25,13,15))){
	}
	if(1==(color[14].colorButton(405,95,25,25,14,15))){
	}
	if(1==(color[15].colorButton(435,95,25,25,15,15))){
	}
	if(d1[0].DrawRectangle(465, 5, 20, 20, 15, 12, 1, 0)){
	}
	if(d1[1].DrawLine(495, 5, 20, 20, 15, 12, 1, 0)){
	}
	if(d1[2].DrawCircle(525, 5, 20, 20, 15, 12, 1, 0)){
	}
	if(d1[3].DrawEllipse(465, 35, 20, 20, 15, 12, 1, 0)){
	}
	if(d1[4].DrawText(495, 35, 20, 20, 15, 12, 1, 0)){
	}
	if(d1[5].DrawEreaser(525, 35, 20, 20, 15, 12, 1, 0)){
	}
	if(d1[6].DrawDotedLine(465, 65, 20, 20, 15, 12, 1, 0)){
	}
	if(d1[7].DrawFill(495, 65, 20, 20, 15, 12, 1, 0)){
	}
	if(d1[8].FillShape(525, 65, 20, 20, 15, 12, 1, 0)){
	}
	if(clear.Button("Clear", 555, 5, 30, 80, 15, 12, 1, 0, 1, 1, 1)==1){
	   clear.clearPart(0,130,640,450);
	}
	ShowXY.getXY(&x,&y);
	sprintf(str,"X: %d, Y: %d",x,y);
	settextstyle(0, 0, 1);
	outtextxy(0,140,str);
	delay(50);
	clear.clearPart(0,140,110,160);

    }
}
