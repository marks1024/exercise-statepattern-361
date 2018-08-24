package kz.edu.nu.cs.exercise;

public class State_1 extends State  {
	
	
    public State_1(StateContext stateContextState) {
    	this.sc = stateContextState;
    	this.accept = false;
    }
	
	
    public void actionA() {
    	//turn to state2
    	this.sc.setCurrentState(sc.state2);
    }

    public void actionB() {
    	//turn to state1, itself
    	this.sc.setCurrentState(sc.state1);
    }

    public boolean isAccept() {
        return this.accept;
    }
	
}
 