package kz.edu.nu.cs.exercise;

public class State1 extends State{
    public State1 (StateContext s){
        sc = s;
    }

    @Override
    public void actionA() {
        sc.setCurrentState(sc.state2);
    }
    @Override
    public void actionB() {
        sc.setCurrentState(sc.state1);
    }

}
