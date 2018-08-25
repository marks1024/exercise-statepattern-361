package kz.edu.nu.cs.exercise;

public class State2 extends State {
    public State2(StateContext sc) {
        this.sc = sc;
    }
    @Override
    public void actionA() {
        this.sc.setCurrentState( this.sc.state3);
    }

    @Override
    public void actionB() {
        this.sc.setCurrentState( this.sc.state1);
    }

}
