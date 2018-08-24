package kz.edu.nu.cs.exercise;

public class State1 extends State {
    public State1(StateContext stateContext, boolean accept) {
        super(stateContext, accept);
    }

    @Override
    public void actionA() {
        this.sc.setCurrentState(this.sc.state2);
    }
}
