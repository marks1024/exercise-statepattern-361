package kz.edu.nu.cs.exercise;

public class StateContext {

    public final State state1 = new State1(this);
    public final State state2 = new State2(this);
    public final State state3 = new State3(this);

    private State currentState;

    public StateContext() {

        this.currentState = state1;
    }

    public void actionA() {
        this.getCurrentState().actionA();
    }

    public void actionB() {
        this.getCurrentState().actionB();

    }

    public boolean inAcceptState() {

        return this.getCurrentState().isAccept();

    }

    public State getCurrentState() {

        return currentState;
    }

    public void setCurrentState(State currentState) {
        this.currentState = currentState;
    }

}
