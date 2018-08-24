package kz.edu.nu.cs.exercise;

public abstract class State {
    protected StateContext sc;
    protected boolean accept;

    public State (StateContext stateContext, boolean accept){
        this.sc = stateContext;
        this.accept = accept;
    }

    public void actionA() {
    }

    public void actionB() {
    }

    public boolean isAccept() {
        return this.accept;
    }
}
