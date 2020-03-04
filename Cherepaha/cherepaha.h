#ifndef CHEREPAHA_H
#define CHEREPAHA_H
#include <utility>//std::pair


enum TurnDiraction {L,R};
enum StepDiraction {F,B};
enum Orientation   {Up, Right, Down,Left,};

class Cherepaha {
public:

    Cherepaha()
    {
        CurrentPos = std::make_pair(0,0);
        CurrentOrientation = Up;
    };

    ~Cherepaha()
    {

    };

    std::pair<int,int> GetCurrentPos()
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
        std::pair<int,int> abstract_pos = CurrentPos;

        for(int i=0;i<(count-1);i++)
        {
            switch (CurrentOrientation)
            {

            case Right:
                CurrentPos.first += -abstract_pos.second;
                CurrentPos.second += abstract_pos.first;
            break;
            case Down:
                CurrentPos.first += -abstract_pos.first;
                CurrentPos.second += -abstract_pos.second;
            break;
            case Left:
                CurrentPos.first += abstract_pos.first;
                CurrentPos.second += -abstract_pos.first;
            break;
            case Up:
                CurrentPos.first += abstract_pos.first;
                CurrentPos.second += abstract_pos.second;
            break;
            }
            CurrentOrientation = Orientation((CurrentOrientation + abstract_orientation)%4);

        }
        return *this;
    }


protected:
    std::pair<int,int> CurrentPos;
    Orientation CurrentOrientation;
};
#endif // CHEREPAHA_H
