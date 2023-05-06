#ifndef STATE_H
#define STATE_H


class State
{
    public:
        State(){}
        virtual void Init() = 0;
        virtual void Render() = 0;
        virtual void Update() = 0;
        virtual void Clean() = 0;
        virtual void Listen() = 0;

    private:

};

#endif // STATE_H
