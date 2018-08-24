package kz.edu.nu.cs.exercise;

public class State3 extends State {
    public State3(StateContext StateContext) {
        super(StateContext);
        this.accept = true;
    }
    @Override
    public void actionA() {
        this.sc.setCurrentState(this.sc.state3);
    }
    @Override
    public void actionB() {
        this.sc.setCurrentState(this.sc.state2);
    }
}
