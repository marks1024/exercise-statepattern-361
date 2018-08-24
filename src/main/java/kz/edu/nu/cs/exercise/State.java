package kz.edu.nu.cs.exercise;

public abstract class State {
    protected StateContext sc;
    protected boolean accept = false;

    public State(StateContext StateContext) {
        this.sc = StateContext;
    }

    public void actionA() {
    }

    public void actionB() {
    }

    public boolean isAccept() {
        return this.accept;
    }
}
