package kz.edu.nu.cs.exercise;

public class StateContext {
    final State state1 = new State1(this);
    final State state2 = new State2(this);
    final State state3 = new State3(this);

    private State currentState;

    public StateContext() {
        this.currentState = state1;
    }

    public void actionA() {
        // complete this method by
        // delegation to the current state
		
		switch (this.currentState) {
            case state1:  setCurrentState(state2);
                     break;
            case state2:  setCurrentState(state3);
                     break;
            case state3:  setCurrentState(state3);
			
            default: setCurrentState(state1);
                     break;
        }
		
    }

    public void actionB() {
        // complete this method
        // delegate to the current state
		
		switch (this.currentState) {
            case state1:  setCurrentState(state1);
                     break;
            case state2:  setCurrentState(state1);
                     break;
            case state3:  setCurrentState(state2);
			
            default: setCurrentState(state1);
                     break;
        }
    }

    public boolean inAcceptState() {
		if(getCurrentState() == state3){
			return true;
		} else
        // complete this method and return correct value
        // delegate to the current state
        return false;
    }

    public State getCurrentState() {
        return currentState;
    }

    public void setCurrentState(State currentState) {
        this.currentState = currentState;
    }

}
