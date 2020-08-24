#include <iostream>
#include <array>
#include <stdio.h>

#define TIMESTEP 1.0

using namespace std;

struct State{
    std::array<double, 3> position{0,0,0};
    std::array<double, 3> velocity{0,0,0};
    double time = 0.0;
};

State initial_conditions(){
    State initial;
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
    for(int i = 0; i<10; i++){
        printf("time: %g\n", ic.time);
        debug_print(ic.velocity);
        debug_print(ic.position);
        physics(ic, 1.0, gravity);
    }
    cout << "Hello world" << endl;
}

