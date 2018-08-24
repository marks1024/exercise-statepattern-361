package kz.edu.nu.cs.exercise;

public class State3 extends State {
	
    protected boolean accept = true;

	public State3(StateContext stateContext) {
		// TODO Auto-generated constructor stub
		this.sc = stateContext;
	}

	public void actionA() {
    	this.sc.setCurrentState(sc.state3);   	
    }

    public void actionB() {
    	this.sc.setCurrentState(sc.state2);
    }

    public boolean isAccept() {
        return this.accept;
    }
}
