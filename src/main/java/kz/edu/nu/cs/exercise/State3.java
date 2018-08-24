package kz.edu.nu.cs.exercise;

public class State3 extends State {

	public State3(StateContext stateContext) {
		sc = stateContext;
		this.accept = true;
	}

    public void actionA() {
    	sc.setCurrentState(sc.state3);
        // complete this method by
        // delegation to the current state
    }

    public void actionB() {
    	sc.setCurrentState(sc.state2);
        // complete this method
        // delegate to the current state
    }

    public boolean inAcceptState() {
    	return this.accept;
        // complete this method and return correct value
        // delegate to the current state
    }

}
