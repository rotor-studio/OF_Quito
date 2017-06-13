//
//  planeta.hpp
//  Astrodata
//
//  Created by Rotor on 07/06/2017.
//
//

#include "ofMain.h"

class planeta{
    
 public:
    
    void init(int num, string nombre, float periodo, float eje, float radio,float year, float au);
    void update(float zoom);
    void draw();
    
    //Declaramos posiciones variables
    float X,Y;
    
    //declaramos caracteristicas variables
    float RADIO,PERIODO,EJE,YEAR,AU,ZOOM;
    string NOMBRE;
    
    //declaramos conversiones
    float theta, thetaSpeed, pixelRadius, pixelAxis;

    
};
