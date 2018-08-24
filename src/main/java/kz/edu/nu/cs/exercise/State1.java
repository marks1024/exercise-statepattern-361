package kz.edu.nu.cs.exercise;

public class State1 extends State {
    public State1(StateContext StateContext) {
        super(StateContext);
        this.accept = false;
    }
    @Override
    public void actionA() {
        this.sc.setCurrentState(this.sc.state2);

    }
    @Override
    public void actionB() {
        this.sc.setCurrentState(this.sc.state2);
    }
}
