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
        if (this.currentState == state1)
            this.currentState = state2;
        else if (this.currentState == state2)
            this.currentState = state3;
        else if (this.currentState == state3)
            this.currentState = state3;
        // complete this method by
        // delegation to the current state
    }

    public void actionB() {
        if (this.currentState == state2)
            this.currentState = state1;
        else if (this.currentState == state3)
            this.currentState = state2;
        else if (this.currentState == state1)
            this.currentState = state1;
        // complete this method
        // delegate to the current state
    }

    public boolean inAcceptState() {
        if (this.currentState == state3){
            return true;
        }else {
        // complete this method and return correct value
        // delegate to the current state
        return false;
        }
    }

    public State getCurrentState() {
        return currentState;
    }

    public void setCurrentState(State currentState) {
        this.currentState = currentState;
    }

    private static class State1 extends State {

        public State1(StateContext aThis) {
        }
    }

    private static class State2 extends State {

        public State2(StateContext aThis) {
        }
    }

    private static class State3 extends State {

        public State3(StateContext aThis) {
        }
    }



}
