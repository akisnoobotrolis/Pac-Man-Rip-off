#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <exception>
#include <MMSystem.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <algorithm>
#define BRICK 219
using namespace std;


class highscore{
	SHORT points;
	SHORT totalpoints;
	char name[10];
	public:
	
		~highscore();
		void settpoints(SHORT x){totalpoints=x;};
		highscore();
		void setpoints(){points=0;}
		SHORT getpoints()const {return points;};
		SHORT gettpoints()const {return totalpoints;};
	void givepoints(float y){points+=y;totalpoints+=y;}
	void resettpoints(){totalpoints=0;};
	void setname(string s){strcpy(name,s.c_str());};
	char* getname() {return name;};
	SHORT getlen() const{return sizeof(name);};	
};
highscore::highscore():points(0),totalpoints(0){
	for(SHORT i=0;i<10;i++)
	name[i]=' ';}

highscore::~highscore(){
};
bool operator<(const highscore &a,const highscore & b)
{
    return a.gettpoints() < b.gettpoints();
}

class moving
{
	protected:
	HANDLE hStdout;
	char a;
	SHORT x;
	SHORT y;
	public:
	
	char getc(){ return a;};
	SHORT getx(){ return x;};
	SHORT gety(){ return y;};
	void sety(SHORT a){y=a;};
	void setx(SHORT b){x=b;};
	moving(){ hStdout = GetStdHandle(STD_OUTPUT_HANDLE) ;hidecursor();}
	void hidecursor();
	moving(SHORT a, SHORT b,char c):x(a), y(b),a(c){hStdout = GetStdHandle(STD_OUTPUT_HANDLE) ;hidecursor();}
	void xy();
	virtual ~moving();
};



void moving::hidecursor(){
	CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(hStdout, &info);
}
	void moving::xy()
{
   
    COORD position = { x, y } ;
	
    SetConsoleCursorPosition( hStdout, position ) ;
}




    

moving::~moving(){}

class gnome : public moving {
	vector<vector<SHORT> > binmap;
	
public:

	gnome();
	gnome(SHORT x, SHORT y,SHORT a, SHORT b,char c);
	void findpath(vector< vector<unsigned char > >,SHORT,SHORT,SHORT, SHORT,SHORT,SHORT);
	void showvisited();
	virtual ~gnome();

};



void gnome::showvisited(){
	for(SHORT i=0;i<binmap.size();i++){
		for(SHORT j=0;j<binmap[i].size();j++){
			cout<<binmap[i][j];
		}
		cout<<endl;
	}
}

gnome::gnome():moving(){}
gnome::gnome(SHORT x, SHORT y,SHORT a,SHORT b,char c):moving(x,y,c){
	 for (SHORT i = 0; i < a; i++) {
       vector<SHORT>temp;
        for (SHORT j = 0; j < b; j++) {
            temp.push_back(i);
		 }
		 binmap.push_back(temp);
    }
}
gnome::~gnome(){}

	



void gnome::findpath(vector< vector<unsigned char > > map,SHORT r,SHORT c,SHORT k,SHORT l,SHORT py, SHORT px){
	for(SHORT i=0;i<map.size();i++){
	
		for(SHORT j=0;j<map[i].size();j++){
		if(r==i && c==j)
			binmap[i][j]=-1;
		else
			if(map[i][j]==219)
				binmap[i][j]=-2;
			else
				binmap[i][j]=-1;
		}
		}
		SHORT prevn=0;
		SHORT n=1;
		binmap[k][l]=-2;
		binmap[y][x]=0;
	while(binmap[r][c]==-1){
		for(SHORT i=1;i<map.size()-1;i++){
			for(SHORT j=1;j<map[i].size()-1;j++){
				if(binmap[i-1][j]==prevn && binmap[i][j]!=-2 && binmap[i][j]==-1)
					binmap[i][j]=n;
				else if(binmap[i+1][j]==prevn && binmap[i][j]!=-2 && binmap[i][j]==-1)
					binmap[i][j]=n;
				else if (binmap[i][j-1]==prevn && binmap[i][j]!=-2 && binmap[i][j]==-1)
					binmap[i][j]=n;
				else if(binmap[i][j+1]==prevn && binmap[i][j]!=-2 && binmap[i][j]==-1)
					binmap[i][j]=n;
			}
		}
		prevn=n;
		n++;
	
}
n--;

	for(SHORT i=1;i<map.size()-1;i++){
			for(SHORT j=1;j<map[i].size()-1;j++){
		
				if(binmap[i][j]==n && (i!=r || j!=c ) )
	 			binmap[i][j]=-1;
		
			
		}
	}
	SHORT fn=n;
	k=1;
	n--;
	while(k<=fn){
		for(SHORT i=1;i<map.size()-1;i++){
			for(SHORT j=1;j<map[i].size()-1;j++){
				SHORT t=0;
				if	(binmap[i][j]==n){
					if(binmap[i-1][j]>binmap[i][j])
						t=1;
						
					else if(binmap[i+1][j]>binmap[i][j])
						t=1;
					else if(binmap[i][j-1]>binmap[i][j])
						t=1;
					else if(binmap[i][j+1]>binmap[i][j])
						t=1;
				if(t==0)
				binmap[i][j]=-1;
			}
			}
		}	
	k++;
	n--;
	}
	SHORT t=0;
	
	
	if(binmap[y][x+1]==1){
	xy();
		if(map[y][x]==' ')
	cout<<' ';
	else if (map[y][x]==04){
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
	cout <<(char)04;}
	else if(y==py && x==px){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);	
	cout<<"x";
	}
		x++;
		t=1;
	}

	
	else if(binmap[y][x-1]==1){
	xy();
	if(map[y][x]==' ')
	cout<<' ';
	else if (map[y][x]==04){
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
	cout <<(char)04;}
	else if(y==py && x==px){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);	
	cout<<"x";
	}
		x--;
		t=1;
	}
	else if(binmap[y-1][x]==1){
	xy();
   	if(map[y][x]==' ')
	cout<<' ';
	else if (map[y][x]==04){
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
	cout <<(char)04;}
	else if(y==py && x==px){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);	
	cout<<"x";
	}
	y--;
	t=1;
	}
	else if(binmap[y+1][x]==1){
	xy();
		if(map[y][x]==' ')
	cout<<' ';
	else if (map[y][x]==04){
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
	cout <<(char)04;}
	else if(y==py && x==px){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);	
	cout<<"x";
	}
		y++;
		t=1;
	}
			
	

}



class traal : public moving {
	
	vector<vector<SHORT> > binmap;
public:
	
	
	traal();
	traal(SHORT x, SHORT y,SHORT, SHORT,char);
	void findpath(vector< vector<unsigned char > > ,SHORT ,SHORT, gnome,SHORT, SHORT );
	
	virtual ~traal();

};

traal::traal():moving(){}
traal::traal(SHORT x, SHORT y,SHORT a, SHORT b,char c):moving(x,y,c){
 for (SHORT i = 0; i < a; i++) {
       vector<SHORT>temp;
        for (SHORT j = 0; j < b; j++) {
            temp.push_back(i);
		 }
		 binmap.push_back(temp);
    }}
traal::~traal(){}

void traal::findpath(vector< vector<unsigned char > > map,SHORT r,SHORT c, gnome baba,SHORT py, SHORT px){
	COORD position;
	for(SHORT i=0;i<map.size();i++){
		for(SHORT j=0;j<map[i].size();j++){
		if(r==i && c==j)
			binmap[i][j]=-1;
		else if(baba.gety()==i && baba.getx()==j)
		binmap[baba.gety()][baba.getx()]=-2;
		else
			if(map[i][j]==BRICK)
				binmap[i][j]=-2;
			else 
				binmap[i][j]=-1;
		}
		}
		SHORT prevn=0;
		SHORT n=1;
		binmap[y][x]=0;
	while(binmap[r][c]==-1){
		for(SHORT i=1;i<map.size()-1;i++){
			for(SHORT j=1;j<map[i].size()-1;j++){
				if(binmap[i-1][j]==prevn  && binmap[i][j]==-1)
					binmap[i][j]=n;
				else if(binmap[i+1][j]==prevn && binmap[i][j]==-1)
					binmap[i][j]=n;
				else if (binmap[i][j-1]==prevn && binmap[i][j]==-1)
					binmap[i][j]=n;
				else if(binmap[i][j+1]==prevn  && binmap[i][j]==-1)
					binmap[i][j]=n;
			}
		}
		prevn=n;
		n++;
	
}
n--;

	for(SHORT i=1;i<map.size()-1;i++){
			for(SHORT j=1;j<map[i].size()-1;j++){
		
				if(binmap[i][j]==n && (i!=r || j!=c ) )
	 			binmap[i][j]=-1;
		
			
		}
	}
	SHORT fn=n;
	SHORT k=1;
	n--;
	while(k<=fn){
		for(SHORT i=1;i<map.size()-1;i++){
			for(SHORT j=1;j<map[i].size()-1;j++){
				SHORT t=0;
				if	(binmap[i][j]==n){
					if(binmap[i-1][j]>binmap[i][j])
						t=1;
						
					else if(binmap[i+1][j]>binmap[i][j])
						t=1;
					else if(binmap[i][j-1]>binmap[i][j])
						t=1;
					else if(binmap[i][j+1]>binmap[i][j])
						t=1;
				if(t==0)
				binmap[i][j]=-1;
			}
			}
		}	
	k++;
	n--;
	}

	

	if(binmap[y+1][x]==1){
	xy();
		if(map[y][x]==' ')
	cout<<' ';
	else if (map[y][x]==04){
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
	cout <<(char)04;}
	else if(y==py && x==px){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);	
	cout<<"x";
	}
		y++;
	
	}

	else if(binmap[y][x+1]==1){
	position = { x, y } ;
   	SetConsoleCursorPosition( hStdout, position ) ;
		if(map[y][x]==' ')
	cout<<' ';
	else if (map[y][x]==04){
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
	cout <<(char)04;}
	else if(y==py && x==px){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);	
	cout<<"x";
	}
		x++;
		
	}

	
	else if(binmap[y][x-1]==1){
	xy();
	if(map[y][x]==' ')
	cout<<' ';
	else if (map[y][x]==04){
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
	cout <<(char)04;}
	else if(y==py && x==px){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);	
	cout<<"x";
	}
		x--;

	}
	else if(binmap[y-1][x]==1){
	xy();
   	if(map[y][x]==' ')
	cout<<' ';
	else if (map[y][x]==04){
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
	cout <<(char)04;}
	else if(y==py && x==px){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);	
	cout<<"x";
	}
	y--;

	}
				
	

}




class hero: public moving {
		vector<vector<SHORT> > binmap;
		bool alive;
	
	public:
		bool getstatus(){return alive;};
		hero();
		hero(SHORT , SHORT , SHORT, SHORT,char);
		void input(vector< vector<unsigned char > >);
		void sethealth();
		void revive(){ alive=true;};
		void findpath(vector< vector<unsigned char > > , gnome, traal,SHORT ,SHORT );
		virtual ~hero();
	
		void showbin();
};


void hero::findpath(vector< vector<unsigned char > > map, gnome baba,  traal yaga,SHORT py,SHORT px){
	for(SHORT i=0;i<binmap.size();i++){
		for(SHORT j=0;j<binmap[0].size();j++){
			if(map[i][j]==BRICK)
				binmap[i][j]=-2;
			else 
				binmap[i][j]=-1;
		}
	}
		binmap[y][x]=0;
		binmap[baba.gety()][baba.getx()]=-2;
		binmap[yaga.gety()][yaga.getx()]=-2;
		SHORT ti,tj;
	
	SHORT prevn=0;
		SHORT n=1;
		
		SHORT t=1;
		while(t){
			SHORT i=1;
				while(i<binmap.size()-1 && t){
					SHORT j=1;
					while(j<binmap[0].size()-1 && t){
					if(binmap[i-1][j]==prevn){
					
						if(binmap[i][j]==-1){
							if(map[i][j]==04|| (i==py && j==px)){
								t=0;
								ti=i;
								tj=j;
							}
							binmap[i][j]=n;
						}
					}
					else if(binmap[i+1][j]==prevn){
					
					 if(binmap[i][j]==-1){
							if(map[i][j]==04|| (i==py && j==px)){
								t=0;
								ti=i;
								tj=j;
							}
							binmap[i][j]=n;
						}
					}
					else if(binmap[i][j-1]==prevn){
					
						if(binmap[i][j]==-1){
							if(map[i][j]==04|| (i==py && j==px)){
								t=0;
								ti=i;
								tj=j;
							}
							binmap[i][j]=n;
						}
					}
					else if(binmap[i][j+1]==prevn){
					
						if(binmap[i][j]==-1){
							if(map[i][j]==04 || (i==py && j==px)){
								t=0;
								ti=i;
								tj=j;
							}
							binmap[i][j]=n;
						}
					}
					j++;
					}
			i++;
		}
		prevn=n;
		n++;	
}
n--;
	for(SHORT i=0;i<binmap.size();i++){
			for(SHORT j=0;j<binmap[i].size();j++){
		
			if(binmap[i][j]==n && (i!=ti || j!=tj ) )
	 			binmap[i][j]=-1;
		
			
		}
	}
	SHORT fn=n;
	SHORT k=1;
	n--;
	while(k<=fn){
		for(SHORT i=1;i<map.size()-1;i++){
			for(SHORT j=1;j<map[i].size()-1;j++){
				SHORT t=0;
				if	(binmap[i][j]==n){
					if(binmap[i-1][j]>binmap[i][j])
						t=1;
						
					else if(binmap[i+1][j]>binmap[i][j])
						t=1;
					else if(binmap[i][j-1]>binmap[i][j])
						t=1;
					else if(binmap[i][j+1]>binmap[i][j])
						t=1;
				if(t==0)
				binmap[i][j]=-1;
			}
			}
		}	
	k++;
	n--;
	}

	
	if(binmap[y-1][x]==1){
	xy();
	cout<<' ';
	y--;

	}
	else if(binmap[y+1][x]==1){
	xy();
	cout<<' ';
	y++;

	}

	else if(binmap[y][x+1]==1){
	xy();
	
	cout<<' ';
		x++;
	
	}

	
	else if(binmap[y][x-1]==1){
	xy();
	cout<<' ';
	x--;
	}
				
	

}

void hero::sethealth(){alive=false;}
void hero::input(vector< vector<unsigned char > >map){
		if ( GetAsyncKeyState( VK_UP ) ){
			if( map[y-1][x] == ' ' || map[y-1][x] == 04 ){
			xy();
			cout<<' ';
			 y--;
			 }
		}
		if ( GetAsyncKeyState( VK_DOWN ) ){

			if( map[y+1][x] == ' ' || map[y+1][x] == 04)
			{
				xy();
					cout<<' ';
					y++;
			}
		}
		if ( GetAsyncKeyState( VK_LEFT ) ){

			if( map[y][x-1] == ' ' || map[y][x-1] == 04 ){
				xy();
			cout<<' ';
			x--;}
		}
		if ( GetAsyncKeyState( VK_RIGHT ) ){
			if( map[y][x+1] == ' ' || map[y][x+1] == 04 ){
				xy();
    			
				cout<<' ';
			x++;}
		}
}


hero::hero():alive(true),moving(){
}
hero::hero(SHORT x, SHORT y,SHORT b,SHORT c,char d):alive(true),moving(x,y,d){ 
for (SHORT i = 0; i < b; i++) {
       vector<SHORT>temp;
        for (SHORT j = 0; j < c; j++) {
            temp.push_back(i);
		 }
		 binmap.push_back(temp);
    }}

hero::~hero(){}


class engine
{
	highscore h;
	hero potter;
	gnome baba;
	traal yaga;
	vector<vector<unsigned char> > map; 
	bool stillplay;
	SHORT py;
	SHORT px;
	SHORT nod;
	SHORT checkpaper;
	highscore sc[5];
	
	
	
	

public:
	SHORT getesc();
	
	engine(const char *,const char *);
	virtual ~engine();
	void puthero();
	void showmap();
	bool getherostatus(){return potter.getstatus();};
	void getheroinput(){return potter.input(map);};
	void putheroai();
	void putgnome();
	void checkdiamonds(float);
	void checkhealth();
	void puttraal();
	void revive();
	void  showscore();
	void checkfpaper();
	SHORT getcheckpaper(){return checkpaper;};
	void resetnod(){nod=10;
	};
	void setgnome();
	void settraal();
	void setnod(){nod++;};
	void setdiamonds();
	void setpotter();
	void setpy(){py=-999;};
	void setpx(){px=-999;};
	SHORT getc(){return map[0].size();};
	SHORT getr(){return map.size();};
	void setcheckpaper(){checkpaper=0;};
	SHORT getmy(){return map.size();};
	SHORT getmx(){return map[0].size();	};
	void settpoints();
	void read(const char *); 
	void exprt(const char *); 
	void play(const char*);
};

void engine::play(const char* filename){
		HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); 
    if(getmx()*10<1000)
    	MoveWindow(console, r.left, r.top,1000 ,getmy()*19 , TRUE);
    else
    	MoveWindow(console, r.left, r.top,getmx()*10 ,getmy()*19 , TRUE);
    CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

Sleep(1000);  
//PlaySound("hp.wav",NULL,SND_FILENAME|SND_ASYNC); 
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8);
cout<<endl;   cout<<endl; 
        
                                                                                                                                                                                     
cout<<"888888b.         d8888 888888b.  8888888 .d8888b."<<endl;                                                    
cout<<"888  888b       d88888 888  888b   888  d88P  Y88b"<<endl;                                                
cout<<"888  .88P      d88P888 888  .88P   888  Y88b. "<<endl;                                              
cout<<"8888888K.     d88P 888 8888888K.   888   Y8888b." << endl;                                                 
cout<<"888  8Y88b   d88P  888 888  Y888b  888      Y888b. "<< endl;                                               
cout<<"888    888  d88P   888 888    888  888        8888"<<endl;                                            
cout<<"888   d88P d8888888888 888   d88P  888  Y88b  d88P   "<< endl;                                              
cout<<"88888888P d88P     888 88888888P 8888888 Y888888P    "<<endl;                                                                                                                                                 
 cout<<                                                                endl;                                     
cout<<"8888888b.   .d88888b. 88888888888 88888888888 8888888888 8888888b.  8888888 8888888b. 8888888 .d8888b.   "<<endl; 
cout<<" 888   Y88b d88P   Y88b    888         888     888        888   Y88b   888   888   Y88b  888  d88P  Y88b  "<<endl; 
cout<<" 888    888 888     888    888         888     888        888    888   888   888    888  888  Y88b.       "<<endl; 
cout<<" 888   d88P 888     888    888         888     8888888    888   d88P   888   888    888  888    Y8888b.    "<<endl; 
cout<<" 888        888     888    888         888     888        888 T88b     888   888    888  888        8888  "<<endl; 
cout<<" 888        Y88b. .d88P    888         888     888        888  T88b    888   888  .d88P  888  Y88b  d88P  "<<endl; 
cout<<" 888         Y888888P      888         888     8888888888 888   T88b 8888888 8888888PP 8888888  Y88888P   "<<endl; 
	
	Sleep(4000); 
	

	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	cout<<"You are Babis Potteridis (";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
	cout<<"H";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	cout<<"). Your purpose is to find all the diamonds ";
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
	cout<<(CHAR)04;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	cout <<" without getting eaten from the monsters (";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	cout<<"G";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	cout<<",";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	cout<<"T";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	cout<<")"<<endl;
	cout<<"Do you want to see a demo? Press y/Y for yes or n/N for no" <<endl;
	char demo;
	cin >> demo;
	SHORT s;
	float multiplier;
	system("cls");
	if(demo=='N' || demo=='n'){
	cout<<"Use the arrow keys to move"<<endl;
	cout<<"CHOOSE DIFFICULTY"<<endl<<"Press E for easy,M for medium,H for hard"<<endl;
	char difficulty;
	cin >> difficulty;
	if (difficulty=='E' || difficulty=='e'){
	multiplier=0.5;
	s=150;
}
	else if (difficulty=='M'|| difficulty=='m'){
	multiplier=0.75;
	s=100;
	}
	else if (difficulty=='H'|| difficulty=='h'){
	multiplier=1;
	s=50;}}
	else if(demo=='y' || demo=='Y'){
		multiplier=1;
		s=50;
	}
	system("cls");
	
	showmap();
 SHORT	level=1;
	while(getherostatus() && getesc()){
		showscore();
	
			if(demo=='N' || demo=='n'){
				
		getheroinput();
		puthero();
		}
		else if(demo=='y' || demo=='Y')
		putheroai();
		puttraal();
		putgnome();
		checkhealth();
		checkdiamonds(multiplier);
		checkfpaper();
		if	(getcheckpaper()){
			
			setpy();
			setpx();
			level++;
			system("cls");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
			cout<<"CONGRATULATIONS!!!"<<endl;
			Sleep(1000);
			cout<<"LEVEL "<<level;
			Sleep(1000);
			system("cls");
			setnod();
			setdiamonds();
			setpotter();
			setgnome();
			settraal();
			setcheckpaper();
			showmap();
		
		}
			
		Sleep(s);
		if(!getherostatus()){
		//	PlaySound("bruh.wav",NULL,SND_FILENAME|SND_ASYNC); 
		
			system("cls");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
			if(demo=='N' || demo=='n'){
				string nm;
			do{
		cout<<"Enter your name :";
			cin>>nm;
			cout<< endl;
		} while(nm.length()>10);
			h.setname(nm);
			exprt(filename);
			cout<<endl<<"Wanna try again? Press y/Y for yes or n/N for no"<<endl;
			char answer;
		cin >> answer;
		if (answer=='Y' || answer=='y'){
		
		system("cls");
		cout<<"CHOOSE DIFFICULTY"<<endl<<"Press E for easy,M for medium,H for hard"<<endl;
		char difficulty;
		cin >> difficulty;
		if (difficulty=='E' || difficulty=='e'){
		multiplier=0.5;
		s=150;
		}
		else if (difficulty=='M'|| difficulty=='m'){
		multiplier=0.7;
		s=100;
		}
		else if (difficulty=='H'|| difficulty=='h'){
		multiplier=1;
		s=50;}
		system("cls");
	
			resetnod();
			settpoints();
			revive();
			setpy();
			setpx();
		
			setdiamonds();
			setpotter();
			setgnome();
			settraal();
			setcheckpaper();
			showmap();
		}
		
		}
		else{
	cout<<"Use the arrow keys to move"<<endl;
	cout<<"CHOOSE DIFFICULTY"<<endl<<"Press E for easy,M for medium,H for hard"<<endl;
	char difficulty;
	cin >> difficulty;
	if (difficulty=='E' || difficulty=='e'){
	multiplier=0.5;
	s=150;
}
	else if (difficulty=='M'|| difficulty=='m'){
	multiplier=0.7;
	s=100;
	}
	else if (difficulty=='H'|| difficulty=='h'){
	multiplier=1;
	s=50;}

	demo='n';
	system("cls");
	settpoints();
		revive();
			setpy();
			setpx();
			setdiamonds();
			setpotter();
			setgnome();
			settraal();
			setcheckpaper();
			showmap();
			}
		}
		Sleep(s);
}
}




void engine::read( const char* filename){
	FILE *scores=fopen(filename, "rb");
	if(!scores){
		for(SHORT i=0;i<5;i++){
			sc[i].settpoints(0);
			sc[i].setname("PLAYER");
	}
	}
	else{
		fread(sc,sizeof(highscore),5,scores);
	}
	fclose(scores);
}
	

void engine::exprt(const char * filename){	
{ 
	SHORT minscore=sc[0].gettpoints();
	SHORT index=0;
	for(SHORT i=1;i<5;i++){
		if(sc[i].getpoints()<minscore){
			minscore=sc[i].gettpoints();
			index=i;
		}
	}
	if(minscore==0 || minscore<h.gettpoints()){
		sc[index]=h;
	}
	sort(sc, sc + 5);
	FILE *scores=fopen(filename, "wb");
	fwrite(sc,sizeof(highscore),5,scores);
	fclose(scores);
}
}

SHORT engine::getesc(){
	if (GetAsyncKeyState( VK_ESCAPE ))
				return 0;
	else return 1;
	
}

void engine::settpoints(){
	h.setpoints();
	h.resettpoints();
}

void engine::settraal(){

	SHORT tempi,tempj;
		do{
		tempi=rand()%map.size();
		tempj=rand()%map[0].size();
		}while(map[tempi][tempj]!=' ' || tempi==potter.gety() || tempj== potter.getx() || tempi==baba.gety() || tempj== baba.getx());
		yaga.sety(tempi);
		yaga.setx(tempj);
}


void engine::setgnome(){

	SHORT tempi,tempj;
		do{
		tempi=rand()%map.size();
		tempj=rand()%map[0].size();
		}while(map[tempi][tempj]!=' ' || tempi==potter.gety() || tempj== potter.getx());
		baba.sety(tempi);
		baba.setx(tempj);
}
	
void engine::setpotter(){
	SHORT tempi,tempj;
		do{
		tempi=rand()%map.size();
		tempj=rand()%map[0].size();
		}while(map[tempi][tempj]!=' ');
	potter.sety(tempi);
	potter.setx(tempj);
}	
	
	
void engine::setdiamonds(){
	for(SHORT i=0;i<map.size();i++){
			for(SHORT j=0;j<map[0].size();j++){
				if (map[i][j]==04)
					map[i][j]=' ';
	}
}


	SHORT tempi,tempj;
		for(SHORT i=0;i<nod;i++){
		do{
		tempi=rand()%map.size();
		tempj=rand()%map[1].size();
		}
		while(map[tempi][tempj]!=' ');
		map[tempi][tempj]=04;
		}
	
}


void engine::checkfpaper(){
	if(py==potter.gety() && px==potter.getx()){
	//	PlaySound("vctr.wav",NULL,SND_FILENAME|SND_ASYNC);
		h.givepoints(100);
		map[potter.gety()][potter.getx()]=' ';
		h.setpoints();
		checkpaper= 1;}
	}


void engine::showscore(){
	COORD pos;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
 	for(SHORT i=4,x=1;i>=0;i--,x++){
 	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),i+1);
 	pos = { (SHORT)(map[0].size()+4),(SHORT)(i-i+x)} ;
	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), pos ) ;
 		for(SHORT j=0;j<sc[i].getlen();j++){
 			char* n=sc[i].getname();
 			cout<<n[j];
		 }
	pos = { (SHORT)(map[0].size()+15),(SHORT)(i-i+x)} ;
		SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), pos ) ;
		 cout<<": "<<sc[i].gettpoints()<<endl;
	 }
	pos = { (SHORT)(map[0].size()+4),7} ;
	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), pos ) ;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12
	);
 	cout<<"YOUR SCORE IS:"<<h.gettpoints();
 
}
void engine::revive(){ potter.revive();}

void engine::checkdiamonds(float mltplr){
	COORD position;
		if (map[potter.gety()][potter.getx()]==04){
		//	PlaySound("dmnd.wav",NULL,SND_FILENAME|SND_ASYNC); 
			h.givepoints(10*mltplr);
			map[potter.gety()][potter.getx()]=' ';
		if(h.getpoints()==10*nod*mltplr){
			
			SHORT i;
			SHORT j;
			do{
			i=rand()%map.size();
			j=rand()%map[0].size();
			}while(map[i][j]!=' ' || i==potter.gety() || j==potter.getx() || i==baba.gety() || j==baba.getx() || i==yaga.gety() || i==yaga.getx());
			py=i;
			px=j;
			 position = { j, i } ;
 			   SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), position ) ;
 			   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
 			   cout<<"x";
		}
		}	
	}
	


void engine::checkhealth(){

		if (baba.gety()==potter.gety() && baba.getx()==potter.getx())
			potter.sethealth();
	

		else if (yaga.gety()==potter.gety() && yaga.getx()==potter.getx())
			potter.sethealth();

	
	
}

void engine::putheroai(){ 
	
 	potter.findpath(map,baba,yaga,py,px);
	potter.xy();
  	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
	cout << potter.getc();
}


void engine::puthero(){ 
   potter.xy(); 
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
   cout << potter.getc();
   
}
void engine::putgnome(){ 
	

	
  	baba.findpath(map,potter.gety(),potter.getx(),yaga.gety(),yaga.getx(),py,px);
  	baba.xy();
  

   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
   
  cout << baba.getc();

}
void engine::puttraal(){ 
	

	
  	yaga.findpath(map,potter.gety(),potter.getx(),baba,py,px);
  	yaga.xy();
  

   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
   
  cout << yaga.getc();

}

	engine::engine(const char *file_name,const char *file_name2){
		read(file_name2);
		checkpaper=0;
		py=-1;
		px=-1;
		nod=10;
		ifstream map_file(file_name);
		stillplay=true;
		srand(time(NULL));
		
		
		string line;

		try{
			if(!map_file.is_open()){
				throw 0;
			}
		}
		catch(SHORT x){
			cout<<"could not load file"<<endl;
		}
	   
	    
		while(getline(map_file,line)){
			vector<unsigned char> temp;
			for(SHORT i=0;i<line.length();i++)
				temp.push_back(line[i]);
			map.push_back(temp);
		}
		for(SHORT i=0;i<map.size();i++){
		for(SHORT j=0;j<map[i].size();j++){
			if (map[i][j]=='*')  
				map[i][j]=BRICK;
			}
		}
		SHORT tempih,tempjh,tempi,tempj,tempig,tempjg,tempit,tempjt;
		do{
		tempih=rand()%map.size();
		tempjh=rand()%map[0].size();
		}while(map[tempih][tempjh]!=' ');
		
		hero a(tempjh,tempih,map.size(),map[0].size(),'H');
		potter=a;

	
	
		do{
		tempig=rand()%map.size();
		tempjg=rand()%map[0].size();
		}
		while(map[tempig][tempjg]!=' ' || tempih==tempig || tempjg==tempjh);
		gnome c(tempjg,tempig,map.size(),map[0].size(),'G');
		baba=c;
		do{
		tempit=rand()%map.size();
		tempjt=rand()%map[1].size();
		}
		while(map[tempit][tempjt]!=' ' ||tempih==tempit || tempjh==tempjt || tempig==tempit || tempjg==tempjt);
		traal d(tempjt,tempit,map.size(),map[0].size(),'T');
		yaga=d;
		for(SHORT i=0;i<10;i++){
		do{
		tempi=rand()%map.size();
		tempj=rand()%map[1].size();
		}
		while(map[tempi][tempj]!=' ');
		map[tempi][tempj]=04;
		}
	}

	




void engine::showmap() {
	

	HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
	for(SHORT i=0;i<map.size();i++){
		for(SHORT j=0;j<map[i].size();j++){
			if (map[i][j]==BRICK){
                SetConsoleTextAttribute(h,5);
			}
			else if(map[i][j]=='T'){
                SetConsoleTextAttribute(h,7);
            }
			else if(map[i][j]==04){
                SetConsoleTextAttribute(h,3);
			}
            cout<<map[i][j];			
		}
		cout<<endl;
	}
}

engine::~engine(){

}

int main(int argc, char const *argv[])
{
	system("cls");
	engine myengine(argv[1],argv[2]);
	myengine.play(argv[2]);

	system("cls");
	cout<<"See you next time :)";
	Sleep(1000);

	return 0;
}
