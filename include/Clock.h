#ifndef CLOCK_H_INCLUDED
#define CLOCK_H_INCLUDED

class Clock{
    private:
        double ticks = 0;
        double cumulative = 0;
        Clock() {}
    public:
        Clock(Clock const&) = delete;
        void operator=(Clock const&) = delete;

        float speed = 1;

        static Clock& instance(){
            static Clock instance;
            return instance;
        }

        void tick(float delta){
            ticks+=delta;
            cumulative += delta;
        }

        double getTick(){
            return this->ticks;
        }

        bool ticked(){
            bool t = (cumulative >= 10);
            if(t)
                cumulative = 0;
            return t;
        }
};



#endif // CLOCK_H_INCLUDED
