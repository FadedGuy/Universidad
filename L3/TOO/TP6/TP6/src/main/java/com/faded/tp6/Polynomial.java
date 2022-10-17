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
    Map<Integer, Integer> values = new TreeMap<>(Collections.reverseOrder());
    
    Polynomial(Map<Integer, Integer> input){
        input.forEach((k,v) -> values.put(k, v));
    }
    
    public double eval_Horner(){
        double coef;
        double res = values.get(values.size()-1);
        
        for(Integer i = values.size()-2; i >= 0; i--){
            res = res
        }
        
        System.out.println(res);
        
        
        return 0.0;
    }
}
