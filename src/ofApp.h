#pragma once

#include "ofMain.h"
#include "planeta.h"
#include "ofxOsc.h"
#include "ofxSyphon.h"

#define HOST "localhost"
#define PORT 12345


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void drawTextura();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    //Declaracion de variables
    bool full,zoomIn, zoomOut;
    
    //Variables de nuestro sistema
    float AU,YEAR,ZOOM;
    
    string nombre;
    float periodo, eje, radio;
    
    //contador de planetas
    int planetas;
    
    //Cantidad de alfa
    int alfa;
    
    //Declaramos los objetos
    vector <planeta> planet;
    
    //FBO
    ofFbo trail;
    
    //Osc
    ofxOscSender envia;
    
    //Syphon
    ofxSyphonServer server;
		
};
