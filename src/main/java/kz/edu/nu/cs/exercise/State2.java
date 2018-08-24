package kz.edu.nu.cs.exercise;

public class State2 extends State {
	
	State2 (StateContext s) {
		sc = s;
	}
	
	public void actionA() {
		sc.setCurrentState(sc.state3);
    }

    public void actionB() {
    	sc.setCurrentState(sc.state1);
    }
}