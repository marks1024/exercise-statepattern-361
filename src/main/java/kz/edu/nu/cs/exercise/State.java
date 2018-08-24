package kz.edu.nu.cs.exercise;

public abstract class State {
    protected StateContext sc;
    protected boolean accept = false;

    abstract public void actionA();

    abstract public void actionB();

    public boolean isAccept() {
        return this.accept;
    }
}
