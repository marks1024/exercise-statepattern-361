package kz.edu.nu.cs.exercise;

public class State1 extends State {
    public State state1;
	public State1(StateContext stateContext) {
		stateContext.setCurrentState(state1);
		
	}
	
}
