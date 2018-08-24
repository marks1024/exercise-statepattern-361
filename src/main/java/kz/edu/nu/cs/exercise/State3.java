package kz.edu.nu.cs.exercise;

public class State3 extends State {
    public State3(StateContext stateContext) {
        sc = stateContext;
        this.accept = true;
    }
    @Override
    public void actionA() {
        sc.setCurrentState(sc.state3);
    }
    @Override
    public void actionB() {
        sc.setCurrentState(sc.state2);
    }

    @Override
    public boolean isAccept() {
        return this.accept;
    }
}
