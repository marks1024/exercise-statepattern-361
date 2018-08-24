package kz.edu.nu.cs.exercise;

public class State3 extends State {
    protected StateContext sc;
    protected boolean accept = true;

    public State3(StateContext val3){
        sc = val3;
    }

    public void actionA() {
        sc.setCurrentState(sc.state3);
    }

    public void actionB() {
        sc.setCurrentState(sc.state2);
    }

    public boolean isAccept() {
        return this.accept;
    }
}
