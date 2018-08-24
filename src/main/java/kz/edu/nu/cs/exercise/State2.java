package kz.edu.nu.cs.exercise;

public class State2 extends State {
    
    public State2(StateContext stateContext) {
		sc = stateContext;
		this.accept = false;
	}

    public void actionA() {
    	sc.setCurrentState(sc.state3);
        // complete this method by
        // delegation to the current state
    }

    public void actionB() {
    	sc.setCurrentState(sc.state1);
        // complete this method
        // delegate to the current state
    }

    public boolean inAcceptState() {
    	return this.accept;
        // complete this method and return correct value
        // delegate to the current state
    }
}
