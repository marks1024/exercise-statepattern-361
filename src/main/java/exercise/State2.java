package exercise;

public class State2 extends State {

	public State2(StateContext stateContext) {
		this.sc = stateContext;
		// TODO Auto-generated constructor stub
	}

	public void actionA() 
	{
		this.sc.setCurrentState(this.sc.state3);
	}

	public void actionB() 
	{
		this.sc.setCurrentState(this.sc.state1);
	}
}
