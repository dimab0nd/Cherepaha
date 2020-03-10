#ifndef CHEREPAHA_H
#define CHEREPAHA_H
#include <QPair>


enum TurnDiraction {L,R};
enum StepDiraction {F,B};
enum Orientation   {Up, Right, Down,Left,};

class Cherepaha {
public:

    Cherepaha()
    {
        CurrentPos = qMakePair(0,0);
        CurrentOrientation = Up;
    };

    ~Cherepaha()
    {

    };

    QPair<int,int> GetCurrentPos()
    {
        return CurrentPos;
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

    Cherepaha operator+(StepDiraction Dir)
    {
        switch ( Dir )
        {
        case F:
            switch(CurrentOrientation)
            {
            case Up: CurrentPos.second++; break;
            case Left: CurrentPos.first--; break;
            case Right: CurrentPos.first++; break;
            case Down: CurrentPos.second--; break;
            }
        break;

        case B:
            switch(CurrentOrientation)
            {
            case Up: CurrentPos.second--; break;
            case Left: CurrentPos.first++; break;
            case Right: CurrentPos.first--; break;
            case Down: CurrentPos.second++; break;
            }
        break;
        }
        return *this;
    }


    Cherepaha operator*=(const unsigned int &count)
    {
        Orientation abstract_orientation = CurrentOrientation;
        QPair<int,int> abstract_pos(CurrentPos);

        for(int i=0;i<(count-1);i++)
        {
            switch (CurrentOrientation)
            {

            case Right:
                CurrentPos.first = CurrentPos.first + abstract_pos.second;
                CurrentPos.second = CurrentPos.second - abstract_pos.first;
            break;
            case Down:
                CurrentPos.first = this->CurrentPos.first - abstract_pos.first;
                CurrentPos.second = this->CurrentPos.second - abstract_pos.second;
            break;
            case Left:
               CurrentPos.first = CurrentPos.first - abstract_pos.second;
                CurrentPos.second = CurrentPos.second + abstract_pos.first;
            break;
            case Up:
                CurrentPos.first = CurrentPos.first + abstract_pos.first;
                CurrentPos.second = CurrentPos.second + abstract_pos.second;

            break;
            }
            CurrentOrientation = Orientation((CurrentOrientation + abstract_orientation)%4);

        }
        return *this;
    }


protected:

    QPair<int,int> CurrentPos;
    Orientation CurrentOrientation;
};
#endif // CHEREPAHA_H
