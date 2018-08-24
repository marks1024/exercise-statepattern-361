package kz.edu.nu.cs.exercise;

public class State2 extends State {

	public State2(StateContext myStateContext) {
        this.sc = myStateContext;
        this.accept = false;
    }
	
	 public void actionA() {
	        this.sc.setCurrentState(this.sc.state3);
	 }

	 public void actionB() {
		 	this.sc.setCurrentState(this.sc.state1);
	 }

	 public boolean inAcceptState() {
	        
		 return this.accept;
	 }

}
