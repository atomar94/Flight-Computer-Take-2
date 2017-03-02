//valve.h





class valve
{

    valve(int power_pin, int receive_pin); //when we care if it worke
    valve(int power_pin); //when we don't care if it worked
    bool is_actuated();
    bool is_open();
    bool open_valve();
    bool close_valve()
    bool actuate();
    bool deactuate();

    private:
        bool is_normal_open;
        bool actuated;

};


























