package kz.edu.nu.cs.exercise;

public class State1 extends State {
	protected StateContext sc;
    protected boolean accept = false;
	public State1(StateContext sc){
		this.sc = sc;
	}
	

    public void actionA() {
    	this.sc.setCurrentState(this.sc.state2);
    }

    public void actionB() {
    	this.sc.setCurrentState(this.sc.state1);
    }

    public boolean isAccept() {
        return this.accept;
    }
}
