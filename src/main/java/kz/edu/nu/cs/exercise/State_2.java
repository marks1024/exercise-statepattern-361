package kz.edu.nu.cs.exercise;

public class State_2 extends State  {
	
    public State_2(StateContext stateContextState) {
    	this.sc = stateContextState;
    	this.accept = false;
    }
	
	
    public void actionA() {
    	//
    	this.sc.setCurrentState(sc.state3);

    } 

    public void actionB() {
    	//turn to 
    	this.sc.setCurrentState(sc.state1);

    }
	
    
    public boolean isAccept() {
        return this.accept;
    }
}
