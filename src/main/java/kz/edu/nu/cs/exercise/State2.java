package kz.edu.nu.cs.exercise;

public class State2 extends State {
	protected StateContext sc;
    protected boolean accept = false;
	public State2(StateContext sc){
		this.sc = sc;
	}
	

    public void actionA() {
    	this.sc.setCurrentState(this.sc.state3);
    }

    public void actionB() {
    	this.sc.setCurrentState(this.sc.state1);
    }

    public boolean isAccept() {
        return this.accept;
    }
}
