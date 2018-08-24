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
public class State3 extends State {
    StateContext stateContext;
    
    public State3(StateContext sc) {
        this.sc = sc;
        accept = true;
    }
    
    public void actionA() {
        sc.setCurrentState(sc.state3);
    }
    
    public void actionB() {
        sc.setCurrentState(sc.state2);
    }
}
