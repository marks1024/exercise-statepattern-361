package kz.edu.nu.cs.exercise;

public class State2 extends State{
	
    public State state2;
	public State2(StateContext stateContext) {
		stateContext.setCurrentState(state2);
	}
	
}
