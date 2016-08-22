//
//  main.cpp
//  hitrix2
//
//  Created by Damian Nahmiyas on 22/6/16.
//
//

#include "ofApp.h"
#include "ofAppNoWindow.h"
int main()
{
	ofAppNoWindow window;
	ofSetupOpenGL(&window, 1024,768, OF_WINDOW);
    ofRunApp(std::make_shared<ofApp>());
}
