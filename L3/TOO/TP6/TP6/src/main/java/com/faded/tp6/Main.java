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
        Map<Integer, Integer> input1 = new TreeMap<>();
        input1.put(2,5);
        input1.put(1,-3);
        input1.put(0, 8);
        Polynomial p1 = new Polynomial(input1);
        p1.eval_Horner();
    }
}
