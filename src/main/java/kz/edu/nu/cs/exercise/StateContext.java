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
        if(this.currentState == state1) {
            this.currentState = state2;
        } else if(this.currentState == state2) {
            this.currentState = state3;
        } else if(this.currentState == state3) {
            this.currentState = state3;
        }
    }

    public void actionB() {
        // complete this method
        // delegate to the current state
        if(this.currentState == state1) {
            this.currentState = state1;
        } else if(this.currentState == state2) {
            this.currentState = state1;
        }
        if(this.currentState == state3) {
            this.currentState = state2;
        }
    }

    public boolean inAcceptState() {
        // complete this method and return correct value
        // delegate to the current state
        if((this.currentState == state3)){ 
            return true;
        }        
        return false;
    }

    public State getCurrentState() {
        return currentState;
    }

    public void setCurrentState(State currentState) {
        this.currentState = currentState;
    }

}