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
        this.currentState.actionA()
    }

    public void actionB() {
      this.currentState.actionB()

    }

    public boolean inAcceptState() {
        this.currentState.isAccept();
    }

    public State getCurrentState() {
        return currentState;
    }

    public void setCurrentState(State currentState) {
        this.currentState = currentState;
    }

    public State getState1(){
      return this.state1;
    }
    public State getState2(){
      return this.state2;
    }
    public State getState3(){
      return this.state3;
    }

}
