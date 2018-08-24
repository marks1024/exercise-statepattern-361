package kz.edu.nu.cs.exercise;

public class State3 extends State {

    public State3(StateContext sc){
        this.sc = sc;
        accept = true;
    }

    public void actionA() {
    }

    public void actionB() {
        sc.setCurrentState(sc.state2);
    }
}
