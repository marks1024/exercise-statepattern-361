package kz.edu.nu.cs.exercise;

public class State1 extends State {

	protected boolean accept = false;
	
	public State1(StateContext stateContext) {
		// TODO Auto-generated constructor stub
		
		this.sc = stateContext;
	}

    public void actionA() {
    	this.sc.setCurrentState(sc.state2);   	
    }

    public void actionB() {
    	this.sc.setCurrentState(sc.state1);
    }

    public boolean isAccept() {
        return this.accept;
    }
	
	

}
