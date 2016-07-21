//
//  ofApp.h
//  hitrix2
//
//  Created by Damian Nahmiyas on 22/6/16.
//
//

#pragma once

#include "ofMain.h"
#include "ofxJSONRPC.h"
#include "ofxXmlSettings.h"
#include "I2Cdev.h"

class ofApp: public ofBaseApp{
public:
    void setup();
    //void draw();
    void exit();
    
    float HEX_to_DBL(uint8_t *data){
        float respuesta;
        long word32 = (data[0]<<24 | data[1]<<16 | data[2]<<8 | data[3]);
        word32 = word32 ^ 134217728;
        word32 = word32 - 134217728;
        respuesta = (float)word32/8388608;
        return respuesta*100;
    }
    void writeDSP(I2Cdev * bus, uint16_t intAddr,uint8_t *data){
        bus->writeBlock(intAddr, 4, data);
    }
    
    uint8_t* readDSP(I2Cdev * bus, uint16_t intAddr){
        uint8_t *data;
        data = new uint8_t[4];
        bus->readBlock(intAddr, 4, data);
        return data;
    }
        
    void vol1(){ vIndex = 0; writeDSP(bus, vol,volumes[vIndex]);}
    void vol2(){ vIndex = 1; writeDSP(bus, vol,volumes[vIndex]);}
    void vol3(){ vIndex = 2; writeDSP(bus, vol,volumes[vIndex]);}
    void vol4(){ vIndex = 3; writeDSP(bus, vol,volumes[vIndex]);}
    void vol5(){ vIndex = 4; writeDSP(bus, vol,volumes[vIndex]);}
    void vol6(){ vIndex = 5; writeDSP(bus, vol,volumes[vIndex]);}
    void vol7(){ vIndex = 6; writeDSP(bus, vol,volumes[vIndex]);}
    void vol8(){ vIndex = 7; writeDSP(bus, vol,volumes[vIndex]);}
    void vol9(){ vIndex = 8; writeDSP(bus, vol,volumes[vIndex]);}
    
    void getVol(ofx::JSONRPC::MethodArgs& args);

    // Register a no-argument notification method.
    void c1mute();
    void c1unmute();
    void c1(ofx::JSONRPC::MethodArgs& args);
    int c1b;
    
    void c2mute();
    void c2unmute();
    void c2(ofx::JSONRPC::MethodArgs& args);
    int c2b;
    
    void c3mute();
    void c3unmute();
    void c3(ofx::JSONRPC::MethodArgs& args);
    int c3b;
    
    void c4mute();
    void c4unmute();
    void c4(ofx::JSONRPC::MethodArgs& args);
    int c4b;
    
    void c5mute();
    void c5unmute();
    void c5(ofx::JSONRPC::MethodArgs& args);
    int c5b;
    
    void c6mute();
    void c6unmute();
    void c6(ofx::JSONRPC::MethodArgs& args);
    int c6b;
    
    void c7mute();
    void c7unmute();
    void c7(ofx::JSONRPC::MethodArgs& args);
    int c7b;
    
    void c8mute();
    void c8unmute();
    void c8(ofx::JSONRPC::MethodArgs& args);
    int c8b;
    
    void c9mute();
    void c9unmute();
    void c9(ofx::JSONRPC::MethodArgs& args);
    int c9b;
    
    void c10mute();
    void c10unmute();
    void c10(ofx::JSONRPC::MethodArgs& args);
    int c10b;

    void c1vol(ofx::JSONRPC::MethodArgs& args);
    void c2vol(ofx::JSONRPC::MethodArgs& args);
    void c3vol(ofx::JSONRPC::MethodArgs& args);
    void c4vol(ofx::JSONRPC::MethodArgs& args);
    void c5vol(ofx::JSONRPC::MethodArgs& args);
    void c6vol(ofx::JSONRPC::MethodArgs& args);
    void c7vol(ofx::JSONRPC::MethodArgs& args);
    void c8vol(ofx::JSONRPC::MethodArgs& args);
    void c9vol(ofx::JSONRPC::MethodArgs& args);
    void c10vol(ofx::JSONRPC::MethodArgs& args);

    ofx::HTTP::JSONRPCServer server;
    
    //i2c dev
    I2Cdev * bus;
    
    uint8_t *on;
    uint8_t *off;
    
    uint16_t mute_addr[10];
    uint16_t pick_addr[10];
    
    uint16_t vol;
    int vIndex;
    uint8_t **volumes;
    
    ofxXmlSettings XML;

};
