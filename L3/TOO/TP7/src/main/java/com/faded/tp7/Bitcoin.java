/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.faded.tp7;

/**
 *
 * @author faded
 */
public class Bitcoin extends Crypto_currency{
    Bitcoin(){
        super("₿", 0,"XBT");
    }
    
    @Override
    public double to_dollar_rate(){
        return 1. * 19580.90;
    }
    
    @Override
    public double to_euro_rate(){
        return 1. * 19866.29;
    }
}
