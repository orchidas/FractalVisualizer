#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //threaded image loader is faster
    ofSetVerticalSync(true);
    soundStream.printDeviceList();
    
    //read numbers into buffer
    ofBuffer buffer = ofBufferFromFile("mandelbrot_boundary.txt");
    
    //read the poinTs of the mandelbrot set into vector of complex numbers
   
    for (auto line : buffer.getLines()){
        auto split = ofSplitString(line, "\t");
        auto re = ofToFloat(split[0]);
        auto im = ofToFloat(split[1]);
        real_c.push_back(re);
        imag_c.push_back(im);
    }
    
    num_c = real_c.size();
    distance = new float* [num_c];
    
    
    //now read image similarities between each pair
    /*ofBuffer buffer2 = ofBufferFromFile("julia_image_similarities.txt");
    
    int k = 0, l = 0;
    for(auto line : buffer2.getLines()){
        distance[k] = new float[num_c];
        auto split = ofSplitString(line, "\t");
        
        //ignore incomplete rows
        if (split.size() < num_c)
            continue;
        
        l = 0;
        for (auto str : split){
            
            //ssim is 1 if images are similar, so 1-ssim is the right
            //measure of distance
            
            distance[k][l] = 1.0-ofToFloat(str);
            cout << str << "," << distance[k][l] << "\t";
            l++;
        }
        k++;
        cout << "\n";
    }*/
    
    
    //add vertices and create empty adjacency matrix
    for(int i = 0; i < num_c; i++){
        G.addVertex(i);
    }
    G.initializeAdjacencyMatrix();
    
    
    //join the vertices based on distances between points on the mandelbrot set
    for(int i = 0; i < num_c; i++){
        distance[i] = new float[num_c];
        
        for (int j = 0; j < num_c; j++){
            if (i==j){
                distance[i][j] = 0.0;
                continue;
            }
            else{
                distance[i][j] = sqrt(pow((real_c.at(i) - real_c.at(j)),2) +
                                        pow((imag_c.at(i) - imag_c.at(j)),2));
                
                 
                //if the distance between points on the mandelbrot set are small enough
                //connect the vertices in the graph
                
                if (distance[i][j] <= threshold){
                    G.addEdge(i, j, distance[i][j]);
                    
                }
            }
        }
    }
    
    //for debugging
    /*cout << "Total number of edges in graph = " << G.getNumEdges() << endl;
        
    for (int i = 0; i < G.getNumVertices(); i++){
        std::vector <int> NIDs = G.getNeighbours(i);
        cout << "Neighbouring nodes of node " << i << " are :" << endl;
        for(auto elem : NIDs)
            cout << elem << "\t";
        cout << "\n";
    }
    

    start_c = 45;
    end_c = 90;
    path = G.djikstraSearch(start_c, end_c);
    cout << "The shortest path is" << endl;
    for(auto elem : path){
        cout << elem << "->" ;
    }*/
    
    //load all the images
    string path = "Figures/";
    images.resize(num_c);
    for(int i = 1; i <= num_c; i++){
        
        //loader.loadFromDisk(images[i-1], path + ofToString(i) + ".png");
        images[i-1].load(path + ofToString(i) + ".png");
        images[i-1].crop(150,120,874,800);
    }
    
    //setup audio
    leftCur.assign(bufferSize, 0.0);
    rightCur.assign(bufferSize, 0.0);
    
    ofSoundStreamSettings settings;
    // or by name
    auto devices = soundStream.getMatchingDevices("default");
    if(!devices.empty()){
        settings.setInDevice(devices[1]);
        cout << devices[1] << " has been set" << endl;
    }

    settings.setInListener(this);
    settings.sampleRate = 44100;
    settings.numOutputChannels = 0;
    settings.numInputChannels = 1;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);
 
    fft = ofxFft::create(fftSize, OF_FFT_WINDOW_HAMMING);
    fftDataPrev = new float[fftSize];
    fftDataCur = new float[fftSize];
    for(int i = 0; i < fftSize; i++)
        fftDataPrev[i] = 0.0;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //sound processing
    spectralFlux = 0.0;
    
    //take fft of left channel
    fft->setSignal(&leftCur[0]);
    
    //get magnitude and copy them to audio bins
    fftDataCur = fft->getAmplitude();
    
    
    //normalize FFT spectra
    maxValue = 0;
    for(int i = 0; i< fft->getBinSize(); i++){
        if(abs(fftDataCur[i]) > maxValue)
            maxValue = fftDataCur[i];
    }
    
    
    //calculate spectral flux
    for(int i = 0; i < fft->getBinSize();i++){
        if (maxValue != 0)
            fftDataCur[i] /= maxValue;
        spectralFlux += pow(fftDataCur[i] - fftDataPrev[i], 2);
    }
    spectralFlux = sqrt(spectralFlux);
    cout << "Spectral flux " << spectralFlux << endl;
    
    
    // if there is a significant change in flux
    if (abs(prevSpectralFlux - spectralFlux) >= thresholdFlux && finishedDrawing){
        
        start_c = end_c;
        end_c = (int)ofMap(spectralFlux, 0 , 5.0, 0, num_c);
        //cout << start_c << "," << end_c << endl;
        path = G.djikstraSearch(start_c, end_c);
    }
    
    
    
    // for next update
    //copy fftCur to fftPrev
    for(int i = 0; i < fft->getBinSize();i++)
        fftDataPrev[i] = fftDataCur[i];
    
    prevSpectralFlux = spectralFlux;

}

//--------------------------------------------------------------
void ofApp::draw(){
    /*
    1 would draw every frame
    2 every other frame
    3 every third frame, etc
    */
    
    if(path.size() == 0)
        return;
    
    if(ofGetFrameNum() % speedDivisor != 0)
    {
        images[path.at(counter)].draw(0,0,874,854);
    }
    //draw code here
    else{
    
        if (counter == 0)
            finishedDrawing = false;
        
        if (counter == path.size()-1){
            finishedDrawing = true;
            counter = 0;
        }
        else
            counter++;
    }
        
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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

void ofApp::audioIn(ofSoundBuffer &input){
    for (int i = 0; i < bufferSize; i++){
        leftCur[i]   = input[i*2];
        rightCur[i]  = input[i*2+1];
       }
}

void ofApp::releaseResources(){
    for(int i = 0; i < num_c; i++)
        delete [] distance[i];
}
