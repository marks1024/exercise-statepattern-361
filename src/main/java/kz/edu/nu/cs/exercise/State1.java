package kz.edu.nu.cs.exercise;

public class State1 extends State {
    State1(StateContext sc) {
        this.sc = sc;
    }
    @Override
    public void actionA() {
        sc.setCurrentState(sc.state2);
    }

    @Override
    public void actionB() {
        sc.setCurrentState(sc.state1);
    }

    @Override
    public boolean isAccept() {
        return false;
    }
}
