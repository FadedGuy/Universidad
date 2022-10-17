/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.faded.tp6;
import java.util.*;

/**
 *
 * @author faded
 */
public class Polynomial {
    Map<Integer, Double> values = new TreeMap<>(Collections.reverseOrder());
    
    Polynomial(Map<Integer, Double> input){
        input.forEach((k,v) -> values.put(k, v));
    }
    
    public double eval_Horner(double x){
        double res = 0.0;
        boolean first = true;

        for(Map.Entry<Integer, Double> entry : values.entrySet()){
            if(first){
                res = entry.getValue();
                first = false;
            }
            else{
                res = (res*x) + entry.getValue();
            }
        }
        
        return res;
    }
    
    public double eval(double x){
        double res = 0.0;
        
        for(Map.Entry<Integer, Double> entry : values.entrySet()){
            res += Math.pow(x, entry.getKey()) * entry.getValue();
        }
        
        return res;
    }
}
