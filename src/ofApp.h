#pragma once

#include "ofMain.h"
#include "graph.hpp"
#include "ofxThreadedImageLoader.h"
#include "ofxFft.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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
        void releaseResources();
        void audioIn(ofSoundBuffer & input);

		

private:
    Graph G;
    vector < float > real_c;
    vector < float > imag_c;
    
    float** distance;
    int num_c;
    //float threshold = 0.9;
    float threshold = 2e-1;
    vector < int > path;
    //ofxThreadedImageLoader loader;
    vector<ofImage> images;
    int speedDivisor = 10;
   
    
    int start_c = 0;
    int end_c = 0;
    int counter = 0;
    
    //sound stuff
    ofSoundStream soundStream;
    const int bufferSize = 256;
    vector <float> leftCur;
    vector <float> rightCur;
    
    //FFT object
    const int fftSize = 256;
    ofxFft* fft;
    float* fftDataCur;
    float* fftDataPrev;
    
    // spectral flux between 2 buffers
    float spectralFlux;
    float prevSpectralFlux = 0.0;
    float maxValue = 0.0;
    
   bool finishedDrawing = true;
    
};
