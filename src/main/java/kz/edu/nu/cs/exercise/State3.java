package kz.edu.nu.cs.exercise;

public class State3 extends State {
    public State3(StateContext sc) {
        this.sc = sc;
        accept = true;
    }


    @Override
    public void actionA() {
    }

    @Override
    public void actionB() {
        this.sc.setCurrentState( this.sc.state2);
    }

}
