package kz.edu.nu.cs.exercise;

public class State3 extends State {
    public State3(StateContext stateContext) {
        this.sc = stateContext;
        this.accept = true;
    }

    public void actionA() {
    }

    public void actionB() {
        sc.setCurrentState(sc.state2);
    }
}
