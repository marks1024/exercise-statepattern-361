package kz.edu.nu.cs.exercise;

public class State2 extends State{
	

	public State2(StateContext sContext) {
		super.sc = sContext;
	}
	
	@Override
	public void actionA() {
		super.sc.setCurrentState(super.sc.state3);
	}
	
	@Override
	public void actionB() {
		super.sc.setCurrentState(super.sc.state1);
	}
	
	@Override
	public boolean isAccept() {
		return false;
	}
}
