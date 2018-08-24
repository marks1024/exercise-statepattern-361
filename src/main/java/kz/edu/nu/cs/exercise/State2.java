package kz.edu.nu.cs.exercise;

public class State2 extends State {
    public State2(StateContext StateContext) {
        super(StateContext);
        this.accept = false;
    }
    @Override
    public void actionA() {
        this.sc.setCurrentState(this.sc.state3);
    }
    @Override
    public void actionB() {
        this.sc.setCurrentState(sc.state1);
    }
}

