package kz.edu.nu.cs.exercise;
public class State3 extends State {
	public State3(StateContext sc) {
	      this.sc = sc;
	      this.accept = true;
	}
    public void actionA() {
    	//loop here
    }

    public void actionB() {
    	// go to 2
    	sc.setCurrentState(sc.state2); 
    }
}
