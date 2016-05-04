/**
 * @file   gamelogic.cpp
 * @author Rys Tomáš, Tadeáš Kovář
 */

#include "./Headers/gamelogic.h"

/**
 * @brief GameLogic::GameLogic Konstruktor třídy. Nebyl využít.
 */
GameLogic::GameLogic()
{
}

/**
 * @brief GameLogic::Move Tato metoda slouží pro provedení tahu.
 * @param GameDat Herní data.
 * @param i Souřadnice osy x, na které ma být proveden tah.
 * @param j Souřadnice osy y, na které ma být proveden tah.
 * @return Vraci herni data.
 */
GameData * GameLogic::Move(GameData *GameDat, int i, int j){
    GameDat->Game.History[GameDat->Game.Actual+1]= GameDat->Game.History[GameDat->Game.Actual];

    GameDat->Game.Actual++;
    GameDat->Game.Last=GameDat->Game.Actual;

    int find=0;
    int end=0;

    if(GameDat->Game.ActivePlayer==0){
        GameDat->Game.History[GameDat->Game.Actual].whoMove=0;
        GameDat->Game.History[GameDat->Game.Actual].Grid[i][j]=1;
        find=2;
        end=1;
    }else{
        GameDat->Game.History[GameDat->Game.Actual].Grid[i][j]=2;
        GameDat->Game.History[GameDat->Game.Actual].whoMove=1;
        find=1;
        end=2;
    }

    int size=GameDat->Game.GridSize;
    int tmpi=i;
    int tmpj=j;
    int Grid[12][12];

    for(int x=0;x<GameDat->Game.GridSize;x++){
        for(int y=0;y<GameDat->Game.GridSize;y++){
            Grid[x][y]=GameDat->Game.History[GameDat->Game.Actual].Grid[x][y];
        }
    }

  //prepis vlevo
    if(i>1){
        if(Grid[i-1][j]==find){
            Grid[i-1][j]=end;
            tmpi=i-2;
            while(tmpi>=0){
                if(Grid[tmpi][j]==end){
                    for(int x=0;x<GameDat->Game.GridSize;x++){
                        for(int y=0;y<GameDat->Game.GridSize;y++){
                            GameDat->Game.History[GameDat->Game.Actual].Grid[x][y]=Grid[x][y];
                        }
                     }
                }else{
                    if(Grid[tmpi][j]==0){
                        break;
                    }else{
                    Grid[tmpi][j]=end;
                    }
                }
                tmpi--;
            }
        }
    }
  //prepis vpravo
    for(int x=0;x<GameDat->Game.GridSize;x++){
        for(int y=0;y<GameDat->Game.GridSize;y++){
            Grid[x][y]=GameDat->Game.History[GameDat->Game.Actual].Grid[x][y];
        }
    }
    if(i<size-2){
        if(Grid[i+1][j]==find){
            Grid[i+1][j]=end;
            tmpi=i+2;
            while(tmpi<size){
                if(Grid[tmpi][j]==end){
                    for(int x=0;x<GameDat->Game.GridSize;x++){
                        for(int y=0;y<GameDat->Game.GridSize;y++){
                            GameDat->Game.History[GameDat->Game.Actual].Grid[x][y]=Grid[x][y];
                        }
                    }
                }else{
                    if(Grid[tmpi][j]==0){
                        break;
                    }else{
                        Grid[tmpi][j]=end;
                        }
                }
                tmpi++;
            }
        }
    }

  //prepis nahoru
    for(int x=0;x<GameDat->Game.GridSize;x++){
        for(int y=0;y<GameDat->Game.GridSize;y++){
            Grid[x][y]=GameDat->Game.History[GameDat->Game.Actual].Grid[x][y];
        }
    }
    if(j>1){
        if(Grid[i][j-1]==find){
            Grid[i][j-1]=end;
            tmpj=j-2;
            while(tmpj>=0){
                if(Grid[i][tmpj]==end){
                    for(int x=0;x<GameDat->Game.GridSize;x++){
                        for(int y=0;y<GameDat->Game.GridSize;y++){
                            GameDat->Game.History[GameDat->Game.Actual].Grid[x][y]=Grid[x][y];
                        }
                    }
                }else{
                    if(Grid[i][tmpj]==0){
                        break;
                    }else{
                        Grid[i][tmpj]=end;
                        }
                }
                tmpj--;
            }
        }
    }

  //prepis dolu
    for(int x=0;x<GameDat->Game.GridSize;x++){
        for(int y=0;y<GameDat->Game.GridSize;y++){
            Grid[x][y]=GameDat->Game.History[GameDat->Game.Actual].Grid[x][y];
        }
    }
    if(j<size-2){
        if(Grid[i][j+1]==find){
            Grid[i][j+1]=end;
            tmpj=j+2;
            while(tmpj<size){
                if(Grid[i][tmpj]==end){
                    for(int x=0;x<GameDat->Game.GridSize;x++){
                        for(int y=0;y<GameDat->Game.GridSize;y++){
                            GameDat->Game.History[GameDat->Game.Actual].Grid[x][y]=Grid[x][y];
                        }
                    }
                }else{
                    if(Grid[i][tmpj]==0){
                        break;
                    }else{
                        Grid[i][tmpj]=end;
                    }
                }
                tmpj++;
            }
        }
    }

  //prepis vlevo dolu
    for(int x=0;x<GameDat->Game.GridSize;x++){
        for(int y=0;y<GameDat->Game.GridSize;y++){
            Grid[x][y]=GameDat->Game.History[GameDat->Game.Actual].Grid[x][y];
        }
    }
    if((i>1) and (j<size-2)){
        if(Grid[i-1][j+1]==find){
            Grid[i-1][j+1]=end;
            tmpj=j+2;
            tmpi=i-2;
            while((tmpj<size) and (tmpi>=0)){
                if(Grid[tmpi][tmpj]==end){
                    for(int x=0;x<GameDat->Game.GridSize;x++){
                        for(int y=0;y<GameDat->Game.GridSize;y++){
                            GameDat->Game.History[GameDat->Game.Actual].Grid[x][y]=Grid[x][y];
                        }
                    }
                }else{
                    if(Grid[tmpi][tmpj]==0){
                        break;
                    }else{
                        Grid[tmpi][tmpj]=end;
                    }
                }
                tmpj++;
                tmpi--;
            }
        }
    }

  //prepis vpravo dolu
    for(int x=0;x<GameDat->Game.GridSize;x++){
        for(int y=0;y<GameDat->Game.GridSize;y++){
            Grid[x][y]=GameDat->Game.History[GameDat->Game.Actual].Grid[x][y];
        }
    }
    if((i<size-2) and (j<size-2)){
        if(Grid[i+1][j+1]==find){
            Grid[i+1][j+1]=end;
            tmpj=j+2;
            tmpi=i+2;
            while((tmpj<size) and (tmpi<size)){
                if(Grid[tmpi][tmpj]==end){
                    for(int x=0;x<GameDat->Game.GridSize;x++){
                        for(int y=0;y<GameDat->Game.GridSize;y++){
                            GameDat->Game.History[GameDat->Game.Actual].Grid[x][y]=Grid[x][y];
                        }
                    }
                }else{
                    if(Grid[tmpi][tmpj]==0){
                        break;
                    }else{
                        Grid[tmpi][tmpj]=end;
                    }
                }
                tmpj++;
                tmpi++;
            }
        }
    }

  //prepis vlevo nahoru
    for(int x=0;x<GameDat->Game.GridSize;x++){
        for(int y=0;y<GameDat->Game.GridSize;y++){
            Grid[x][y]=GameDat->Game.History[GameDat->Game.Actual].Grid[x][y];
        }
    }
    if((i>1) and (j>1)){
        if(Grid[i-1][j-1]==find){
            Grid[i-1][j-1]=end;
            tmpj=j-2;
            tmpi=i-2;
            while((tmpj>=0) and (tmpi>=0)){
                if(Grid[tmpi][tmpj]==end){
                    for(int x=0;x<GameDat->Game.GridSize;x++){
                        for(int y=0;y<GameDat->Game.GridSize;y++){
                            GameDat->Game.History[GameDat->Game.Actual].Grid[x][y]=Grid[x][y];
                        }
                    }
                }else{
                    if(Grid[tmpi][tmpj]==0){
                        break;
                    }else{
                        Grid[tmpi][tmpj]=end;
                    }
                }
                tmpj--;
                tmpi--;
            }
        }
    }

  //prepis vpravo nahoru
    for(int x=0;x<GameDat->Game.GridSize;x++){
        for(int y=0;y<GameDat->Game.GridSize;y++){
            Grid[x][y]=GameDat->Game.History[GameDat->Game.Actual].Grid[x][y];
        }
    }
    if((i<size-2) and (j>1)){
        if(Grid[i+1][j-1]==find){
            Grid[i+1][j-1]=end;
            tmpj=j-2;
            tmpi=i+2;
            while((tmpj>=0) and (tmpi<size)){
                if(Grid[tmpi][tmpj]==end){
                    for(int x=0;x<GameDat->Game.GridSize;x++){
                        for(int y=0;y<GameDat->Game.GridSize;y++){
                            GameDat->Game.History[GameDat->Game.Actual].Grid[x][y]=Grid[x][y];
                        }
                    }
                }else{
                    if(Grid[tmpi][tmpj]==0){
                        break;
                    }else{
                    Grid[tmpi][tmpj]=end;
                    }
                }
                tmpj--;
                tmpi++;
            }
        }
    }
    return GameDat;
}

/**
 * @brief GameLogic::CanMove Tato metoda kontroluje, zda aktualní hrác může provedst nějaky tah.
 * @param GameDat Herní data.
 * @return Vrací logickou hodnotu, která určíje zda může aktualní hrač hrát.
 */
bool GameLogic::CanMove(GameData *GameDat){
    for(int i=0;i<GameDat->Game.GridSize;i++){
        for(int j=0;j<GameDat->Game.GridSize;j++){
            if(GameDat->Game.History[GameDat->Game.Actual].Grid[i][j]==0){
                if(this->SolveMove(GameDat->Game.History[GameDat->Game.Actual].Grid,i,j,GameDat->Game.GridSize,GameDat->Game.ActivePlayer)){
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * @brief GameLogic::ReCountScore Tato metoda slouží k přepočítaní skore po provedení tahu.
 * @param GameDat Herní data pro přepočítaní skore.
 * @return Vrací přepočítaná herní data.
 */
GameData * GameLogic::ReCountScore(GameData *GameDat){
    GameDat->Game.Player1Score=0;
    GameDat->Game.Player2Score=0;
    for(int i=0;i<GameDat->Game.GridSize;i++){
        for(int j=0;j<GameDat->Game.GridSize;j++){
            if(GameDat->Game.History[GameDat->Game.Actual].Grid[i][j]==1){
                GameDat->Game.Player1Score++;
            }
            if(GameDat->Game.History[GameDat->Game.Actual].Grid[i][j]==2){
                GameDat->Game.Player2Score++;
            }
        }
    }
    GameDat->Game.RemainingStones=(GameDat->Game.GridSize*GameDat->Game.GridSize)-GameDat->Game.Player1Score-GameDat->Game.Player2Score;
    return GameDat;
}
/**
 * @brief GameLogic::SolveMove Tato metoda kontroluje hra zadaný tah je proveditelný.
 * @param Grid Herní deska, která obsahuje udaje o aktualním stavu na hrací desce.
 * @param i Souřadnice osy x, na které ma být proveden tah.
 * @param j Souřadnice osy y, na které ma být proveden tah.
 * @param size Velikost hrací desky.
 * @param player Aktualní hráč na tahu.
 * @return Vrací logickou hornotu zda může být zadaný tah proveden.
 */
bool GameLogic::SolveMove(int Grid[12][12], int i, int j,int size,int player)
{
    int find=0;
    int end=0;
    int tmpi=i;
    int tmpj=j;
    if(player==0){
      find=2;
      end=1;
    }else{
      find=1;
      end=2;
    }
  //hledani vlevo
    if(i>1){
        if(Grid[i-1][j]==find){
            tmpi=i-2;
            while(tmpi>=0){
                if(Grid[tmpi][j]==end){
                    return true;
                }else{
                    if(Grid[tmpi][j]==0){
                        break;
                    }
                }
                tmpi--;
            }
        }
    }
    tmpi=i;
  //hledani vpravo
    if(i<size-2){
        if(Grid[i+1][j]==find){
            tmpi=i+2;
            while(tmpi<size){
                if(Grid[tmpi][j]==end){
                    return true;
                }else{
                    if(Grid[tmpi][j]==0){
                        break;
                    }
                }
                tmpi++;
            }
        }
    }

  //hledani nahoru
    if(j>1){
        if(Grid[i][j-1]==find){
            tmpj=j-2;
            while(tmpj>=0){
                if(Grid[i][tmpj]==end){
                    return true;
                }else{
                    if(Grid[i][tmpj]==0){
                        break;
                    }
                }
                tmpj--;
            }
        }
    }

  //hledani dolu
    if(j<size-2){
        if(Grid[i][j+1]==find){
            tmpj=j+2;
            while(tmpj<size){
                if(Grid[i][tmpj]==end){
                    return true;
                }else{
                    if(Grid[i][tmpj]==0){
                        break;
                    }
                }
                tmpj++;
            }
        }
    }

  //hledani vlevo dolu
    if((i>1) and (j<size-2)){
        if(Grid[i-1][j+1]==find){
            tmpj=j+2;
            tmpi=i-2;
            while((tmpj<size) and (tmpi>=0)){
                if(Grid[tmpi][tmpj]==end){
                    return true;
                }else{
                    if(Grid[tmpi][tmpj]==0){
                        break;
                    }
                }
                tmpj++;
                tmpi--;
            }
        }
    }

  //hledani vpravo dolu
    if((i<size-2) and (j<size-2)){
        if(Grid[i+1][j+1]==find){
            tmpj=j+2;
            tmpi=i+2;
            while((tmpj<size) and (tmpi<size)){
                if(Grid[tmpi][tmpj]==end){
                    return true;
                }else{
                    if(Grid[tmpi][tmpj]==0){
                        break;
                    }
                }
                tmpj++;
                tmpi++;
            }
        }
    }

  //hledani vlevo nahoru
    if((i>1) and (j>1)){
        if(Grid[i-1][j-1]==find){
            tmpj=j-2;
            tmpi=i-2;
            while((tmpj>=0) and (tmpi>=0)){
                if(Grid[tmpi][tmpj]==end){
                    return true;
                }else{
                    if(Grid[tmpi][tmpj]==0){
                        break;
                    }
                }
                tmpj--;
                tmpi--;
            }
        }
    }

  //hledani vpravo nahoru
    if((i<size-2) and (j>1)){
        if(Grid[i+1][j-1]==find){
            tmpj=j-2;
            tmpi=i+2;
            while((tmpj>=0) and (tmpi<size)){
                if(Grid[tmpi][tmpj]==end){
                    return true;
                }else{
                    if(Grid[tmpi][tmpj]==0){
                        break;
                    }
                }
                tmpj--;
                tmpi++;
            }
        }
    }

  return false;
}
