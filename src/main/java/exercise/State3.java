package exercise;

public class State3 extends State {

	public State3(StateContext stateContext) {
		// TODO Auto-generated constructor stub
		this.accept=true;
		this.sc = stateContext;
		// TODO Auto-generated constructor stub
	}

	public void actionA() 
	{
		this.sc.setCurrentState(this.sc.state3);
	}

	public void actionB() 
	{
		this.sc.setCurrentState(this.sc.state2);
	}

}
