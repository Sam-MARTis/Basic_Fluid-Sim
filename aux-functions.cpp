#include<aux-functions.hpp> 
#include<random>

void print(const auto message)
{
    std::cout << message << std::endl;
};
auto clamp(const auto value, const auto min, const auto max)
{
    return (value < min) ? min : (value > max) ? max : value;
}
float randf(const float min, const float max){
    return min + ((float)rand()/RAND_MAX) * (max - min);
};