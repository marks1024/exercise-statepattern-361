package kz.edu.nu.cs.exercise;

public class State3 extends State {
    public State3 (StateContext s){
        sc = s;
        accept = true;
    }

    @Override
    public void actionA() {
        sc.setCurrentState(sc.state3);
    }
    @Override
    public void actionB() {
        sc.setCurrentState(sc.state2);
    }
}
