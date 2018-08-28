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
    	if (currentState == state1) {
    		currentState = state2;
    	} else 
    		if(currentState == state2) {
        		currentState = state3;
        } else 
        	if(currentState == state3) {
    		currentState = state3;
        	}
        }


    public void actionB() {
    	if (currentState == state1) {
    		currentState = state1;
    	} else 
    		if(currentState == state2) {
        		currentState = state1;
        } else 
        	if(currentState == state3) {
    		currentState = state2;
        	}
    }

    public boolean inAcceptState() {
        if (currentState == state3)
        return true; 
        else
        return false;
    }

    public State getCurrentState() {
        return currentState;
    }

    public void setCurrentState(State currentState) {
        this.currentState = currentState;
    }

}
