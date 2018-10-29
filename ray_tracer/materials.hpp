#pragma once

class Material {

public:
    Material()
    {
    }
    Material(const double albedo) :
        albedo(albedo)
    {
    }

    double albedo;

};
