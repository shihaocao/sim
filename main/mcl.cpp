#include <iostream>
#include <array>
#include <stdio.h>

#define TIMESTEP 1.0

using namespace std;

struct State{
    std::array<std::array<double, 3>, 10> data;
    unsigned char dp = 0; // data pointer
    std::array<double, 3> past_position{0,0,0};
    std::array<double, 3> position{0,0,0};
    std::array<double, 3> velocity{0,0,0};
    double time = 0.0;
};

class Vector {
    private:
        std::array<double, 3> buffer{0,0,0};
    public:

        double &operator[](int i) {
            if( i > 3 ) {
                throw "Index out of bounds";
            }
            return buffer[i];
        }    

        /**
         * @brief Construct a new Vector object - Default
         * 
         */
        Vector(){
            buffer[0] = 0;
            buffer[1] = 0;
            buffer[2] = 0;
        }

        Vector(double x, double y, double z){
            buffer[0] = x;
            buffer[1] = y;
            buffer[2] = z;
        }



    // Overload + operator to add two Box objects.
    Vector operator+(const Vector& b) {
        Vector ret;
        for(int i = 0; i<3; i++){
            ret.buffer[i] = this->buffer[i] + b.buffer[i];
        }
        return ret;
    }

    Vector operator-(const Vector& b) {
        Vector ret;
        for(int i = 0; i<3; i++){
            ret.buffer[i] = this->buffer[i] - b.buffer[i];
        }
        return ret;
    }
      
    Vector map(Vector&a, double func (double)){
        Vector ret;
        for(int i = 0; i<3; i++){
            ret[i] = func(a[i]);
        }
        return ret;
    }
};

State initial_conditions(){
    State initial;

    for(int i = 0; i<10; i++){
        initial.data[i] = initial.position;
    }

    return initial;
}

void physics(State& input, double timestep, std::array<double,3> forces){
    input.time = input.time + timestep;
    for(int i = 0; i<3; i++){
        input.velocity[i] = timestep * forces[i] + input.velocity[i];
    }
    for(int i = 0; i<3; i++){
        input.position[i] = timestep * input.velocity[i] + input.position[i];
    }
    
}

void control(State& input, double timestep, std::array<double,3> target){

    std::array<double, 3> gains{0,0,0};
    std::array<double, 3> p_errors{0,0,0};

    input.dp++;
    if(input.dp >= 10)
        input.dp = 0;
    input.data[input.dp] = input.position;

    for(int i = 0; i<3; i++){
        p_errors[i] = target[i] - input.position[i];
    }

    for(int i = 0; i<3; i++){
        
    }
    
}

void debug_print(std::array<double, 3>& arr){
    printf("%g,%g,%g\n", arr[0], arr[1], arr[2]);
}

void debug_print(std::string& label, std::array<double, 3>& arr){
    cout << label << " ";
    printf("%g,%g,%g\n", arr[0], arr[1], arr[2]);
}

int main(){
    State ic = initial_conditions();
    std::array<double, 3> gravity{0,0, - 9.81};
    for(int i = 0; i<100; i++){
        printf("time: %g\n", ic.time);
        debug_print(ic.velocity);
        debug_print(ic.position);
        physics(ic, 1.0, gravity);
    }
    cout << "Hello world" << endl;
}

