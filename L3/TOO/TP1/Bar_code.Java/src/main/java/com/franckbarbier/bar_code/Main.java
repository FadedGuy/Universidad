package com.franckbarbier.bar_code;

public class Main {

    public static void main(String[] args) {
        Bar_code bar_code = new Bar_code("5010356823357");
        System.out.println(bar_code.toString() + ", correct? " + bar_code.correct);
        Bar_code bar_code1 = new Bar_code("2109876543216");
        System.out.println(bar_code1.toString() + ", correct? " + bar_code1.correct);
        Bar_code bar_code__ = new Bar_code("5010356҉23357");
        System.out.println(bar_code__.toString() + ", correct? " + bar_code.correct);
    }
}
