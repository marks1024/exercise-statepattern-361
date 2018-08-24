package exercise;

public class State1 extends State {

	public State1(StateContext stateContext) {
		this.sc = stateContext;

		// TODO Auto-generated constructor stub
	}

	public void actionA() 
	{
		this.sc.setCurrentState(this.sc.state2);
	}

	public void actionB() 
	{
		this.sc.setCurrentState(this.sc.state1);
	}

}
