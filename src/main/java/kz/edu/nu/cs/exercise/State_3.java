package kz.edu.nu.cs.exercise;

public class State_3 extends State  {
	
    public State_3(StateContext stateContextState) {
    	this.sc = stateContextState;
    	this.accept = true;
    }
	
    public void actionA() {
    	this.sc.setCurrentState(sc.state3);
    }

    public void actionB() {
    	this.sc.setCurrentState(sc.state2);    	
    } 
    
    public boolean isAccept() {
        return this.accept;
    }
    
    
}
