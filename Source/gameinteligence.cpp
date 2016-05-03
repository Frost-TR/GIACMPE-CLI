/**
 * @file   gameinteligence.cpp
 * @author Rys Tomáš, Tadeáš Kovář
 */

#include "./Headers/gameinteligence.h"


/**
 * @brief GameInteligence::GameInteligence Konstruktor třídy. Nebyl využít
 */
GameInteligence::GameInteligence()
{

}

/**
 * @brief GameInteligence::SwitchInteligence Tato metoda určije jaká uroven inteligence ma být aplikována.
 * @param GameDat Herni data
 * @return Vraci herni data na které byla aplikována herní inteligence pro provedení tahu.
 */
GameData *GameInteligence::SwitchInteligence(GameData *GameDat)
{
    switch(GameDat->Game.AIlevel){
        case 0:
            return this->Hard(GameDat);
            break;
        case 1:
            return this->Medium(GameDat);
            break;
        case 2:
            return this->Stupid(GameDat);
            break;
    }
    return GameDat;
}

/**
 * @brief GameInteligence::Hard Metoda definující nejtěžší úroven herní inteligence.
 * @param GameDat Herní data
 * @return Vraci herni data na které byla aplikována herní inteligence pro provedení tahu.
 */
GameData *GameInteligence::Hard(GameData *GameDat)
{
    struct ScoreArray Score[200];
    int pointer=0;
    int actual=GameDat->Game.Actual;
    int last= GameDat->Game.Last;
    GameData *TmpGame = new GameData();
    TmpGame=GameDat;

    for(int i=0;i<GameDat->Game.GridSize;i++){
        for(int j=0;j<GameDat->Game.GridSize;j++){
            GameLogic *Logic = new GameLogic();
          if(TmpGame->Game.History[TmpGame->Game.Actual].Grid[i][j]==0){
            if(Logic->SolveMove(TmpGame->Game.History[TmpGame->Game.Actual].Grid,i,j,TmpGame->Game.GridSize,TmpGame->Game.ActivePlayer)){
                TmpGame = Logic->Move(TmpGame,i,j);
                Score[pointer].i=i;
                Score[pointer].j=j;
                int points=0;
                for(int x=0;x<GameDat->Game.GridSize;x++){
                    for(int y=0;y<GameDat->Game.GridSize;y++){
                        if((TmpGame->Game.History[TmpGame->Game.Actual].Grid[x][y])==2){
                            points++;
                        }
                    }
                }
                Score[pointer].diffscore=points-(GameDat->Game.Player2Score);
                points=0;
                TmpGame->Game.Actual=actual;
                TmpGame->Game.Last=last;
                TmpGame=GameDat;
                pointer++;
            }
          }
        }
    }
    int maxpointer=pointer;
    int max=Score[0].diffscore;
    int pointerOfMax=0;
    for(pointer=1;pointer<maxpointer;pointer++){
        if(Score[pointer].diffscore>max){
            max=Score[pointer].diffscore;
            pointerOfMax=pointer;
        }
    }
    GameLogic *Logic = new GameLogic();
    GameDat->Game.Actual=actual;
    GameDat->Game.Last=last;
    return Logic->Move(GameDat,Score[pointerOfMax].i,Score[pointerOfMax].j);
}

/**
 * @brief GameInteligence::Hard Metoda definující střední úroven herní inteligence.
 * @param GameDat Herní data
 * @return Vraci herni data na které byla aplikována herní inteligence pro provedení tahu.
 */
GameData *GameInteligence::Medium(GameData *GameDat)
{
    struct ScoreArray Score[200];
    int pointer=0;
    int actual=GameDat->Game.Actual;
    int last= GameDat->Game.Last;
    GameData *TmpGame = new GameData();
    TmpGame=GameDat;

    for(int i=0;i<GameDat->Game.GridSize;i++){
        for(int j=0;j<GameDat->Game.GridSize;j++){
            GameLogic *Logic = new GameLogic();
          if(TmpGame->Game.History[TmpGame->Game.Actual].Grid[i][j]==0){
            if(Logic->SolveMove(TmpGame->Game.History[TmpGame->Game.Actual].Grid,i,j,TmpGame->Game.GridSize,TmpGame->Game.ActivePlayer)){
                TmpGame = Logic->Move(TmpGame,i,j);
                Score[pointer].i=i;
                Score[pointer].j=j;
                int points=0;
                for(int x=0;x<GameDat->Game.GridSize;x++){
                    for(int y=0;y<GameDat->Game.GridSize;y++){
                        if((TmpGame->Game.History[TmpGame->Game.Actual].Grid[x][y])==2){
                            points++;
                        }
                    }
                }
                Score[pointer].diffscore=points-(GameDat->Game.Player2Score);
                points=0;
                TmpGame->Game.Actual=actual;
                TmpGame->Game.Last=last;
                TmpGame=GameDat;
                pointer++;
            }
          }
        }
    }
    int randomValue = qrand() % pointer;
    GameLogic *Logic = new GameLogic();
    GameDat->Game.Actual=actual;
    GameDat->Game.Last=last;
    return Logic->Move(GameDat,Score[randomValue].i,Score[randomValue].j);
}
/**
 * @brief GameInteligence::Hard Metoda definující trivialní úroven herní inteligence.
 * @param GameDat Herní data
 * @return Vraci herni data na které byla aplikována herní inteligence pro provedení tahu.
 */
GameData *GameInteligence::Stupid(GameData *GameDat)
{
    struct ScoreArray Score[200];
    int pointer=0;
    int actual=GameDat->Game.Actual;
    int last= GameDat->Game.Last;
    GameData *TmpGame = new GameData();
    TmpGame=GameDat;

    for(int i=0;i<GameDat->Game.GridSize;i++){
        for(int j=0;j<GameDat->Game.GridSize;j++){
            GameLogic *Logic = new GameLogic();
          if(TmpGame->Game.History[TmpGame->Game.Actual].Grid[i][j]==0){
            if(Logic->SolveMove(TmpGame->Game.History[TmpGame->Game.Actual].Grid,i,j,TmpGame->Game.GridSize,TmpGame->Game.ActivePlayer)){
                TmpGame = Logic->Move(TmpGame,i,j);
                Score[pointer].i=i;
                Score[pointer].j=j;
                int points=0;
                for(int x=0;x<GameDat->Game.GridSize;x++){
                    for(int y=0;y<GameDat->Game.GridSize;y++){
                        if((TmpGame->Game.History[TmpGame->Game.Actual].Grid[x][y])==2){
                            points++;
                        }
                    }
                }
                Score[pointer].diffscore=points-(GameDat->Game.Player2Score);
                points=0;
                TmpGame->Game.Actual=actual;
                TmpGame->Game.Last=last;
                TmpGame=GameDat;
                pointer++;
            }
           }
        }
    }
    int maxpointer=pointer;
    int min=Score[0].diffscore;
    int pointerOfMin=0;
    for(pointer=1;pointer<maxpointer;pointer++){
        if(Score[pointer].diffscore<min){
            min=Score[pointer].diffscore;
            pointerOfMin=pointer;
        }
    }
    GameLogic *Logic = new GameLogic();
    GameDat->Game.Actual=actual;
    GameDat->Game.Last=last;
    return Logic->Move(GameDat,Score[pointerOfMin].i,Score[pointerOfMin].j);
}
