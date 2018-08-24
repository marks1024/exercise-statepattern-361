/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package kz.edu.nu.cs.exercise;

/**
 *
 * @author Abylay
 */
public class State1 extends State { 
    
    public State1(StateContext sc) {
        this.sc = sc;
        accept = false;
    }
    
    public void actionA() {
        sc.setCurrentState(sc.state2);
    }
    
    public void actionB() {
        sc.setCurrentState(sc.state1);
    }
    
}
