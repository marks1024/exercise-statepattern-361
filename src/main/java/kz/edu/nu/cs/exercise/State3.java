package kz.edu.nu.cs.exercise;

public class State3 extends State {
    public State3(StateContext a3){
        this.sc = a3;
    }
    @Override
    public void actionA() {
        sc.setCurrentState(this);

    }
    public void actionB() {
        this.sc.setCurrentState(sc.state2);

    }

    @Override
    public boolean isAccept() {
        return true;
    }
}
