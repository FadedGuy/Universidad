/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.faded.tp7;

/**
 *
 * @author faded
 */
public class Moroccan_Dirham extends Currency{
    public Moroccan_Dirham(){
        super("د. م", 504, "MAD");
    }
    
    @Override
    public double to_dollar_rate(){
        return 1. * 0.092;
    }
    
    @Override
    public double to_euro_rate(){
        return 1. * 0.093;
    }
}
