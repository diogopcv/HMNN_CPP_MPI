//
//  ltscell.cpp
//  cortex
//
//  Created by Diogo Porfirio de Castro Vieira on 27/11/11.
//  Copyright 2011 Universidade de Sao Paulo. All rights reserved.
//

#include "ltscell.h"  

ltscell::ltscell() : neuron() {
    numeq = 2;
    fbuf = new double[numeq];
    w = new double[numeq];
    waux = new double[numeq];
    ks = new double * [numeq]; 
    for (int i = 0; i < numeq; i++)
    	ks[i] = new double[4];         
    startKs(); 
    cap = 100.0, k = 1.0, vr = -56.0, vt = -42.0;
    setpar(0.03, 8.0, -50.0, 20.0);
	double w_[2] = {vr,0.0};
    setw0(w_);   
}    

ltscell::ltscell(double aArg, double bArg, double cArg, double dArg) : neuron() {
    numeq = 2;
    fbuf = new double[numeq];
    w = new double[numeq];
    waux = new double[numeq];
    ks = new double * [numeq]; 
    for (int i = 0; i < numeq; i++)
    	ks[i] = new double[4];         
    startKs(); 
    cap = 100.0, k = 1.0, vr = -56.0, vt = -42.0;
    setpar(aArg, bArg, cArg, dArg);
	double w_[2] = {vr,0.0};
    setw0(w_);      
}

void ltscell::fx(double inj, float time) {
    inj -=calcsyncurrent(time);
    fbuf[0] = (k * (waux[0] - vr) * (waux[0] - vt) - waux[1] + inj)/cap;
    fbuf[1] = a * (b * (waux[0] - vr) - waux[1]);
}

void ltscell::checkPeak(float time){
    if (w[0] >= 40.0) {
        w[0] = c;
        w[1] = w[1] + d;
        if (w[1] > 670)
        	w[1] = 670;        
	sendevent(time);
    }
}

void ltscell::setpar(double aArg, double bArg, double cArg, double dArg) {
    a = aArg;
    b = bArg;
    c = cArg;
    d = dArg;
}

void ltscell::setvrest(double vrest){
    vr = vrest;
	double w_[2] = {vrest,0.0};
    setw0(w_);
}

void ltscell::setvtresh(double vtresh){
    vt = vtresh;
}

void ltscell::setk(double k_){
    k = k_;
}

void ltscell::setcap(double cap_){
    cap = cap_;
}
