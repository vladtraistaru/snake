#include <string.h>
#include <fstream.h>
#include <iomanip.h>
#include <math.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream.h>
#include <dos.h>
#define ESC 0x1b
#define SUS 0x48
#define JOS 0x50
#define STG 0x4b
#define DR 0x4d

void *buf[3];

struct snake{
	int x, y, sens;
	} sarpe[1000], ultim;

int limita, randx, randy, sunet, start;
float viteza, viteza_joc, scor=0, scor_max;
char viteza_ch[10], nume[30], scor_ch[10], scor_max_ch[10], v[10];
void bip(int frecventa, int durata);
void minifer();
void plansa();
void inceput();
void dead();
void randomeaza();
void snake();
int mutare(int dir);

void bip(int frecventa, int durata)
{
	sound(frecventa);
	delay(durata);
	nosound();
}

void minifer()
{
	int maxx, maxy;
	maxx=getmaxx();
	maxy=getmaxy();
	setcolor(WHITE);
	rectangle(maxx/2-100, maxy/2+100-9, maxx/2+100, maxy/2+127-9);
	rectangle(maxx/2-100+1, maxy/2+100-9+1, maxx/2+100-1, maxy/2+127-9-1);
	setcolor(RED);
	rectangle(maxx/2-100+2, maxy/2+100-9+2, maxx/2+100-2, maxy/2+127-9-2);
	setcolor(WHITE);
	rectangle(maxx/2-100+3, maxy/2+100-9+3, maxx/2+100-3, maxy/2+127-9-3);
	rectangle(maxx/2-100+4, maxy/2+100-9+4, maxx/2+100-4, maxy/2+127-9-4);
	line(maxx/2-100+7, maxy/2+127-9, maxx/2-100+7, maxy/2+127-9+7);
	line(maxx/2-100+7, maxy/2+127-9+7, maxx/2+100+7, maxy/2+127-9+7);
	line(maxx/2+100+7, maxy/2+127-9+7, maxx/2+100+7, maxy/2+100-9+7);
	line(maxx/2+100+7, maxy/2+100-9+7, maxx/2+100, maxy/2+100-9+7);
	setfillstyle(CLOSE_DOT_FILL, WHITE);
	floodfill(maxx/2, maxy/2+127-8, WHITE);
	setfillstyle(SOLID_FILL, RED);
	floodfill(maxx/2, maxy/2+105, WHITE);
}

void plansa()
{
	int marime, maxx, maxy;
	maxx=getmaxx();
	maxy=getmaxy();
	cleardevice();
	//!!!!!!!!!!!!!  SCORUL  !!!!!!!!
	settextstyle(2, HORIZ_DIR, 7);
	outtextxy(maxx/2-204, 45, "Scorul:");
	outtextxy(maxx/2-205, 45, "Scorul");
	rectangle(maxx/2-124, 45, maxx/2-5, 66);
	setfillstyle(SOLID_FILL, MAGENTA);
	floodfill(maxx/2-60, 60, WHITE);
	settextstyle(2, HORIZ_DIR, 7);
	outtextxy(maxx/2-120, 44, "0");
	//!!!!!!!!!!!!!  VIETZA   !!!!!!!!!!
	settextstyle(2, HORIZ_DIR, 7);
	outtextxy(maxx/2+5, 45, "Viteza:");
	outtextxy(maxx/2+6, 45, "Viteza");
	rectangle(maxx/2+83, 45, maxx/2+202, 66);
	setfillstyle(SOLID_FILL, MAGENTA);
	floodfill(maxx/2+85, 60, WHITE);
	sprintf(viteza_ch, "%f", 11-(viteza_joc/20));
	settextstyle(2, HORIZ_DIR, 7);
	outtextxy(maxx/2+88, 44,viteza_ch);
	//!!!!!!!!!!!!!!  NUMELE !!!!!!!!!!!!!!
	setcolor(WHITE);
	settextstyle(2, HORIZ_DIR, 7);
	outtextxy(maxx/2-204, 400, "Numele:");
	outtextxy(maxx/2-205, 400, "Numele");
	setcolor(MAGENTA);
	settextstyle(5, HORIZ_DIR, 3);
	outtextxy(maxx/2-110, 390, nume);
	outtextxy(maxx/2-111, 390, nume);
	//!!!!!!!!!!!!  TASTELE  !!!!!!!!!!!!!!!
	setcolor(WHITE);
	settextstyle(2, HORIZ_DIR, 7);
	outtextxy(maxx/2+20, 395, "P=Pauza");
	outtextxy(maxx/2+21, 395, "P");
	outtextxy(maxx/2+20, 415, "ESC=iesire");
	outtextxy(maxx/2+21, 415, "ESC");
	//!!!!!!!!!!!!  MARGINEA   !!!!!!!!!!!!
	setcolor(RED);
	rectangle(0, 0, maxx, maxy);
	rectangle(1, 1, maxx-1, maxy-1);
	rectangle(2,2 , maxx-2, maxy-2);
	rectangle(3, 3, maxx-3, maxy-3);
	rectangle(4,4 , maxx-4, maxy-4);
	rectangle(5,5 , maxx-5, maxy-5);
	rectangle(5,5 , maxx-5, maxy-5);
	rectangle(6, 6, maxx-6, maxy-6);
	//!!!!!!!!!!!!  CAREUL  !!!!!!!!!!!!!!!
	setbkcolor(GREEN);
	setfillstyle(1, RED);
	bar(maxx/2-200,maxy/2-144, maxx/2+200, maxy/2+144);
	setcolor(WHITE);
	rectangle(maxx/2-201,maxy/2-145, maxx/2+200, maxy/2+144);
	rectangle(maxx/2-202,maxy/2-146, maxx/2+201, maxy/2+145);
	rectangle(maxx/2-203,maxy/2-147, maxx/2+202, maxy/2+146);
	rectangle(maxx/2-205,maxy/2-149, maxx/2+204, maxy/2+148);
	rectangle(maxx/2-206,maxy/2-150, maxx/2+205, maxy/2+149);
	//!!!!!!!!!!!!!!  INCEPUTUL SARPELUI !!!!!!!!!!!!!!!
	limita = 3;
	sarpe[0].x=maxx/2-8;
	sarpe[0].y=maxy/2-24;
	sarpe[0].sens=8;
	sarpe[1].x=maxx/2-8;
	sarpe[1].y=maxy/2-16;
	sarpe[2].x=maxx/2-8;
	sarpe[2].y=maxy/2-8;
	ultim.x=maxx/2-8;
	ultim.y=maxy/2-8;
	putimage(sarpe[0].x, sarpe[0].y, buf[0], 0);
	putimage(sarpe[1].x, sarpe[1].y, buf[0], 0);
	putimage(sarpe[2].x, sarpe[2].y, buf[0], 0);
}
void inceput()
{
char optiune, key;
inceput:

fstream f("snake.txt", ios::in);
if(f){
	cleardevice();
	//careul rosu in jurul palnsei
	setcolor(WHITE);
	int maxx, maxy;
	maxx=getmaxx();
	maxy=getmaxy();
	rectangle(0, maxy, maxx, 0);
	rectangle(1, maxy-1,maxx-1, 1);
	rectangle(2, maxy-2, maxx-2, 2);
	//titlul
	settextstyle(10, HORIZ_DIR, 4);
	outtextxy(238, 70, "SNAKE");
	setfillstyle(1, RED);
	floodfill(258, 100, 15);
	floodfill(278, 100, 15);
	floodfill(312, 100, 15);
	floodfill(341, 100, 15);
	floodfill(373, 100, 15);
	f>>viteza>>sunet>>nume>>scor_max;
	viteza_joc=((10-viteza)+1)*20;
	settextstyle(0, HORIZ_DIR, 1);
	//SE AFISEAZA MENIUL
	//start
	setcolor(DARKGRAY);
	outtextxy(getmaxx()/2-textwidth("1. tart")/2, getmaxy()/2-25,"1. tart");
	setcolor(WHITE);
	outtextxy(getmaxx()/2-textwidth("       ")/2, getmaxy()/2-25,"  S");
	//viteza
	setcolor(DARKGRAY);
	outtextxy(getmaxx()/2-textwidth("3. iteza00")/2, getmaxy()/2-5,"3. iteza");
	setcolor(WHITE);
	outtextxy(getmaxx()/2-textwidth("          ")/2, getmaxy()/2-5,"  V");
	f.close();
	fstream f("snake.txt", ios::in);
	f>>viteza_ch>>sunet>>nume>>scor_max;
	f.close();
	setcolor(GREEN);
	outtextxy(getmaxx()/2-textwidth("10")/2+45, getmaxy()/2-5,viteza_ch);
	//sunet
	setcolor(DARKGRAY);
	outtextxy(getmaxx()/2-textwidth("2.Sunet ")/2, getmaxy()/2-15,"2.Sunet");
	setcolor(WHITE);
	outtextxy(getmaxx()/2-textwidth("        ")/2, getmaxy()/2-15,"    n");
	setcolor(GREEN);
	if(sunet) outtextxy(getmaxx()/2-textwidth("        ")/2+63, getmaxy()/2-15,"ON");
	else  outtextxy(getmaxx()/2-textwidth("        ")/2+63, getmaxy()/2-15,"OFF");
	//scor maxim
	setcolor(DARKGRAY);
	outtextxy(getmaxx()/2-textwidth("4. Scorul Maxim")/2, getmaxy()/2+5,"4. Scorul Maxim");
	setcolor(WHITE);
	outtextxy(getmaxx()/2-textwidth("               ")/2, getmaxy()/2+5,"          M");
	sprintf(scor_max_ch,"%f", scor_max);
	setcolor(GREEN);
	outtextxy(getmaxx()/2+53, getmaxy()/2+5,scor_max_ch);
	//nume
	setcolor(DARKGRAY);
	outtextxy(getmaxx()/2-textwidth("5. Numele Tau ")/2, getmaxy()/2+15,"5. Numele Tau");
	setcolor(WHITE);
	outtextxy(getmaxx()/2-textwidth("              ")/2, getmaxy()/2+15,"    u");
	setcolor(GREEN);
	outtextxy(getmaxx()/2-textwidth("5. Numele tau ")/2+110, getmaxy()/2+15,nume);
	//help
	setcolor(DARKGRAY);
	outtextxy(getmaxx()/2-textwidth("6.Help")/2, getmaxy()/2+25,"6. Help");
	setcolor(WHITE);
	outtextxy(getmaxx()/2-textwidth("      ")/2, getmaxy()/2+25,"   H");
	//exit
	setcolor(DARKGRAY);
	outtextxy(getmaxx()/2-textwidth("7.Exit")/2, getmaxy()/2+35,"7.Exit");
	setcolor(WHITE);
	outtextxy(getmaxx()/2-textwidth("      ")/2, getmaxy()/2+35,"   x");
	//jos de tot
	settextstyle(2, HORIZ_DIR,4);
	setcolor(WHITE);
	outtextxy(getmaxx()/2-textwidth("Apasa tasta corespunzatoare")/2, getmaxy()/2+225,"Apasa tasta corespunzatoare");
	while(optiune=getch()) //pt meniu
	{
		if(optiune==0x00) optiune = getch();
		//setcolor(WHITE);
		switch(optiune)
		{
			case 's' :{
					  plansa();
					  randomeaza();
					  start=1;
					  snake();
					  goto inceput;
					  }
			case 'v' :{
					 if(sunet) bip(400, 50);
					 minifer();
					 settextstyle(2,HORIZ_DIR,5);
					 setcolor(BLUE);
					 outtextxy(getmaxx()/2-textwidth("Viteza (2-10)")/2-20  , getmaxy()/2+95,"Viteza (2-10)");
					 outtextxy(getmaxx()/2-textwidth("Viteza (2-10)")/2-20+1, getmaxy()/2+95,"Viteza (2-10)");
					 gotoxy(46,22);
					 cin>>viteza;
					 if(viteza<2 || viteza>10)
						{
							minifer();
							outtextxy(getmaxx()/2-textwidth("Valoare Incorecta")/2  , getmaxy()/2+95,"Valoare Incorecta");
							outtextxy(getmaxx()/2-textwidth("Valoare Incorecta")/2+1, getmaxy()/2+95,"Valoare Incorecta");
							getch();
						}
					 else
						{
							fstream f("snake.txt", ios::out);
							f<<viteza<<" "<<sunet<<" "<<nume<<" "<<scor_max;
							f.close();
						}
					 goto inceput;
					 }
			case 'n':{
					 if(sunet) bip (400,50);
					 minifer();
					 settextstyle(2,HORIZ_DIR,5);
					 setcolor(BLUE);
					 outtextxy(getmaxx()/2-textwidth("1=ON  0=OFF")/2-20  , getmaxy()/2+95,"1=ON  0=OFF");
					 outtextxy(getmaxx()/2-textwidth("1=ON  0=OFF")/2-20+1, getmaxy()/2+95,"1=ON  0=OFF");
					 gotoxy(46,22);
					 cin>>sunet;
					 if(sunet<0 || sunet>1)
						{
							minifer();
							outtextxy(getmaxx()/2-textwidth("Valoare Incorecta")/2  , getmaxy()/2+95,"Valoare Incorecta");
							outtextxy(getmaxx()/2-textwidth("Valoare Incorecta")/2+1, getmaxy()/2+95,"Valoare Incorecta");
							getch();
						}
					 else
						{
							fstream f("snake.txt", ios::out);
							f<<viteza<<" "<<sunet<<" "<<nume<<" "<<scor_max;
							f.close();
						}
					 goto inceput;
					 }
			case 'm':{
					 if(sunet) bip (400,50);
					 minifer();
					 settextstyle(0,HORIZ_DIR,1);
					 setcolor(BLUE);
					 outtextxy(getmaxx()/2-90  , getmaxy()/2+100,"Scor maxim de");
					 fstream scor_max_fis("smf.txt", ios::in);
					 scor_max_fis>>nume;
					 scor_max_fis.close();
					 outtextxy(getmaxx()/2+20, getmaxy()/2+100,nume);
					 getch();
					 goto inceput;
					 }
			case 'u':{
					 if(sunet) bip (400,50);
					 minifer();
					 settextstyle(2,HORIZ_DIR,5);
					 setcolor(BLUE);
					 outtextxy(getmaxx()/2-textwidth("Numele tau")/2-45  , getmaxy()/2+95,"Numele tau");
					 outtextxy(getmaxx()/2-textwidth("Numele tau")/2-45+1, getmaxy()/2+95,"Numele tau");
					 gotoxy(41,22);
					 cin>>nume;
					 fstream f("snake.txt", ios::out);
					 f<<viteza_ch<<" "<<sunet<<" "<<nume<<" "<<scor_max;
					 f.close();
					 goto inceput;
					 }
			case 'h':{
					 if(sunet) bip(400, 50);
					 fstream help("help.txt", ios::in);
					 cleardevice();
					 char ch[10];
					 settextstyle(6, HORIZ_DIR, 3);
					 int pozitia;
					 for(int i=10; i<475 && !help.eof();)
						{
						for(int j=5;j<630 && !help.eof();)
							{
							pozitia = help.tellp();
							help>>ch;
							if(j+textwidth(ch) > 630)
							{
								help.seekp(pozitia, ios::beg);
								break;
							}
							outtextxy(i, j, ch);
							j+=textwidth(ch)+7;
							delay(20);
							}
						i+=textheight(ch+5);
						}
					 help.close();
					 settextstyle(2, HORIZ_DIR, 5);
					 setcolor(BLUE);
					 outtextxy(150, 460, "Press any key to exit...");
					 getch();
					 goto inceput;
					 }
			case 'x':{
					 if(sunet) {
							   bip(300, 150); bip(200, 150);
							   bip(100, 150); bip(50, 150);
							   bip(20, 150);
							   }
					 cleardevice();
					 exit(1);
					 }
			case ESC:
					 {
					 if(sunet) {
							   bip(300, 150); bip(200, 150);
							   bip(100, 150); bip(50, 150);
							   bip(20, 150);
							   }
					 cleardevice();
					 exit(1);
					 }
			default:
					{
					if(sunet) bip(120, 150);
					goto inceput;
					}
		} // NU ARE VOIE SA AJUNGA AICI !!!!!!!!!
	inceput();
	} // de la while
	}
else
	{//nu exitsa fisierul adica e prima data cand rulezi programul
	fstream scor_max_fis("smf.txt", ios::out);
	scor_max_fis<<"Vlad";  // hehe, normal ca eu, nu ?
	scor_max_fis.close();
	fstream f("snake.txt", ios::out);
	cout<<"\n\n\n    Este pt ptima data cand folosesti programul";
	cout<<"\n\nIntrodu optiunile initale";
	cout<<"\n\nViteza de la 1 la 10";
	cin >> viteza;
	f<<viteza<<" ";
	cout<<"Sunet 1==ON 0==OFF: ";
	cin>>sunet;
	f<<sunet<<" ";
	cout<<"Numele tau (pt a salva scorurile maxime";
	cin>>nume;
	f<<nume<<" ";
	scor_max=300;
	f<<scor_max;
	f.close();
	inceput();
	}
}

void dead()
{
   setbkcolor(BLACK);
   delay(120);
   setbkcolor(WHITE);
   delay(120);
   setbkcolor(BLACK);
   delay(120);
   setbkcolor(WHITE);
   delay(120);
   setbkcolor(BLACK);
   delay(120);
   setbkcolor(WHITE);
   delay(120);
   setbkcolor(GREEN);
   start=0;
   if(sunet){
	   bip(300, 150);  bip(200, 150);
	   bip(100, 150);  bip( 50, 150);
	   bip( 20, 150);
			}
   setcolor(YELLOW);
   settextstyle(7, HORIZ_DIR, 5);
   outtextxy(getmaxx()/2-130, getmaxy()/2-100, "AI MURIT !!!");
   outtextxy(getmaxx()/2-129, getmaxy()/2-100, "AI MURIT !!!");
   sprintf(scor_ch, "%f puncte", scor);
   settextstyle(7, HORIZ_DIR, 5);
   outtextxy(getmaxx()/2-198, getmaxy()/2, scor_ch);
   if(scor > scor_max)
   {
		fstream f ("snake.txt", ios::out);
		f<<viteza_ch<<" "<<sunet<<" "<<nume<<" "<<scor;
		f.close();
   }
   delay (1500);
   getch();
   setbkcolor(BLACK);
   scor=0;
   inceput(); //o ia de la capat
}

void randomeaza()
{
	struct time t;
	int a, x;
	//pe horiz (199 --- 519)
	gettime(&t);
	a=x=int(t.ti_hund);
	if(a>=2) x= ((a+1)/2*8)+111;
	else x=(a*8)+119;
	randx=x;
	//pe verticala(95 --- 383)
	gettime(&t);
	a=x=int (t.ti_hund);
	if( ((a+1)/2)<37)
	{
		if(a>2) x=((a+1)/2*8)+87;
		else x=(a*8)+95;
	}
	else
	{
		a=-73;
		if(a>=2) x=((a+1)/2*8)+87;
		else x=(a*8)+95;
	}
	randy=x;
	if( getpixel(randx, randy) == YELLOW ) randomeaza(); //daca e ocupat
	else putimage(randx, randy, buf[2], 0);
}

int mutare(int dir)
{
	if(dir==0) return 1;
	if(dir+sarpe[0].sens == 10) //daca da su spatele, NU moare !!!
	{
		mutare(sarpe[0].sens);
		return 1;
	}
	ultim.x=sarpe[limita-1].x;
	ultim.y=sarpe[limita-1].y;
	for(int i=limita; i>1; i--)//for in care se schimba coordonatele fiecarui patrat in afara de sarpe[0] in fct de cel de dinainte
	{
		sarpe[i-1].x = sarpe[i-2].x;
		sarpe[i-1].y = sarpe[i-2].y;
	}
	switch(dir) //se schimba sarpe[0].sens si coordonatele lui sarpe[0] in fct de directia primita
	{
		case 8:{
				sarpe[0].sens = 8;
				sarpe[0].y -= 8;
				break;
				}
		case 2:{
				sarpe[0].sens = 2;
				sarpe[0].y += 8;
				break;
				}
		case 6:{
				sarpe[0].sens = 6;
				sarpe[0].x += 8;
				break;
				}
		case 4:{
				sarpe[0].sens = 4;
				sarpe[0].x -= 8;
				break;
				}
		}
	//valorile maxime, altfel da cu capu de zid
	if((sarpe[0].x<119) || (sarpe[0].x>515) || (sarpe[0].y<95) || (sarpe[0].y>380))
	{
		start = 0;
		dead();
	}
	if(start==0) return 1;
	//se deseneaza capul sarpelui si se sterge coada
	putimage(sarpe[0].x, sarpe[0].y, buf[0], 0);
	putimage(ultim.x, ultim.y, buf[1], 0);
	//daca a mancat
	if(sarpe[0].x == randx && sarpe[0].y == randy)
	{
		if(sunet) bip(500, 20);
		//scorul
		setcolor(MAGENTA);
		sprintf(scor_ch, "%f", scor);
		settextstyle(2, HORIZ_DIR, 7);
		outtextxy(getmaxx()/2-120, 44, scor_ch);  //se sterge scorul vechi
		scor+=(pow(11-(viteza_joc/20), 2))/4; // se recalculeaza scorul
		setcolor(WHITE);
		sprintf(scor_ch, "%f", scor);
		settextstyle(2, HORIZ_DIR, 7);
		outtextxy(getmaxx()/2-120, 44, scor_ch);  //se sterge scorul vechi

		//viteza se moddifica si se afiseaza
		if(viteza_joc>15)
		{
			setcolor(MAGENTA);
			sprintf(v, "%f", 11-(viteza_joc/20));
			settextstyle(2, HORIZ_DIR, 7);
			outtextxy(getmaxx()/2+88, 44, v);
			viteza_joc-=1;
			setcolor(WHITE);
			sprintf(v, "%f", 11-(viteza_joc/20));
			outtextxy(getmaxx()/2+88, 44, v);
		}
		limita++; //creste limita daca loveste o patratica
		randomeaza(); //se geneeraza alta patratica
	}
	setfillstyle(1, RED); //se sterge ultima patratica
	return 1;
}

void snake()
{
	char ch;
	delay(500);
	scor=0;
	int directie=8;
	while(start)
	{
		delay(viteza_joc);
		if(!kbhit())   mutare(directie);
		else
		{
			ch = getch();
			switch(ch)
			{
				case SUS: {
							directie = 8;
							mutare(8);
							break;
							}
				case JOS: {
							directie = 2;
							mutare(2);
							break;
							}
				case DR : {
							directie = 6;
							mutare(6);
							break;
							}
				case STG: {
							directie = 4;
							mutare(4);
							break;
							}
				case 'p': {
							if(sunet) bip (350, 100);
							mutare(0);
							directie=0;
							break;
							}
				case ESC: {
							if(sunet) bip(200, 50);
							start = 0;
							setbkcolor(BLACK);
							inceput(); break;
							}
				}
			}
		}
	}

void main()
{
	textcolor(RED);
	int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, "");
	int marime;

	//patratica 8X8 pixeli
	setfillstyle(1, BLUE);
	bar(1,1,8,8);
	marime = imagesize(1,1,8,8);
	buf[0] = malloc(marime);
	setcolor(YELLOW);
	rectangle(1,1,8,8);
	getimage(1,1,8,8,buf[0]); //s-a memorat patratul albastru

	setfillstyle(1, RED);
	bar(1,1,8,8);
	marime = imagesize(1,1,8,8);
	buf[1] = malloc(marime);
	getimage(1,1,8,8,buf[0]); //s-a memorat patratul rosu
	cleardevice();
	setfillstyle(1, LIGHTBLUE);
	bar(1,1,8,8);
	marime = imagesize(1,1,8,8);
	buf[2] = malloc(marime);
	getimage(1,1,8,8, buf[2]); //se mem patratyl mancare
	cleardevice();
	inceput();
}


































