package kz.edu.nu.cs.exercise;

public class State1 extends State{
	protected StateContext sc;
    protected boolean accept = false;

    public State1(StateContext stateContext) {
    	this.sc = stateContext;
	}

	public void actionA() {
    	sc.setCurrentState(sc.state2);
    }

    public void actionB() {
    	sc.setCurrentState(sc.state1);
    }

    public boolean isAccept() {
        return this.accept;
    }
}
