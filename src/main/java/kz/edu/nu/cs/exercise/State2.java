package kz.edu.nu.cs.exercise;
public class State2 extends State {
	public State2(StateContext sc) {
	      this.sc = sc;
	      this.accept = false;
	}
    public void actionA() {
    	// go to 3
    	sc.setCurrentState(sc.state3); 
    }

    public void actionB() {
    	// go to 1
    	sc.setCurrentState(sc.state1); 
    }
}
