package com.sxt;

import java.util.Scanner;

public class hello {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("请输入一个三位数");
        int i = sc.nextInt();
        int a = i%10;
        int b = i/10 %10;
        int c = i/100 % 10;
        System.out.println(a);
        System.out.println(b);
        System.out.println(c);
    }
}
