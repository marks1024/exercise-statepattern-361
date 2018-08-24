package kz.edu.nu.cs.exercise;

public class State1 extends State {

    public State1(StateContext stateContext) {
    	this.sc = stateContext;
    }
    
    public void actionA() {
    	sc.setCurrentState(sc.state2);
    }

    public void actionB() {
 
    }
}
