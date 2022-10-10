/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.tp4;

/**
 *
 * @author faded
 */
public class LeapYear {
    public boolean leap_year(int annee){
        return (((annee % 4 == 0) && (annee % 100 != 0)) || (annee % 400 == 0));
    }
    
    public boolean leap_year(java.time.LocalDate time){
        return leap_year(time.getYear());
    }
}
