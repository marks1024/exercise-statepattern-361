package kz.edu.nu.cs.exercise;

public class State1 extends State {
	
	State1 (StateContext s) {
		sc = s;
	}
	
	public void actionA() {
		sc.setCurrentState(sc.state2);
    }

    public void actionB() {
    	//sc.setCurrentState(sc.state1);
    }
}