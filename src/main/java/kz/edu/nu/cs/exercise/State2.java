package kz.edu.nu.cs.exercise;

public class State2 extends State{
	protected StateContext sc;
    protected boolean accept;
    
	public State2(StateContext sccon) {
		this.sc = sccon;
		this.accept = false;
	}
	
	public void actionA() {
		sc.setCurrentState(sc.state3);
    }

    public void actionB() {
    	sc.setCurrentState(sc.state1);
    }

    public boolean isAccept() {
        return this.accept;
    }
}
