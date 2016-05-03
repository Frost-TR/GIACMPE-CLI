/**
 * @file   gamedata.h
 * @author Rys Tomáš, Tadeáš Kovář
 */

#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <QString>

/**
 * @brief The GameData class Tato třída slouží pouze pro uchovaní dat hry.
 */
class GameData
{
public:
    GameData();

    /**
     * @brief The gameHistoryList struct Struktura obsahujici jednotlivé herní pole
     */
    struct gameHistoryList{
        int Grid[12][12]; //0 prazdna 1 bila 2 cerna

    };

    /**
     * @brief The GameInfo struct Struktura obsahujicí data hry.
     */
    struct GameInfo{
        int GridSize;
        int Actual;
        int Last;
        int Player1Score;
        int Player2Score;
        int RemainingStones;
        int ActivePlayer; //0 player1 1 player2
        QString *Player1Name;
        QString *Player2Name;
        bool OpponentIsHuman;
        int AIlevel; // 0 very stupid 1 stupid
        struct gameHistoryList History[200];
    };

    struct GameInfo Game;
};

#endif // GAMEDATA_H
