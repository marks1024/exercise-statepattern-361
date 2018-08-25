package kz.edu.nu.cs.exercise;

public class State1 extends State {
    public State1(StateContext sc) {
        this.sc = sc;
    }

    @Override
    public void actionA() {
        this.sc.setCurrentState( this.sc.state2);

    }

    @Override
    public void actionB() {
    }

}
