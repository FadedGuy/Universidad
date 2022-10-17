/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Project/Maven2/JavaApp/src/main/java/${packagePath}/${mainClassName}.java to edit this template
 */

package com.faded.tp6;
import java.util.*;

/**
 *
 * @author faded
 */
public class Main {

    public static void main(String[] args) {
        Map<Integer, Double> input1 = new TreeMap<>();
        input1.put(2,5.0);
        input1.put(1,-3.0);
        input1.put(0, 8.0);
        Polynomial p1 = new Polynomial(input1);
        System.out.println("eval:" + p1.eval(2.0));
        System.out.println("eval Horner: " + p1.eval_Horner(2.0));
        
        Map<Integer, Double> input2 = new TreeMap<>();
        input2.put(10, -12.0);
        input2.put(39, 8.0);
        Polynomial p2 = new Polynomial(input2);
        System.out.println("eval:" + p2.eval(1));
        System.out.println("eval Horner: " + p2.eval_Horner(1));
    }
}
