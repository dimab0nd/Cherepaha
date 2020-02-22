#ifndef CHEREPAHA_H
#define CHEREPAHA_H
#include <utility>

/**
 * Шаблонный класс чрепахи
 */
enum TurnDiraction {L,R};
enum StepDiraction {F,B};
enum Orientation   {Up, Right, Down,Left,};

class Cherepaha {
public:

    Cherepaha()
    {
        pos = std::make_pair(0,0);
        CurrentOrientation = Up;
    };

    std::pair<int,int> GetCurrentPos()
    {
        return pos;
    };

    Orientation GetCurrentOrientation()
    {
        return CurrentOrientation;
    };

    void SetTurn(TurnDiraction Dir)
    {
        switch ( Dir )
        {
        case L:
         if(CurrentOrientation == Up) CurrentOrientation = Left;
         else CurrentOrientation = Orientation((CurrentOrientation - 1 )%4 );
          break;

        case R:
            CurrentOrientation = Orientation((CurrentOrientation + 1 )%4 );
          break;
        }
    }

    void Step(StepDiraction Dir)
    {
        switch ( Dir )
        {
        case F:
            switch(CurrentOrientation)
            {
            case Up: pos.second++; break;
            case Left: pos.first--; break;
            case Right: pos.first++; break;
            case Down: pos.second--; break;
            }
        break;

        case B:
            switch(CurrentOrientation)
            {
            case Up: pos.second--; break;
            case Left: pos.first++; break;
            case Right: pos.first--; break;
            case Down: pos.second++; break;
            }
        break;
        }
    }

protected:
    std::pair<int,int> pos;
    Orientation CurrentOrientation;
};
#endif // CHEREPAHA_H
