package kz.edu.nu.cs.exercise;

public class State2 extends State {

	public State2(StateContext stateContext) {
		// TODO Auto-generated constructor stub
		this.sc = stateContext;
	}

	public void actionA() {

		this.sc.setCurrentState(sc.state3);
	}

	public void actionB() {

		this.sc.setCurrentState(sc.state1);

	}

	public boolean inAcceptState() {

		return false;
	}

}
