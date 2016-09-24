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
    //control master volume
    void vol1(){ vIndex = 0; writeDSP(bus, vol,volumes[vIndex]);}
    void vol2(){ vIndex = 1; writeDSP(bus, vol,volumes[vIndex]);}
    void vol3(){ vIndex = 2; writeDSP(bus, vol,volumes[vIndex]);}
    void vol4(){ vIndex = 3; writeDSP(bus, vol,volumes[vIndex]);}
    void vol5(){ vIndex = 4; writeDSP(bus, vol,volumes[vIndex]);}
    void vol6(){ vIndex = 5; writeDSP(bus, vol,volumes[vIndex]);}
    void vol7(){ vIndex = 6; writeDSP(bus, vol,volumes[vIndex]);}
    void vol8(){ vIndex = 7; writeDSP(bus, vol,volumes[vIndex]);}
    void vol9(){ vIndex = 8; writeDSP(bus, vol,volumes[vIndex]);}

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
    
    //control master volume
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
    
    void getVol(ofx::JSONRPC::MethodArgs& args);
    
    
    //distortions
    void c1distor();
    void c2distor();
    void c3distor();
    void c4distor();
    void c5distor();
    void c6distor();
    void c7distor();
    void c8distor();
    void c9distor();
    void c10distor();
    
    void c1undistor();
    void c2undistor();
    void c3undistor();
    void c4undistor();
    void c5undistor();
    void c6undistor();
    void c7undistor();
    void c8undistor();
    void c9undistor();
    void c10undistor();
    
    int d1b;
    int d2b;
    int d3b;
    int d4b;
    int d5b;
    int d6b;
    int d7b;
    int d8b;
    int d9b;
    int d10b;
    
    void d1(ofx::JSONRPC::MethodArgs& args);
    void d2(ofx::JSONRPC::MethodArgs& args);
    void d3(ofx::JSONRPC::MethodArgs& args);
    void d4(ofx::JSONRPC::MethodArgs& args);
    void d5(ofx::JSONRPC::MethodArgs& args);
    void d6(ofx::JSONRPC::MethodArgs& args);
    void d7(ofx::JSONRPC::MethodArgs& args);
    void d8(ofx::JSONRPC::MethodArgs& args);
    void d9(ofx::JSONRPC::MethodArgs& args);
    void d10(ofx::JSONRPC::MethodArgs& args);
    
    void setEq(ofx::JSONRPC::MethodArgs& args);
    mutable std::mutex mutex;
    std::string userText;
    void setUserText(const std::string& text);
    
    ofx::HTTP::JSONRPCServer server;
    
    //parametriEQ        --------------------------------------------------//
    int fs = 192000;
    int gain = 0;
    //float frec = 100;
    //float q = 0.707;
    //float boost = -15;
    
    float bandParam[7][3];
    
    double ax;
    double omega;
    double seno;
    double coseno;
    double alpha;
    double a0;
    double gain_lin;
    
    double block[5];
    /*
    double b0;
    double b1;
    double b2;
    double a1;
    double a2;
    */
    uint16_t paramData[7][5];
    
    uint8_t * toHex(double n){
        uint8_t *buff;
        buff = new uint8_t[4];
        int c =(int)(n*pow(2,23));
        buff[0] = (c >> 24);
        buff[1] = (c >> 16);
        buff[2] = (c >> 8);
        buff[3] = (uint8_t)(c);
        return buff;
    }
    
    void calcEQ(float frec, float q, float boost, int band){
        bandParam[band][0] = frec;
        bandParam[band][1] = q;
        bandParam[band][2] = boost;
        
        ax = pow(10,(boost/40));
        omega = 2*PI*frec/fs;
        seno = sin(omega);
        coseno = cos(omega);
        alpha = seno/(2*q);
        a0 = 1+(alpha/ax);
        gain_lin = pow(10,(gain/20))/a0;
        /*
        b0 = (1+(alpha*ax))*gain_lin;
        b1 = -1*(2*coseno)*gain_lin;
        b2 = (1-(alpha*ax))*gain_lin;
        a1 = (-2*coseno)/a0;
        a2 = (1-(alpha/ax))/a0;
        */
        block[0] = (1+(alpha*ax))*gain_lin;
        block[1] = -1*(2*coseno)*gain_lin;
        block[2] = (1-(alpha*ax))*gain_lin;
        block[3] = (-2*coseno)/a0;
        block[4] = (1-(alpha/ax))/a0;
        
        for (int i = 0; i<5; i++)
            writeDSP(bus, paramData[band][i],toHex(block[i]));
    }
    //--------------------------------------------------------------------//
    
    //i2c dev
    I2Cdev * bus;
    
    uint8_t *on;
    uint8_t *off;
    uint8_t *on_dist;
    
    uint16_t mute_addr[10];
    uint16_t pick_addr[10];
    uint16_t distor_addr[10];
    
    uint16_t vol;
    int vIndex;
    uint8_t **volumes;
    
    ofxXmlSettings XML;
};
