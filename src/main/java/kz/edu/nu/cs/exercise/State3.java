package kz.edu.nu.cs.exercise;

public class State3 extends State {
    public State3(StateContext stateContext, boolean accept) {
        super(stateContext, accept);
    }

    @Override
    public void actionB() {
        this.sc.setCurrentState(this.sc.state2);
    }
}
