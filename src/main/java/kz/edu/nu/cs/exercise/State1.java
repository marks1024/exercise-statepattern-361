package kz.edu.nu.cs.exercise;

public class State1 extends State {

	public State1(StateContext myStateContext) {
        this.sc = myStateContext;
        this.accept = false;
    }
	
	 public void actionA() {
	        this.sc.setCurrentState(this.sc.state2);
	 }

	 public void actionB() {
		 	this.sc.setCurrentState(this.sc.state1);
	 }

	 public boolean inAcceptState() {
	        
		 return this.accept;
	 }

}
