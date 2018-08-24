package kz.edu.nu.cs.exercise;



public class State1 extends State {
    public State1(StateContext a1){
        this.sc = a1;
    }
    @Override
    public void actionA() {
        this.sc.setCurrentState(sc.state2);

    }
    public void actionB() {
        sc.setCurrentState(this);

    }

    @Override
    public boolean isAccept() {
        return false;
    }
}
