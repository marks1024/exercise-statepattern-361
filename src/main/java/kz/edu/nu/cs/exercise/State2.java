package kz.edu.nu.cs.exercise;

public class State2 extends State {
    
    protected StateContext sc;
    protected boolean accept = false;
    
    public State2(StateContext sc) {
        this.sc = sc;
    }
    
    @Override
    public void actionA() {
        sc.setCurrentState(sc.state3);
    }
    
    @Override
    public void actionB() {
        sc.setCurrentState(sc.state1);
    }
    
    @Override
    public boolean isAccept() {
        return accept;
    }
}
