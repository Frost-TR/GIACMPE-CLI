/**
 * @file   gameinteligence.h
 * @author Rys Tomáš, Tadeáš Kovář
 */

#ifndef GAMEINTELIGENCE_H
#define GAMEINTELIGENCE_H

#include "./Headers/gamedata.h"
#include "./Headers/gamelogic.h"

/**
 * @brief The GameInteligence class Třída obsahující herni inteligencí. Obsahuje 3 úrovně obtížnosti.
 */
class GameInteligence
{
public:
    GameInteligence();
    GameData *SwitchInteligence(GameData *GameDat);
private:
    GameData *Hard(GameData *GameDat);
    GameData *Medium(GameData *GameDat);
    GameData *Stupid(GameData *GameDat);
    struct ScoreArray{
        int i;
        int j;
        int diffscore;

    };
};

#endif // GAMEINTELIGENCE_H
