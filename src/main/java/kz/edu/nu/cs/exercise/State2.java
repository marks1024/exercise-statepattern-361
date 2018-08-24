package kz.edu.nu.cs.exercise;

public class State2 extends State {
    public State2(StateContext stateContext) { this.sc = stateContext; }

    @Override
    public void actionA() { sc.setCurrentState(sc.state3); }

    @Override
    public void actionB() { sc.setCurrentState(sc.state1); }
}
