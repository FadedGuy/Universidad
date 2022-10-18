/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.faded.tp7;

/**
 *
 * @author faded
 */
public class Lats extends Currency implements Obsolete_currency {
    private static final java.time.LocalDate _substitution_date = java.time.LocalDate.of(2014, 1, 1);
    
    public Lats(){
        super("Ls", 428, "LVL");
    }
    
    @Override
    public double to_dollar_rate(){
        final Currency substitute = substitute();
        return rate(this) * substitute.to_dollar_rate();
    }
    
    @Override
    public double to_euro_rate(){
        return 1. * 0.702804;
    }
    
    @Override
    public java.time.LocalDate substitution_date(){
        return _substitution_date;
    }
}
