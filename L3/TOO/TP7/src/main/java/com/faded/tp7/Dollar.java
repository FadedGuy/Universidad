/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.faded.tp7;

/**
 *
 * @author faded
 */
public class Dollar extends Currency{
    public Dollar(){
        super("$", 840, "USD");
    }
    
    @Override
    public double to_dollar_rate(){
        return 1. ;
    }
    
    @Override
    public double to_euro_rate(){
        return 1. * 1.01;
    }
}
