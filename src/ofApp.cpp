//
//  ofApp.cpp
//  hitrix2
//
//  Created by Damian Nahmiyas on 22/6/16.
//
//

#include "ofApp.h"
#include "I2Cdev.h"
#include "DSP Completo HITRIX (con mux entrada)_IC_1_PARAM.h"
#include "DSP Completo HITRIX (con mux entrada)_IC_1.h"

extern void default_download_IC_1();

#define DSP_addr 0x3b

void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    if(!XML.load("saves.xml"))
        ofLogError("xml file not loaded!");
    
    default_download_IC_1();
    
    bus = new I2Cdev("/dev/i2c-1");
    bus->addressSet(DSP_addr);
   
    mute_addr[0] = MOD_CANAL_0_MUTENOSLEWALG1MUTE_ADDR;
    mute_addr[1] = MOD_CANAL_1_MUTENOSLEWALG5MUTE_ADDR;
    mute_addr[2] = MOD_CANAL_2_MUTENOSLEWALG3MUTE_ADDR;
    mute_addr[3] = MOD_CANAL_3_MUTENOSLEWALG6MUTE_ADDR;
    mute_addr[4] = MOD_CANAL_4_MUTENOSLEWALG7MUTE_ADDR;
    mute_addr[5] = MOD_CANAL_5_MUTENOSLEWALG8MUTE_ADDR;
    mute_addr[6] = MOD_CANAL_6_MUTENOSLEWALG9MUTE_ADDR;
    mute_addr[7] = MOD_CANAL_7_MUTENOSLEWALG10MUTE_ADDR;
    
    mute_addr[9] = MOD_CANAL_8_MUTENOSLEWALG2MUTE_ADDR;
    mute_addr[8] = MOD_CANAL_9_MUTENOSLEWALG4MUTE_ADDR;
    
    distor_addr[0] = MOD_DISTORS_0_ISON_ADDR;
    distor_addr[1] = MOD_DISTORS_0_ISON_ADDR;
    distor_addr[2] = MOD_DISTORS_0_ISON_ADDR;
    distor_addr[3] = MOD_DISTORS_0_ISON_ADDR;
    distor_addr[4] = MOD_DISTORS_0_ISON_ADDR;
    distor_addr[5] = MOD_DISTORS_0_ISON_ADDR;
    distor_addr[6] = MOD_DISTORS_0_ISON_ADDR;
    distor_addr[7] = MOD_DISTORS_0_ISON_ADDR;
    distor_addr[8] = MOD_DISTORS_0_ISON_ADDR;
    distor_addr[9] = MOD_DISTORS_0_ISON_ADDR;
    
    pick_addr[0] = MOD_READBACK_CANAL_0_READBACKALGSIGMA2001_ADDR;
    pick_addr[1] = MOD_READBACK_CANAL_1_READBACKALGSIGMA2002_ADDR;
    pick_addr[2] = MOD_READBACK_CANAL_2_READBACKALGSIGMA2003_ADDR;
    pick_addr[3] = MOD_READBACK_CANAL_3_READBACKALGSIGMA2004_ADDR;
    pick_addr[4] = MOD_READBACK_CANAL_4_READBACKALGSIGMA2005_ADDR;
    pick_addr[5] = MOD_READBACK_CANAL_5_READBACKALGSIGMA2006_ADDR;
    pick_addr[6] = MOD_READBACK_CANAL_6_READBACKALGSIGMA2007_ADDR;
    pick_addr[7] = MOD_READBACK_CANAL_7_READBACKALGSIGMA2008_ADDR;
    
    vol = MOD_VOLUMEN_GRAL_GAIN1940ALGNS1_ADDR;
    
    paramData[0][0] = MOD_PARAMEQ1_ALG0_STAGE0_B0_ADDR;
    paramData[0][1] = MOD_PARAMEQ1_ALG0_STAGE0_B1_ADDR;
    paramData[0][2] = MOD_PARAMEQ1_ALG0_STAGE0_B2_ADDR;
    paramData[0][3] = MOD_PARAMEQ1_ALG0_STAGE0_A0_ADDR;
    paramData[0][4] = MOD_PARAMEQ1_ALG0_STAGE0_A1_ADDR;
    
    paramData[1][0] = MOD_PARAMEQ1_ALG0_STAGE1_B0_ADDR;
    paramData[1][1] = MOD_PARAMEQ1_ALG0_STAGE1_B1_ADDR;
    paramData[1][2] = MOD_PARAMEQ1_ALG0_STAGE1_B2_ADDR;
    paramData[1][3] = MOD_PARAMEQ1_ALG0_STAGE1_A0_ADDR;
    paramData[1][4] = MOD_PARAMEQ1_ALG0_STAGE1_A1_ADDR;
    
    paramData[2][0] = MOD_PARAMEQ1_ALG0_STAGE2_B0_ADDR;
    paramData[2][1] = MOD_PARAMEQ1_ALG0_STAGE2_B1_ADDR;
    paramData[2][2] = MOD_PARAMEQ1_ALG0_STAGE2_B2_ADDR;
    paramData[2][3] = MOD_PARAMEQ1_ALG0_STAGE2_A0_ADDR;
    paramData[2][4] = MOD_PARAMEQ1_ALG0_STAGE2_A1_ADDR;
    
    paramData[3][0] = MOD_PARAMEQ1_ALG0_STAGE3_B0_ADDR;
    paramData[3][1] = MOD_PARAMEQ1_ALG0_STAGE3_B1_ADDR;
    paramData[3][2] = MOD_PARAMEQ1_ALG0_STAGE3_B2_ADDR;
    paramData[3][3] = MOD_PARAMEQ1_ALG0_STAGE3_A0_ADDR;
    paramData[3][4] = MOD_PARAMEQ1_ALG0_STAGE3_A1_ADDR;
    
    paramData[4][0] = MOD_PARAMEQ1_ALG0_STAGE4_B0_ADDR;
    paramData[4][1] = MOD_PARAMEQ1_ALG0_STAGE4_B1_ADDR;
    paramData[4][2] = MOD_PARAMEQ1_ALG0_STAGE4_B2_ADDR;
    paramData[4][3] = MOD_PARAMEQ1_ALG0_STAGE4_A0_ADDR;
    paramData[4][4] = MOD_PARAMEQ1_ALG0_STAGE4_A1_ADDR;
    
    paramData[5][0] = MOD_PARAMEQ1_ALG0_STAGE5_B0_ADDR;
    paramData[5][1] = MOD_PARAMEQ1_ALG0_STAGE5_B1_ADDR;
    paramData[5][2] = MOD_PARAMEQ1_ALG0_STAGE5_B2_ADDR;
    paramData[5][3] = MOD_PARAMEQ1_ALG0_STAGE5_A0_ADDR;
    paramData[5][4] = MOD_PARAMEQ1_ALG0_STAGE5_A1_ADDR;
    
    paramData[6][0] = MOD_PARAMEQ1_ALG0_STAGE6_B0_ADDR;
    paramData[6][1] = MOD_PARAMEQ1_ALG0_STAGE6_B1_ADDR;
    paramData[6][2] = MOD_PARAMEQ1_ALG0_STAGE6_B2_ADDR;
    paramData[6][3] = MOD_PARAMEQ1_ALG0_STAGE6_A0_ADDR;
    paramData[6][4] = MOD_PARAMEQ1_ALG0_STAGE6_A1_ADDR;
    
    //vIndex = 0;
    volumes = new uint8_t *[9];
    
    for (int i = 0; i<9; i++) {
        volumes[i] = new uint8_t[4];
    }
    
    volumes[0][0] = 0x00;
    volumes[0][1] = 0x80;
    volumes[0][2] = 0x00;
    volumes[0][3] = 0x00;
    
    volumes[1][0] = 0x00;
    volumes[1][1] = 0x50;
    volumes[1][2] = 0xc3;
    volumes[1][3] = 0x36;
    
    volumes[2][0] = 0x00;
    volumes[2][1] = 0x40;
    volumes[2][2] = 0x26;
    volumes[2][3] = 0xe7;
    
    volumes[3][0] = 0x00;
    volumes[3][1] = 0x28;
    volumes[3][2] = 0x7a;
    volumes[3][3] = 0x27;
    
    volumes[4][0] = 0x00;
    volumes[4][1] = 0x20;
    volumes[4][2] = 0x26;
    volumes[4][3] = 0xf3;
    
    volumes[5][0] = 0x00;
    volumes[5][1] = 0x14;
    volumes[5][2] = 0x49;
    volumes[5][3] = 0x61;
    
    volumes[6][0] = 0x00;
    volumes[6][1] = 0x10;
    volumes[6][2] = 0x1d;
    volumes[6][3] = 0x3f;
    
    volumes[7][0] = 0x00;
    volumes[7][1] = 0x0a;
    volumes[7][2] = 0x2a;
    volumes[7][3] = 0xdb;
    
    volumes[8][0] = 0x00;
    volumes[8][1] = 0x08;
    volumes[8][2] = 0x13;
    volumes[8][3] = 0x85;
    
    on = new uint8_t[4];
    on[0] = 0x00;
    on[1] = 0x80;
    on[2] = 0x00;
    on[3] = 0x00;
    
    off = new uint8_t[4];
    off[0] = 0x00;
    off[1] = 0x00;
    off[2] = 0x00;
    off[3] = 0x00;
    
    on_dist = new uint8_t[4];
    on_dist[0] = 0x00;
    on_dist[1] = 0x00;
    on_dist[2] = 0x00;
    on_dist[3] = 0x01;
    
    c1b = XML.getValue("SAVES:BT1",0);
    c2b = XML.getValue("SAVES:BT2",0);
    c3b = XML.getValue("SAVES:BT3",0);
    c4b = XML.getValue("SAVES:BT4",0);
    c5b = XML.getValue("SAVES:BT5",0);
    c6b = XML.getValue("SAVES:BT6",0);
    c7b = XML.getValue("SAVES:BT7",0);
    c8b = XML.getValue("SAVES:BT8",0);
    c9b = XML.getValue("SAVES:BT9",0);
    c10b = XML.getValue("SAVES:BT10",0);
    
    d1b = XML.getValue("SAVES:D1",0);
    d2b = XML.getValue("SAVES:D2",0);
    d3b = XML.getValue("SAVES:D3",0);
    d4b = XML.getValue("SAVES:D4",0);
    d5b = XML.getValue("SAVES:D5",0);
    d6b = XML.getValue("SAVES:D6",0);
    d7b = XML.getValue("SAVES:D7",0);
    d8b = XML.getValue("SAVES:D8",0);
    d9b = XML.getValue("SAVES:D9",0);
    d10b = XML.getValue("SAVES:D10",0);
    
    vIndex = XML.getValue("SAVES:VOL",0);
    for (int i = 0; i<7; i++) {
        byPass[i] = XML.getValue("SAVES:EQ:BD"+ ofToString(i+1) +":BP",0);
        bandParam[i][0] = XML.getValue("SAVES:EQ:BD"+ ofToString(i+1) +":FR",0);
        bandParam[i][1] = XML.getValue("SAVES:EQ:BD"+ ofToString(i+1) +":Q",0);
        bandParam[i][2] = XML.getValue("SAVES:EQ:BD"+ ofToString(i+1) +":BS",0);
        
        if (byPass[i]) {
            calcEQ(bandParam[i][0],
                   bandParam[i][1],
                   bandParam[i][2],
                   i);
        }
        else{
            //disable EQ band
            disableEQBand(i);
        }
    }
    
    if (c1b) {
        writeDSP(bus, mute_addr[0],on);
    }
    if (c2b) {
        writeDSP(bus, mute_addr[1],on);
    }
    if (c3b) {
        writeDSP(bus, mute_addr[2],on);
    }
    if (c4b) {
        writeDSP(bus, mute_addr[3],on);
    }
    if (c5b) {
        writeDSP(bus, mute_addr[4],on);
    }
    if (c6b) {
        writeDSP(bus, mute_addr[5],on);
    }
    if (c7b) {
        writeDSP(bus, mute_addr[6],on);
    }
    if (c8b) {
        writeDSP(bus, mute_addr[7],on);
    }
    if (c9b) {
        writeDSP(bus, mute_addr[8],on);
    }
    if (c10b) {
        writeDSP(bus, mute_addr[9],on);
    }
    
    if (d1b) {
        writeDSP(bus, distor_addr[0],on_dist);
    }
    if (d2b) {
        writeDSP(bus, distor_addr[1],on_dist);
    }
    if (d3b) {
        writeDSP(bus, distor_addr[2],on_dist);
    }
    if (d4b) {
        writeDSP(bus, distor_addr[3],on_dist);
    }
    if (d5b) {
        writeDSP(bus, distor_addr[4],on_dist);
    }
    if (d6b) {
        writeDSP(bus, distor_addr[5],on_dist);
    }
    if (d7b) {
        writeDSP(bus, distor_addr[6],on_dist);
    }
    if (d8b) {
        writeDSP(bus, distor_addr[7],on_dist);
    }
    if (d9b) {
        writeDSP(bus, distor_addr[8],on_dist);
    }
    if (d10b) {
        writeDSP(bus, distor_addr[9],on_dist);
    }
    
    writeDSP(bus, vol,volumes[vIndex]);

    ofx::HTTP::JSONRPCServerSettings settings;
    settings.setPort(8080);

    server.setup(settings);

    // Register RPC methods.
    server.registerMethod("vol0",
                          "Set master volume.",
                          this,
                          &ofApp::vol1);
    server.registerMethod("vol-3",
                          "Set master volume.",
                          this,
                          &ofApp::vol2);
    server.registerMethod("vol-6",
                          "Set master volume.",
                          this,
                          &ofApp::vol3);
    server.registerMethod("vol-9",
                          "Set master volume.",
                          this,
                          &ofApp::vol4);
    server.registerMethod("vol-12",
                          "Set master volume.",
                          this,
                          &ofApp::vol5);
    server.registerMethod("vol-15",
                          "Set master volume.",
                          this,
                          &ofApp::vol6);
    server.registerMethod("vol-18",
                          "Set master volume.",
                          this,
                          &ofApp::vol7);
    server.registerMethod("vol-21",
                          "Set master volume.",
                          this,
                          &ofApp::vol8);
    server.registerMethod("vol-24",
                          "Set master volume.",
                          this,
                          &ofApp::vol9);

    
    server.registerMethod("getVol",
                          "Returns index volume.",
                          this,
                          &ofApp::getVol);
    
    server.registerMethod("c1",
                          "Get volume status.",
                          this,
                          &ofApp::c1);
    server.registerMethod("c1mute",
                          "mute channel",
                          this,
                          &ofApp::c1mute);
    server.registerMethod("c1unmute",
                           "unmute channel",
                          this,
                          &ofApp::c1unmute);
    
    server.registerMethod("c2",
                          "Get volume status.",
                          this,
                          &ofApp::c2);
    server.registerMethod("c2mute",
                          "mute channel",
                          this,
                          &ofApp::c2mute);
    server.registerMethod("c2unmute",
                          "unmute channel",
                          this,
                          &ofApp::c2unmute);
    
    server.registerMethod("c3",
                          "Get volume status.",
                          this,
                          &ofApp::c3);
    server.registerMethod("c3mute",
                          "mute channel",
                          this,
                          &ofApp::c3mute);
    server.registerMethod("c3unmute",
                          "unmute channel",
                          this,
                          &ofApp::c3unmute);
    
    server.registerMethod("c4",
                          "Get volume status.",
                          this,
                          &ofApp::c4);
    server.registerMethod("c4mute",
                          "mute channel",
                          this,
                          &ofApp::c4mute);
    server.registerMethod("c4unmute",
                          "unmute channel",
                          this,
                          &ofApp::c4unmute);
    
    server.registerMethod("c5",
                          "Get volume status.",
                          this,
                          &ofApp::c5);
    server.registerMethod("c5mute",
                         "mute channel",
                          this,
                          &ofApp::c5mute);
    server.registerMethod("c5unmute",
                          "unmute channel",
                          this,
                          &ofApp::c5unmute);
    
    server.registerMethod("c6",
                          "Get volume status.",
                          this,
                          &ofApp::c6);
    server.registerMethod("c6mute",
                          "mute channel",
                          this,
                          &ofApp::c6mute);
    server.registerMethod("c6unmute",
                          "unmute channel",
                          this,
                          &ofApp::c6unmute);
    
    server.registerMethod("c7",
                          "Get volume status.",
                          this,
                          &ofApp::c7);
    server.registerMethod("c7mute",
                          "mute channel",
                          this,
                          &ofApp::c7mute);
    server.registerMethod("c7unmute",
                          "unmute channel",
                          this,
                          &ofApp::c7unmute);
    
    server.registerMethod("c8",
                          "Get volume status.",
                          this,
                          &ofApp::c8);
    server.registerMethod("c8mute",
                          "mute channel",
                          this,
                          &ofApp::c8mute);
    server.registerMethod("c8unmute",
                          "unmute channel",
                          this,
                          &ofApp::c8unmute);
    
    server.registerMethod("c9",
                          "Get volume status.",
                          this,
                          &ofApp::c9);
    server.registerMethod("c9mute",
                          "mute channel",
                          this,
                          &ofApp::c9mute);
    server.registerMethod("c9unmute",
                          "unmute channel",
                          this,
                          &ofApp::c9unmute);
    
    server.registerMethod("c10",
                          "Get volume status.",
                          this,
                          &ofApp::c10);
    server.registerMethod("c10mute",
                          "mute channel",
                          this,
                          &ofApp::c10mute);
    server.registerMethod("c10unmute",
                          "unmute channel",
                          this,
                          &ofApp::c10unmute);


    server.registerMethod("c1vol",
                          "Returns channel pick value [0,100].",
                          this,
                          &ofApp::c1vol);
    server.registerMethod("c2vol",
                          "Returns channel pick value [0,100].",
                          this,
                          &ofApp::c2vol);
    server.registerMethod("c3vol",
                          "Returns channel pick value [0,100].",
                          this,
                          &ofApp::c3vol);
    server.registerMethod("c4vol",
                          "Returns channel pick value [0,100].",
                          this,
                          &ofApp::c4vol);
    server.registerMethod("c5vol",
                          "Returns channel pick value [0,100].",
                          this,
                          &ofApp::c5vol);
    server.registerMethod("c6vol",
                          "Returns channel pick value [0,100].",
                          this,
                          &ofApp::c6vol);
    server.registerMethod("c7vol",
                          "Returns channel pick value [0,100].",
                          this,
                          &ofApp::c7vol);
    server.registerMethod("c8vol",
                          "Returns channel pick value [0,100].",
                          this,
                          &ofApp::c8vol);
    server.registerMethod("c9vol",
                          "Returns channel pick value [0,100].",
                          this,
                          &ofApp::c9vol);
    server.registerMethod("c10vol",
                          "Returns channel pick value [0,100].",
                          this,
                          &ofApp::c10vol);
    //distortion /-------------------------------------
    server.registerMethod("c1dist",
                          "distortion channel",
                          this,
                          &ofApp::c1distor);
    server.registerMethod("c1und",
                          "distortion channel",
                          this,
                          &ofApp::c1undistor);
    server.registerMethod("c1d",
                          "Returns distortion state.",
                          this,
                          &ofApp::d1);
    
    server.registerMethod("c2dist",
                          "distortion channel",
                          this,
                          &ofApp::c1distor);
    server.registerMethod("c2und",
                          "distortion channel",
                          this,
                          &ofApp::c1undistor);
    server.registerMethod("c2d",
                          "Returns distortion state.",
                          this,
                          &ofApp::d1);
    
    server.registerMethod("c3dist",
                          "distortion channel",
                          this,
                          &ofApp::c1distor);
    server.registerMethod("c3und",
                          "distortion channel",
                          this,
                          &ofApp::c1undistor);
    server.registerMethod("c3d",
                          "Returns distortion state.",
                          this,
                          &ofApp::d1);
    
    server.registerMethod("c4dist",
                          "distortion channel",
                          this,
                          &ofApp::c1distor);
    server.registerMethod("c4und",
                          "distortion channel",
                          this,
                          &ofApp::c1undistor);
    server.registerMethod("c4d",
                          "Returns distortion state.",
                          this,
                          &ofApp::d1);
    
    server.registerMethod("c5dist",
                          "distortion channel",
                          this,
                          &ofApp::c1distor);
    server.registerMethod("c5und",
                          "distortion channel",
                          this,
                          &ofApp::c1undistor);
    server.registerMethod("c5d",
                          "Returns distortion state.",
                          this,
                          &ofApp::d1);
    
    
    server.registerMethod("c6dist",
                          "distortion channel",
                          this,
                          &ofApp::c1distor);
    server.registerMethod("c6und",
                          "distortion channel",
                          this,
                          &ofApp::c1undistor);
    server.registerMethod("c6d",
                          "Returns distortion state.",
                          this,
                          &ofApp::d1);
    
    server.registerMethod("c7dist",
                          "distortion channel",
                          this,
                          &ofApp::c1distor);
    server.registerMethod("c7und",
                          "distortion channel",
                          this,
                          &ofApp::c1undistor);
    server.registerMethod("c7d",
                          "Returns distortion state.",
                          this,
                          &ofApp::d1);
    
    server.registerMethod("c8dist",
                          "distortion channel",
                          this,
                          &ofApp::c1distor);
    server.registerMethod("c8und",
                          "distortion channel",
                          this,
                          &ofApp::c1undistor);
    server.registerMethod("c8d",
                          "Returns distortion state.",
                          this,
                          &ofApp::d1);
    
    server.registerMethod("c9dist",
                          "distortion channel",
                          this,
                          &ofApp::c1distor);
    server.registerMethod("c9und",
                          "distortion channel",
                          this,
                          &ofApp::c1undistor);
    server.registerMethod("c9d",
                          "Returns distortion state.",
                          this,
                          &ofApp::d1);
    
    server.registerMethod("c10dist",
                          "distortion channel",
                          this,
                          &ofApp::c1distor);
    server.registerMethod("c10und",
                          "distortion channel",
                          this,
                          &ofApp::c1undistor);
    server.registerMethod("c10d",
                          "Returns distortion state.",
                          this,
                          &ofApp::d1);
    
    server.registerMethod("setEq",
                          "Sets text from the user.",
                          this,
                          &ofApp::setEq);

    server.start();
}

void ofApp::setEq(ofx::JSONRPC::MethodArgs& args){
    setUserText(args.params.asString());
    ofLogVerbose("setEq") << args.params.asString();
    string cad = args.params.asString();
    vector<string> splitItems = ofSplitString(cad, "_");
    /*
    if (splitItems.size() == 4) {
        bandParam[splitItems.[0]][0] = splitItems.[1];
        bandParam[splitItems.[0]][1] = splitItems.[2];
        bandParam[splitItems.[0]][2] = splitItems.[3];
        
        calcEQ(splitItems.[1],
               splitItems.[2],
               splitItems.[3],
               splitItems.[0]);
    }*/
}
/*
void ofApp:getVol(ofx::JSONRPC::MethodArgs& args){
    args.params.asString()
}
*/
void ofApp::setUserText(const std::string& text){
    std::unique_lock<std::mutex> lock(mutex);
    userText = text;
}

void ofApp::exit(){
    ofLogToConsole();
    XML.setValue("SAVES:BT1", c1b);
    XML.setValue("SAVES:BT2", c2b);
    XML.setValue("SAVES:BT3", c3b);
    XML.setValue("SAVES:BT4", c4b);
    XML.setValue("SAVES:BT5", c5b);
    XML.setValue("SAVES:BT6", c6b);
    XML.setValue("SAVES:BT7", c7b);
    XML.setValue("SAVES:BT8", c8b);
    XML.setValue("SAVES:BT9", c9b);
    XML.setValue("SAVES:BT10", c10b);
    
    XML.setValue("SAVES:D1", c1b);
    XML.setValue("SAVES:D2", c2b);
    XML.setValue("SAVES:D3", c3b);
    XML.setValue("SAVES:D4", c4b);
    XML.setValue("SAVES:D5", c5b);
    XML.setValue("SAVES:D6", c6b);
    XML.setValue("SAVES:D7", c7b);
    XML.setValue("SAVES:D8", c8b);
    XML.setValue("SAVES:D9", c9b);
    XML.setValue("SAVES:D10", c10b);
    
    XML.setValue("SAVES:VOL", vIndex);

    XML.saveFile("saves.xml");
}

void ofApp::getVol(ofx::JSONRPC::MethodArgs& args){
    args.result = vIndex*(-3);
    //args.result = vIndex;
    //ofLogVerbose("getVol") << vIndex;
    
}

void ofApp::c1unmute(){
    writeDSP(bus, mute_addr[0],on);
    c1b = 1;
}
void ofApp::c1mute(){
    writeDSP(bus, mute_addr[0],off);
    c1b = 0;
}
void ofApp::c1(ofx::JSONRPC::MethodArgs& args){
    args.result = c1b;
    //ofLogVerbose("c1") << args.result.asString();
}//-------------------------------------------
void ofApp::c2unmute(){
    writeDSP(bus, mute_addr[1],on);
    c2b = 1;
}
void ofApp::c2mute(){
    writeDSP(bus, mute_addr[1],off);
    c2b = 0;
}
void ofApp::c2(ofx::JSONRPC::MethodArgs& args){
    args.result = c2b;
    //ofLogVerbose("c2") << args.result.asString();
}//-------------------------------------------
void ofApp::c3unmute(){
    writeDSP(bus, mute_addr[2],on);
    c3b = 1;
}
void ofApp::c3mute(){
    writeDSP(bus, mute_addr[2],off);
    c3b = 0;
}
void ofApp::c3(ofx::JSONRPC::MethodArgs& args){
    args.result = c3b;
    //ofLogVerbose("c3") << args.result.asString();
}//-------------------------------------------
void ofApp::c4unmute(){
    writeDSP(bus, mute_addr[3],on);
    c4b = 1;
}
void ofApp::c4mute(){
    writeDSP(bus, mute_addr[3],off);
    c4b = 0;
}
void ofApp::c4(ofx::JSONRPC::MethodArgs& args){
    args.result = c4b;
    //ofLogVerbose("c4") << args.result.asString();
}//-------------------------------------------
void ofApp::c5unmute(){
    writeDSP(bus, mute_addr[4],on);
    c5b = 1;
}
void ofApp::c5mute(){
    writeDSP(bus, mute_addr[4],off);
    c5b = 0;
}
void ofApp::c5(ofx::JSONRPC::MethodArgs& args){
    args.result = c5b;
    //ofLogVerbose("c5") << args.result.asString();
}//-------------------------------------------
void ofApp::c6unmute(){
    writeDSP(bus, mute_addr[5],on);
    c6b = 1;
}
void ofApp::c6mute(){
    writeDSP(bus, mute_addr[5],off);
    c6b = 0;
}
void ofApp::c6(ofx::JSONRPC::MethodArgs& args){
    args.result = c6b;
    //ofLogVerbose("c6") << args.result.asString();
}//-------------------------------------------
void ofApp::c7unmute(){
    writeDSP(bus, mute_addr[6],on);
    c7b = 1;
}
void ofApp::c7mute(){
    writeDSP(bus, mute_addr[6],off);
    c7b = 0;
}
void ofApp::c7(ofx::JSONRPC::MethodArgs& args){
    args.result = c7b;
    //ofLogVerbose("c7") << args.result.asString();
}//-------------------------------------------
void ofApp::c8unmute(){
    writeDSP(bus, mute_addr[7],on);
    c8b = 1;
}
void ofApp::c8mute(){
    writeDSP(bus, mute_addr[7],off);
    c8b = 0;
}
void ofApp::c8(ofx::JSONRPC::MethodArgs& args){
    args.result = c8b;
    //ofLogVerbose("c8") << args.result.asString();
}//-------------------------------------------
void ofApp::c9unmute(){
    writeDSP(bus, mute_addr[8],on);
    c9b = 1;
}
void ofApp::c9mute(){
    writeDSP(bus, mute_addr[8],off);
    c9b = 0;
}
void ofApp::c9(ofx::JSONRPC::MethodArgs& args){
    args.result = c9b;
    //ofLogVerbose("c9") << args.result.asString();
}//-------------------------------------------
void ofApp::c10unmute(){
    writeDSP(bus, mute_addr[9],on);
    c10b = 1;
}
void ofApp::c10mute(){
    writeDSP(bus, mute_addr[9],off);
    c10b = 0;
}
void ofApp::c10(ofx::JSONRPC::MethodArgs& args){
    args.result = c10b;
    //ofLogVerbose("c10") << args.result.asString();
}//-------------------------------------------

void ofApp::c1vol(ofx::JSONRPC::MethodArgs& args){
    args.result = HEX_to_DBL(readDSP(bus, pick_addr[0]));
    //args.result = 25;
    //ofLogVerbose("c1vol") << args.result.asString();
}
void ofApp::c2vol(ofx::JSONRPC::MethodArgs& args){
    args.result = HEX_to_DBL(readDSP(bus, pick_addr[1]));
    //ofLogVerbose("c2vol") << args.result.asString();
}
void ofApp::c3vol(ofx::JSONRPC::MethodArgs& args){
    args.result = HEX_to_DBL(readDSP(bus, pick_addr[2]));
    //ofLogVerbose("c3vol") << args.result.asString();
}
void ofApp::c4vol(ofx::JSONRPC::MethodArgs& args){
    args.result = HEX_to_DBL(readDSP(bus, pick_addr[3]));
    //ofLogVerbose("c4vol") << args.result.asString();
}
void ofApp::c5vol(ofx::JSONRPC::MethodArgs& args){
    args.result = HEX_to_DBL(readDSP(bus, pick_addr[4]));
    //ofLogVerbose("c5vol") << args.result.asString();
}
void ofApp::c6vol(ofx::JSONRPC::MethodArgs& args){
    args.result = HEX_to_DBL(readDSP(bus, pick_addr[5]));
    //ofLogVerbose("c6vol") << args.result.asString();
}
void ofApp::c7vol(ofx::JSONRPC::MethodArgs& args){
    args.result = HEX_to_DBL(readDSP(bus, pick_addr[6]));
    //ofLogVerbose("c7vol") << args.result.asString();
}
void ofApp::c8vol(ofx::JSONRPC::MethodArgs& args){
    args.result = HEX_to_DBL(readDSP(bus, pick_addr[7]));
    //ofLogVerbose("c8vol") << args.result.asString();
}
void ofApp::c9vol(ofx::JSONRPC::MethodArgs& args){
    args.result = HEX_to_DBL(readDSP(bus, pick_addr[7]));
    //ofLogVerbose("c9vol") << args.result.asString();
}
void ofApp::c10vol(ofx::JSONRPC::MethodArgs& args){
    args.result = HEX_to_DBL(readDSP(bus, pick_addr[8]));
    //ofLogVerbose("c10vol") << args.result.asString();
}

void ofApp::c1distor(){
    writeDSP(bus, distor_addr[0],on_dist);
    d1b = 1;
}
void ofApp::c1undistor(){
    writeDSP(bus, distor_addr[0],off);
    d1b = 0;
}
void ofApp::c2distor(){
    writeDSP(bus, distor_addr[1],on_dist);
    d1b = 1;
}
void ofApp::c2undistor(){
    writeDSP(bus, distor_addr[1],off);
    d1b = 0;
}
void ofApp::c3distor(){
    writeDSP(bus, distor_addr[2],on_dist);
    d1b = 1;
}
void ofApp::c3undistor(){
    writeDSP(bus, distor_addr[2],off);
    d1b = 0;
}
void ofApp::c4distor(){
    writeDSP(bus, distor_addr[3],on_dist);
    d1b = 1;
}
void ofApp::c4undistor(){
    writeDSP(bus, distor_addr[3],off);
    d1b = 0;
}
void ofApp::c5distor(){
    writeDSP(bus, distor_addr[4],on_dist);
    d1b = 1;
}
void ofApp::c5undistor(){
    writeDSP(bus, distor_addr[4],off);
    d1b = 0;
}
void ofApp::c6distor(){
    writeDSP(bus, distor_addr[5],on_dist);
    d1b = 1;
}
void ofApp::c6undistor(){
    writeDSP(bus, distor_addr[5],off);
    d1b = 0;
}
void ofApp::c7distor(){
    writeDSP(bus, distor_addr[6],on_dist);
    d1b = 1;
}
void ofApp::c7undistor(){
    writeDSP(bus, distor_addr[6],off);
    d1b = 0;
}
void ofApp::c8distor(){
    writeDSP(bus, distor_addr[7],on_dist);
    d1b = 1;
}
void ofApp::c8undistor(){
    writeDSP(bus, distor_addr[7],off);
    d1b = 0;
}
void ofApp::c9distor(){
    writeDSP(bus, distor_addr[8],on_dist);
    d1b = 1;
}
void ofApp::c9undistor(){
    writeDSP(bus, distor_addr[8],off);
    d1b = 0;
}
void ofApp::c10distor(){
    writeDSP(bus, distor_addr[9],on_dist);
    d1b = 1;
}
void ofApp::c10undistor(){
    writeDSP(bus, distor_addr[9],off);
    d1b = 0;
}
void ofApp::d1(ofx::JSONRPC::MethodArgs& args){args.result = d1b;}
void ofApp::d2(ofx::JSONRPC::MethodArgs& args){args.result = d2b;}
void ofApp::d3(ofx::JSONRPC::MethodArgs& args){args.result = d3b;}
void ofApp::d4(ofx::JSONRPC::MethodArgs& args){args.result = d4b;}
void ofApp::d5(ofx::JSONRPC::MethodArgs& args){args.result = d5b;}
void ofApp::d6(ofx::JSONRPC::MethodArgs& args){args.result = d6b;}
void ofApp::d7(ofx::JSONRPC::MethodArgs& args){args.result = d7b;}
void ofApp::d8(ofx::JSONRPC::MethodArgs& args){args.result = d8b;}
void ofApp::d9(ofx::JSONRPC::MethodArgs& args){args.result = d9b;}
void ofApp::d10(ofx::JSONRPC::MethodArgs& args){args.result = d10b;}
