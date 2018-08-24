package kz.edu.nu.cs.exercise;

public class State3 extends State {

	public State3(StateContext myStateContext) {
        this.sc = myStateContext;
        this.accept = true;
    }
	
	 public void actionA() {
	        this.sc.setCurrentState(this.sc.state3);
	 }

	 public void actionB() {
		 	this.sc.setCurrentState(this.sc.state2);
	 }

	 public boolean inAcceptState() {
	        
		 return this.accept;
	 }

}
