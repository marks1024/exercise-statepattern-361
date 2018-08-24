package kz.edu.nu.cs.exercise;

public class State3 extends State {
	
	State3 (StateContext s) {
		sc = s;
		accept = true;
	}
	
	public void actionA() {
		//sc.setCurrentState(sc.state3);
    }

    public void actionB() {
    	sc.setCurrentState(sc.state2);
    }
}