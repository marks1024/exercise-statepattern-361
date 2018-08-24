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
        currentState.actionA();
        // complete this method by
        // delegation to the current state
    }

    public void actionB() {
        currentState.actionB();

        // complete this method
        // delegate to the current state
    }

    public boolean inAcceptState() {
        return currentState.isAccept();
//        if (this.currentState == state3){
//            return true;
//        }
//        // complete this method and return correct value
//        // delegate to the current state
//        else return false;
    }

    public State getCurrentState() {
        return currentState;
    }

    public void setCurrentState(State currentState) {
        this.currentState = currentState;
    }

}
