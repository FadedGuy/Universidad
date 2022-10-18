/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.faded.tp7;
/**
 *
 * @author faded
 */

interface Obsolete_currency{
    static final Currency Default_substitute = new Euro();
    
    default Currency substitute(){
        return Default_substitute;
    }
    
    default boolean still_active_(){
        return false;
    }
    
    abstract java.time.LocalDate substitution_date();
}

abstract public class Currency {
    final public String _common_symbol;
    final public Integer _iso_code;
    final public String _iso_symbol;
    
    protected Currency(String common_symbol, Integer iso_code, String iso_symbol){
        _common_symbol = common_symbol;
        _iso_code = iso_code;
        _iso_symbol = iso_symbol;
    }
    
    public double rate(final Currency currency){
        return 1. / currency.to_euro_rate();
    }
    
    public abstract double to_dollar_rate();
    
    public double convert_to_dollar(final double amount){
        return amount * to_dollar_rate();
    }
    
    public abstract double to_euro_rate();
    
    public double convert_to_euro(final double amount){
        return amount * to_euro_rate();
    }
    
}


