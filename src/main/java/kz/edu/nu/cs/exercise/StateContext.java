package kz.edu.nu.cs.exercise;

public class StateContext {
    final State state1 = new State1(this);
    final State state2 = new State2(this);
    final State state3 = new State3(this);

    private State currentState;

    public StateContext() {
        this.currentState = state1;
    }

    public void actionA() {
        // complete this method by
        // delegation to the current state
    	if (this.getCurrentState().equals(state1)) {
    		setCurrentState(state2);
//    		System.out.println("The state is 2 now");
    	} else {
    		setCurrentState(state3);
//    		System.out.println("The state is 3 now");
    	}
    	
    }

    public void actionB() {
        // complete this method
        // delegate to the current state
    	if (this.getCurrentState().equals(state3)) {
    		setCurrentState(state2);
//    		System.out.println("The state is 2 now");
    	} else {
    		setCurrentState(state1);
//    		System.out.println("The state is 1 now");
    	}

    }

    public boolean inAcceptState() {
        // complete this method and return correct value
        // delegate to the current state
    	if (this.getCurrentState().equals(state3)) {
    		return true;
    	} else {
    		return false;
    	}	
    }

    public State getCurrentState() {
        return currentState;
    }

    public void setCurrentState(State currentState) {
        this.currentState = currentState;
    }

}
