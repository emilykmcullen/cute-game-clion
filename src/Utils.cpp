#include "Utils.h"
#include <cmath>

float NormalizedVecsDotProduct(vec2 vecA, vec2 vecB)
{
    //Normalize the vectors 
    float lengthA = sqrt((vecA.x)*(vecA.x) + (vecA.y)*(vecA.y));
    float lengthB = sqrt((vecB.x)*(vecB.x) + (vecB.y)*(vecB.y));
    if (lengthB == 0 || lengthA == 0)
    {
        std::cout << "LengthA" << lengthA << ", lengthB" << lengthB << std::endl;

    }

    vec2 normalizedA = { (vecA.x)/lengthA, (vecA.y)/lengthA};
    vec2 normalizedB = { (vecB.x)/lengthB, (vecB.y)/lengthB};
    float dotProduct = (normalizedA.x * normalizedB.x) + (normalizedA.y * normalizedB.y);
    return dotProduct;
}

void NormalizeVector(vec2& vector)
{
    float magnitude = sqrt((vector.x)*(vector.x) + (vector.y)*(vector.y));
    if (magnitude == 0)
    {
        std::cout << "magnitude" << magnitude << std::endl;

    }
    vector = { (vector.x)/magnitude, (vector.y)/magnitude};
}

