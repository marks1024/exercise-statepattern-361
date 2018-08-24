package kz.edu.nu.cs.exercise;

public class State3 extends State{
	protected StateContext sc;
    protected boolean accept;
    
	public State3(StateContext sccon) {
		this.sc = sccon;
		this.accept = true;
	}
	
	public void actionA() {
		sc.setCurrentState(sc.state3);
    }

    public void actionB() {
    	sc.setCurrentState(sc.state2);
    }

    public boolean isAccept() {
        return this.accept;
    }
}
