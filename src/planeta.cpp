//
//  planeta.cpp
//  Astrodata
//
//  Created by Rotor on 07/06/2017.
//
//

#include "planeta.h"


//-----------------------------------------------------------------------
void planeta::init(int num, string nombre, float periodo, float eje, float radio, float year,float au){
    
    NOMBRE=nombre;
    PERIODO=periodo;
    EJE=eje;
    RADIO=radio;
    YEAR=year;
    AU=au;
    
    theta=0;
    thetaSpeed=0;
    pixelRadius=0;
    
    pixelRadius= RADIO * 2;
    pixelAxis = EJE * AU;
    
    float periodInYears = PERIODO/365;
    float periodInFrames = periodInYears * YEAR;
    
    theta = ofRandom(2 * PI);
    thetaSpeed = (2 * PI) / periodInFrames;
    
    X=0;
    Y=0;
    
 
    
  //  ofLog() <<"Estos son nuestros datos: Planeta numero: "+ofToString(num)+" / "+nombre+" / "+ofToString(periodo)+" / "+ofToString(eje)+" /  "+ofToString(radio);
    
}
//-----------------------------------------------------------------------
void planeta::update(float zoom){
    
    ZOOM = zoom;
    
    //Posición.
    theta += thetaSpeed;
    
    X = sin(theta) * pixelAxis;
    Y = cos(theta) * pixelAxis;

}
//-----------------------------------------------------------------------
void planeta::draw(){
    
    ofPushMatrix();
    ofTranslate(X,Y);
    
    ofSetColor(255,0,0);
    ofDrawCircle(0,0,pixelRadius+4/ZOOM);
    
    ofPopMatrix();
    
    
    
}
