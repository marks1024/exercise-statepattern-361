package kz.edu.nu.cs.exercise;

public class State2 extends State {
	public State2(StateContext stateContext) {
		this.sc = stateContext;
	}
	
	public void actionA() {
    	sc.setCurrentState(sc.state3);
    }

    public void actionB() {
    	sc.setCurrentState(sc.state1);
    }
}
