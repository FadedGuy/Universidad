/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Project/Maven2/JavaApp/src/main/java/${packagePath}/${mainClassName}.java to edit this template
 */

package com.mycompany.tp4;

/**
 *
 * @author faded
 */
public class Main {
    public static void main(String[] args) {
        LeapYear ly1 = new LeapYear();
        System.out.println("2020 is leap year? " + ly1.leap_year(2020));
        System.out.println("2027 is leap year? " + ly1.leap_year(2027));
        
        java.time.LocalDate ld1 = java.time.LocalDate.now();
        System.out.println("Is this year a leap year? " + ly1.leap_year(ld1));
        
        java.time.LocalDate ld2 = java.time.LocalDate.of(2028, 5, 5);
        System.out.println("2028 is leap year? " + ly1.leap_year(ld2));
    }
}
