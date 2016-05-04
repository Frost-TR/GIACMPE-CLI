#include <QtCore/QCoreApplication>
#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QChar>
#include <QThread>
#include <iostream>
#include <unistd.h>
#include "./Headers/gamedata.h"



using namespace std;

void Render();

GameData *GameDat= new GameData();
bool DisableGrid[12][12];
bool error;
QChar GridRe[100][100];
int size;

void clearConsole(){
    system("cls||clear");
}


void printHelp(){
    clearConsole();
    cout<<"Help:"<<endl;
    cout<<"     Priklad spusteni: hra2016-cli -n => spusti novou hru"<<endl;
    cout<<"     Priklad spusteni: hra2016-cli -l game.dat => Nacte hru se zadaneho souboru"<<endl;
    cout<<"     Priklad spusteni: hra2016-cli -h => vytiskne tuto napovedu"<<endl;
}

void prepareNewGame(){
    clearConsole();
    QTextStream s(stdin);
    QString *Qline = new QString();
    std::string line;

    cout<<"Nova Hra :"<<endl;
    cout<<"Zadejte velikost hraciho pole (6 pro 6x6,8 pro 8x8, 10 pro 10x10, 12 pro 12x12, defaultni hodnota je 8): ";
    std::getline(std::cin, line);
    *Qline=QString::fromStdString(line);
    int tmpnumber = Qline->toInt();
    switch(tmpnumber){
    case 6:
        GameDat->Game.GridSize=6;
        break;
    case 8:
        GameDat->Game.GridSize=8;
        break;
    case 10:
        GameDat->Game.GridSize=10;
        break;
    case 12:
        GameDat->Game.GridSize=12;
        break;
    default:
        GameDat->Game.GridSize=8;
        break;
    }

    cout<<"Zadejte jmeno prvniho hrace : ";
    std::getline(std::cin, line);
    Qline->clear();
    *Qline=QString::fromStdString(line);
    GameDat->Game.Player1Name = new QString(*Qline);

    cout<<"Prejete si hrat proti Umele inteligenci? A/N (defaultni hodnota je N) : ";
    std::getline(std::cin, line);
    Qline->clear();

    *Qline=QString::fromStdString(line);

    if(QString::compare(*Qline,"A")==0){
        GameDat->Game.OpponentIsHuman=false;
        line.clear();
        cout<<"Vybrali jste si pocitac jako protivnika..." << endl;
        cout<<"Zadejte jeho uroven (0 pro tezkou, 1 pro stredni, 2 pro lehkou, defaultni hornota je 1): ";
        std::getline(std::cin, line);
        QString Qline2;
        Qline2.append(QString::fromStdString(line));
        tmpnumber = Qline2.toInt();
        switch(tmpnumber){
        case 0:
            GameDat->Game.AIlevel=0;
            GameDat->Game.Player2Name = new QString("AI (Hard)");
            break;
        case 1:
            GameDat->Game.AIlevel=1;
            GameDat->Game.Player2Name = new QString("AI (Medium)");
            break;
        case 2:
            GameDat->Game.AIlevel=2;
            GameDat->Game.Player2Name = new QString("AI (Stupid)");
            break;
        default:
            GameDat->Game.AIlevel=1;
            GameDat->Game.Player2Name = new QString("AI (Medium)");
            break;
        }
    }else{
        GameDat->Game.OpponentIsHuman=true;
        cout<<"Vybrali jste si lidskeho protivnika..." << endl;
        cout<<"Zadejte jmeno druheho hrace: ";
        std::getline(std::cin, line);
        Qline->clear();
        *Qline=QString::fromStdString(line);
        GameDat->Game.Player2Name= new QString(*Qline);
    }

    GameDat->Game.Actual=0;
    GameDat->Game.Last=0;
    GameDat->Game.ActivePlayer=0;
    GameDat->Game.Player1Score=2;
    GameDat->Game.Player2Score=2;

    for(int i=0;i<GameDat->Game.GridSize;i++){
        for(int j=0;j<GameDat->Game.GridSize;j++){
            GameDat->Game.History[0].Grid[i][j]=0;
        }
    }
    int halfsize=GameDat->Game.GridSize/2;

    GameDat->Game.History[0].Grid[halfsize-1][halfsize-1]=1;
    GameDat->Game.History[0].Grid[halfsize][halfsize]=1;

    GameDat->Game.History[0].Grid[halfsize-1][halfsize]=2;
    GameDat->Game.History[0].Grid[halfsize][halfsize-1]=2;
    GameDat->Game.RemainingStones=(GameDat->Game.GridSize*GameDat->Game.GridSize)-4;
    return ;

}

void prepareLoadGame(QString *filename){
    error=false;
    QFile file(*filename);
    QTextStream in(&file);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QString line = in.readLine();
        if((QString::compare(line,"Hra2016-TTRK",Qt::CaseSensitive))!=0){
            cerr<<"Neznamy parametr..."<<endl;
            error=true;
            return ;
        }
        line = in.readLine();
        GameDat->Game.GridSize=line.toInt();
        line = in.readLine();
        GameDat->Game.Actual=line.toInt();
        line = in.readLine();
        GameDat->Game.Last=line.toInt();
        line = in.readLine();
        GameDat->Game.Player1Score=line.toInt();
        line = in.readLine();
        GameDat->Game.Player2Score=line.toInt();
        line = in.readLine();
        GameDat->Game.RemainingStones=line.toInt();
        line = in.readLine();
        GameDat->Game.ActivePlayer=line.toInt();
        line = in.readLine();
        GameDat->Game.AIlevel=line.toInt();
        line = in.readLine();
        if(line.toInt()==0){
           GameDat->Game.OpponentIsHuman=false;
        }else{
           GameDat->Game.OpponentIsHuman=true;
        }
        line = in.readLine();
        GameDat->Game.Player1Name= new QString(line);
        line = in.readLine();
        GameDat->Game.Player2Name= new QString(line);
        int position=0;
        for(int x=0;x<=GameDat->Game.Last;x++){
           line = in.readLine();
           for(int i=0;i<GameDat->Game.GridSize;i++){
               for(int j=0;j<GameDat->Game.GridSize;j++){
                   QChar key=line.at(position);
                   GameDat->Game.History[x].Grid[i][j]=key.toLatin1()-48;
                   position++;
               }
           }
           position=0;
        }
    }else{
        cerr<<"Neznamy parametr..."<<endl;
        error=true;
        return ;
    }
    file.close();

}

void Save(){
    QString Filename;
    QFile file(Filename);
         if (file.open(QIODevice::WriteOnly | QIODevice::Text))
             {
             QTextStream outToFile(&file);
             outToFile << "Hra2016-TTRK" << endl;
             outToFile << QString::number(GameDat->Game.GridSize) << endl;
             outToFile << QString::number(GameDat->Game.Actual) << endl;
             outToFile << QString::number(GameDat->Game.Last) << endl;
             outToFile << QString::number(GameDat->Game.Player1Score) << endl;
             outToFile << QString::number(GameDat->Game.Player2Score) << endl;
             outToFile << QString::number(GameDat->Game.RemainingStones) << endl;
             outToFile << QString::number(GameDat->Game.ActivePlayer) << endl;
             outToFile << QString::number(GameDat->Game.AIlevel) << endl;
             if(GameDat->Game.OpponentIsHuman){
                 outToFile << QString::number(1) << endl;
             }else{
                 outToFile << QString::number(0) << endl;
             }
             outToFile << *GameDat->Game.Player1Name << endl;
             outToFile << *GameDat->Game.Player2Name << endl;
             QString *outputGrid = new QString();
             outputGrid->resize(2*GameDat->Game.GridSize);
             outputGrid->clear();
             int position=0;
             for(int x=0;x<=GameDat->Game.Last;x++){
                 for(int i=0;i<GameDat->Game.GridSize;i++){
                     for(int j=0;j<GameDat->Game.GridSize;j++){
                     outputGrid->insert(position,QChar(GameDat->Game.History[x].Grid[i][j]+48));
                     position++;
                     }
                 }
                outToFile << *outputGrid << endl;
                position=0;
                outputGrid->clear();
             }
             file.close();
         }else{
         clearConsole();
         cout<<"Soubor se nepodarilo otevrit.."<<endl;
         QThread::sleep(2);
         Render();
         }
}

void Redo(){

}

void Undo(){

}

void Render(){
    clearConsole();

    cout << "Prikazy: undo (vrati hru o krok zpet), redo (posune hru o krok vpred), quit (ukonci hru), save (ulozi hru), add x y (provede tah na souradnicich x osa x a y na ose y)" <<endl;
    cout<<endl;
    cout << "------------------------------------------------------------------------------------------------------------------" << endl;
    int i=2;
    int j=2;
    int x=0;
    int y=0;

    while(i<size){
        while(j<size){
            if(GameDat->Game.History[GameDat->Game.Actual].Grid[x][y]==0){
                GridRe[i][j]='\0';
            }
            if(GameDat->Game.History[GameDat->Game.Actual].Grid[x][y]==1){
                GridRe[i][j]='o';
            }
            if(GameDat->Game.History[GameDat->Game.Actual].Grid[x][y]==2){
                GridRe[i][j]='x';
            }
            j++;
            j++;
            y++;
        }
        i++;
        i++;
        x++;
        j=2;
        y=0;
    }

    for(int i=0;i<size+1;i++){
        cout<<"    ";
        for(int j=0;j<size+1;j++){
            if(GridRe[i][j]==58){
                cout<< " 10";
            }else{
                if(GridRe[i][j]==59){
                    cout<< " 11";
                }else{
                    if(GridRe[i][j]==60){
                        cout<< " 12";
                    }else{
                        cout<< " "<< GridRe[i][j].toLatin1() << " ";
                    }
                }
            }
        }
        cout<<endl;
    }
    if(GameDat->Game.ActivePlayer==0){
        cout<< "     oooooooooooooooo - " << *GameDat->Game.Player1Name->toLatin1();
        cout << "Score: " << std::to_string(GameDat->Game.Player1Score);
        cout << " (Na tahu) "<< endl;
        cout<<endl;
        cout<< "     xxxxxxxxxxxxxxxx - " << *GameDat->Game.Player2Name->toLatin1();
        cout << "Score: " << std::to_string(GameDat->Game.Player2Score);
    }else{
        cout<< "     oooooooooooooooo - " << *GameDat->Game.Player1Name->toLatin1();
        cout << "Score: " << std::to_string(GameDat->Game.Player1Score);
        cout<<endl;
        cout<< "     xxxxxxxxxxxxxxxx - " << *GameDat->Game.Player2Name->toLatin1();
        cout << "Score: " << std::to_string(GameDat->Game.Player2Score);
        cout << " (Na tahu) "<< endl;
    }
    cout << endl;
    cout << "Prikaz : ";

}

void Init(){
    for(int i=0;i<100;i++){
        for(int j=0;j<100;j++){
            GridRe[i][j]='\0';
        }
    }
    int i=1;
    int offset=65;
    size=GameDat->Game.GridSize*2+2;
    while(i<size){
        GridRe[i][0]='-';
        GridRe[i][size]='-';
        i++;
        if(i<size){
        GridRe[i][0]=QChar(offset);
        GridRe[i][size]=QChar(offset);
        offset++;
        i++;
        }
    }
    i=1;
    offset=49;
    while(i<size){
        GridRe[0][i]='|';
        GridRe[size][i]='|';
        i++;
        if(i<size){
        GridRe[0][i]=QChar(offset);
        GridRe[size][i]=QChar(offset);
        offset++;
        i++;
        }
    }
    i=1;
    int j=1;
    while(i<size){
        while(j<size){
            GridRe[i][j]='+';
            j++;
            GridRe[i][j]='-';
            j++;
        }
        i++;
        i++;
        j=1;
    }
    i=2;
    j=1;
    while(i<size){
        while(j<size){
            GridRe[i][j]='|';
            j++;
            j++;
        }
        i++;
        i++;
        j=1;
    }
}

void DissableButtonGrid(){
    for(int i=0;i<GameDat->Game.GridSize;i++){
        for(int j=0;j<GameDat->Game.GridSize;j++){
            if(GameDat->Game.History[GameDat->Game.Actual].Grid[i][j]!=0){
                DisableGrid[i][j]=true;
            }else{
                DisableGrid[i][j]=false;;
            }
        }
    }
}

void SwitchActivePlayer(){
    if(GameDat->Game.ActivePlayer==0){
        GameDat->Game.ActivePlayer=1;
    }else{
        GameDat->Game.ActivePlayer=0;
    }
}

int game(){
    DissableButtonGrid();
    Init();
    Render();

}

int main(int argc, char *argv[])
{
    if(!((argc>1) && (argc<4))){
        clearConsole();
        printHelp();
        return 1;
    }

    int option;
    QString *filename;
    while ((option = getopt(argc, argv, "hnl:")) != -1) {
           switch (option) {
               case 'h':
                   printHelp();
                   break;
               case 'n':
                   prepareNewGame();
                   if(error){
                    return 1;
                   }
                   break;
               case 'l':
                   filename=new QString(optarg);
                   prepareLoadGame(filename);
                   if(error){
                    return 1;
                   }
                   break;
               default:
                   cerr<<"Neznamy parametr..."<<endl;
                   printHelp();
                   return 1;
           }
       }
    if(game()!=0){
        return 1;
    }
    return 0;
}
