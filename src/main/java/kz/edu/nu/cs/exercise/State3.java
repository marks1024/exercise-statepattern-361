package kz.edu.nu.cs.exercise;

public class State3 extends State {
    protected StateContext sc;
    protected boolean accept = true;
     public State3(StateContext stateContext) {
        sc = stateContext;
    }
     public void actionA() {
    }
     public void actionB() {
        sc.setCurrentState(sc.state2);
    }
     public boolean isAccept() {
        return this.accept;
    }
}
