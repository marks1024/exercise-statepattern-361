package kz.edu.nu.cs.exercise;

public class State3 extends State {
	protected StateContext sc;
    protected boolean accept = true;
    
    public State3(StateContext sc) {
    	this.sc = sc;
    }

    public void actionA() {
    	this.sc.setCurrentState(this.sc.getState3());
    }

    public void actionB() {
    	this.sc.setCurrentState(this.sc.getState2());
    }

    public boolean isAccept() {
        return this.accept;
    }
}
