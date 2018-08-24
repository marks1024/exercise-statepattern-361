package kz.edu.nu.cs.exercise;

public class State3 extends State {
	public State3(StateContext sContext) {
		super.sc = sContext;
	}
	
	@Override
	public void actionB() {
		super.sc.setCurrentState(super.sc.state2);
	}
	
	@Override
	public boolean isAccept() {
		return true;
	}
}
