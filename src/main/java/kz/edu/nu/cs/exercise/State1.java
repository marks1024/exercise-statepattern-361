package kz.edu.nu.cs.exercise;

public class State1 extends State {
	public State1(StateContext sc) {
		this.sc = sc;
		accept = false;
	}
    public void actionA() {
    	sc.setCurrentState(sc.state2);
    }
}
