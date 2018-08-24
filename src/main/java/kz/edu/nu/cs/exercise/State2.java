package kz.edu.nu.cs.exercise;

public class State2 extends State {
    public State2(StateContext stateContext) {
        sc = stateContext;
        this.accept = false;
    }
    @Override
    public void actionA() {
        sc.setCurrentState(sc.state3);
    }
    @Override
    public void actionB() {
        sc.setCurrentState(sc.state1);
    }

    @Override
    public boolean isAccept() {
        return this.accept;
    }
}
