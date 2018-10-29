#pragma once

class Material {

public:
    Material()
    {
    }
    Material(const double diffuse, const double specular) :
        diffuse(diffuse), specular(specular)
    {
    }

    // Values range from 0 to 1 and represent a portion of light for each
    double diffuse;
    double specular;

};
