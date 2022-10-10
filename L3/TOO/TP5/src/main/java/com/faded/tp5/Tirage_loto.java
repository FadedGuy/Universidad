/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.faded.tp5;

/**
 *
 * @author faded
 */
public class Tirage_loto {
    private final Integer _n_borne_max = 48;
    private java.util.ArrayList<Integer> _res_tirage = new java.util.ArrayList<>();
    
    public void afficher(){
        for(int i = 0; i < _n_borne_max; i++){
            if((i % 6) ==  0){
                System.out.print("\n");
            }
            System.out.print(" " + _res_tirage.get(i));
        }
    }
    
    public void tirage(){
        for(int i = 0; i < _n_borne_max; i++){
            _res_tirage.add(_tirage_num());
        }
    }
    
    private int _tirage_num(){
        int num_tir = (int)(Math.random() * _n_borne_max) + 1;
        
        if(!_res_tirage.contains(num_tir)){
            return num_tir;
        }
        
        return _tirage_num();
    }
}
