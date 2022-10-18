/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.faded.tp7;

/**
 *
 * @author faded
 */
public class Euro extends Currency{
    public Euro(){
        super("€", 978, "EUR");
    }
    
    @Override
    public double to_dollar_rate(){
        return 1. / 1.03;
    }
    
    @Override
    public double to_euro_rate(){
        return 1.;
    }
}
