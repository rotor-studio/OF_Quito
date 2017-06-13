#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //Titulo con medidor de framerate
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    //Pintamos el fondo de negro
    ofBackground(0,0,0);
    
    //Declaraci√≥n de estado de las variables
    full=false;
    zoomIn=false;
    zoomOut=false;
    
    //Unidad astronomica en pixeles en nuestra pantalla
    AU = 1500;
    
    // 1 a√±o en frames
    YEAR = 2000;
    
    //Posici√≥n del zoom al arrancar el programa
    ZOOM = 0.3;
    
    //Tengo todos estos planetas
    planet.resize(750);
    
    
    //Nombre del archivo
    string archivo = "exoplanets-orbit.csv";
    
    //Cargo de la carpeta bin/data el archivo
    ofFile file(archivo);
    
    // Por si acaso.
    if(file.exists()==false){
        ofLogError("El archivo: " + archivo + " no esta!!!!");
    }
    
    //Espacio donde alojamos temporalmente el archivo
    ofBuffer buffer(file);
    
    //Estructura que lee todas la lineas
    for (ofBuffer::Line it = buffer.getLines().begin(),end = buffer.getLines().end(); it != end; ++it){
        
        //Line
        string line = *it;
        
        //Busca columnas
        vector<string> datosPlaneta = ofSplitString(line, ",");
        
        nombre = datosPlaneta[0];
        
        periodo = ofToFloat(datosPlaneta[1]);
        
        eje = ofToFloat(datosPlaneta[2]);
        
        //Esto es para comprobar si hay o no datos y si no hay ponemos uno nosotros.
        string rad = datosPlaneta[3];
        
        if(rad.length()==0){
            radio = 1;
        }else{
            radio = ofToFloat(datosPlaneta[3]);
        }
        //contador de planetas
        planetas=planetas+1;
        
    //ofLog() <<"Estos son nuestros datos: "+nombre+" / "+ofToString(periodo)+" / "+ofToString(eje)+" /  "+ofToString(radio);
        
        //Asignamos los valores inciales de cada planeta
        planet[planetas].init(planetas, nombre, periodo, eje, radio, YEAR, AU);
        
    }

    //Declaramos una textura simple
    trail.allocate(ofGetScreenWidth(),ofGetScreenHeight(), GL_RGBA);
    
    //Limpiar la pantalla
    trail.begin();
    ofClear(255,255,255,0);
    trail.end();
    
    
    //OSC SETUP
    envia.setup(HOST,PORT);
    
    //OSC SETUP
    server.setName("Planet Output");
    

}

//--------------------------------------------------------------
void ofApp::update(){
    
    //Habilitamos texturas con alfa
    ofEnableAlphaBlending();
    
    trail.begin();
    drawTextura();
    trail.end();
    
    
    //Espera que actives el zoom hacía afuera
    if(zoomOut){
        ZOOM = ofLerp(ZOOM,0.006,0.02);
    }
    
    //Espera que actives el zoom hacía adentro
    if(zoomIn){
        ZOOM = ofLerp(ZOOM,2,0.02);
    }
    
    //Aquí actualizamos nuestro update
    for(int i=0;i<planet.size();i=i+1){
        planet[i].update(ZOOM);
    }
    
    //OSC DATA PLANET
    ofxOscMessage mensaje;
    
    //Cuerpo del mensaje
    mensaje.setAddress("/datosPlaneta");
    
    //Variables del mensaje
    mensaje.addFloatArg(planet[50].X);
    mensaje.addFloatArg(planet[50].Y);
    mensaje.addStringArg(planet[50].NOMBRE);
    
    //Enviamos el mensaje
    envia.sendMessage(mensaje,false);
    

 //Pongamos a pantalla completa
 ofSetFullscreen(full);
  
}
//--------------------------------------------------------------
void ofApp::drawTextura(){
    
    alfa=20;
    
    if( ofGetKeyPressed('c') ){
        ofClear(255,255,255, 0);
    }
  
     ofFill();
     ofSetColor(255,255,255,alfa);
     ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    
    ofPushMatrix();
    
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofScale(ZOOM,ZOOM);

    //Estructura de repetici√≥n
    for(int i=0;i<planet.size();i=i+1){
        planet[i].draw();
    }
    ofPopMatrix();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    
    //Dibujamos el sol
    ofPushMatrix();
    ofPushStyle();
    
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofScale(ZOOM,ZOOM);
    
    ofFill();
    ofSetColor(255,150,0,200);
    ofDrawCircle(0,0,28);
    
    ofSetColor(255,255,0);
    ofDrawCircle(0,0,20);
    
    ofNoFill();
    ofSetColor(255);
    ofCircle(0,0, AU);
    
    ofCircle(0,0, AU*2);
    
    ofCircle(0,0, AU*10);


    
    ofPopStyle();
    
    
    ofPopMatrix();
    //Acabamos de dibujar el sol
    
    //Pintamos nuestra info en la pantalla
    ofSetColor(255);
    ofDrawBitmapString("Total exoplanetas: "+ofToString(planet.size()), 40, 40);
    ofDrawBitmapString("FrameRate: "+ofToString(ofGetFrameRate()), 40, 60);
    ofDrawBitmapString("Scale: "+ofToString(ZOOM), 40, 80);
    ofDrawBitmapString("Zoom Keys: a,z ", 40, 100);
    
    
    //Textura
    trail.draw(0,0);
    
    
    //Publica la pantalla vía syphon
    server.publishScreen();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    //Lee la tecla F y cambia la variable full
    if(key == 'f'){
        full=!full;
    }
    
    if(key == 'a'){
        zoomIn=true;
    }
    if(key == 's'){
        zoomOut=true;
    }
    

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if(key == 'a'){
        zoomIn=false;
    }
    if(key == 's'){
        zoomOut=false;
    }

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
