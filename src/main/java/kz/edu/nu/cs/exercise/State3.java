package kz.edu.nu.cs.exercise;

public class State3 extends State {
    State3(StateContext sc) {
        this.sc = sc;
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
        return true;
    }
}
