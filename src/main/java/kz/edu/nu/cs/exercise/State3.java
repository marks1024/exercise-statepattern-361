package kz.edu.nu.cs.exercise;

public class State3 extends State {

	protected boolean accept = true;
	
	public State3(StateContext sc) {
		this.sc = sc;
	}
	
	public void actionA() {
		sc.setCurrentState(sc.getCurrentState());
	}

	public void actionB() {
		sc.setCurrentState(sc.state2);
	}

	public boolean isAccept() {
		return accept;
	}

}