package kz.edu.nu.cs.exercise;

public class State1 extends State {
	
	public State1(StateContext sContext) {
		super.sc = sContext;
	}
	
	@Override
	public void actionA() {
		super.sc.setCurrentState(super.sc.state2);
	}
	
	@Override
	public boolean isAccept() {
		return false;
	}
}
