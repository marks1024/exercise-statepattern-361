package kz.edu.nu.cs.exercise;

public class State3 extends State {
    public State3 (StateContext sc) {
        this.sc = sc;
        this.accept = true;
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
