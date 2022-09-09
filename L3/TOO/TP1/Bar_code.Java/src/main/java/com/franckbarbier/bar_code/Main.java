package com.franckbarbier.bar_code;

public class Main {

    public static void main(String[] args) {
        Bar_code bar_code = new Bar_code("5010356823357");
        System.out.println(bar_code.toString() + ", correct? " + bar_code.correct);
        Bar_code bar_code_ = new Bar_code("5010356҉23357");
        System.out.println(bar_code_.toString() + ", correct? " + bar_code.correct);
    }
}
