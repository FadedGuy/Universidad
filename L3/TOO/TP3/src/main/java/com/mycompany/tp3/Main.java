/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.tp3;

/**
 *
 * @author faded
 */
public class Main {
    public static void main(String[] args) {
        Yesterday yesterday = new Yesterday(9, 5, 2019);
        System.out.println(yesterday.before_yesterday());
        
        Yesterday yesterday1 = new Yesterday(27, 9, 2022);
        System.out.println(yesterday1.before_yesterday());
    }
}
