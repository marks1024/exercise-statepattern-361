package kz.edu.nu.cs.exercise;

public class State1 extends State{
	protected StateContext sc;
    protected boolean accept = false;
    
	public State1(StateContext stateContext) {
		this.sc = stateContext; 
	}
	public void actionA() {
		this.sc.setCurrentState(this.sc.getState2());
    }

    public void actionB() {
//    	no change of the state
    }

    public boolean isAccept() {
        return this.accept;
    }
}

