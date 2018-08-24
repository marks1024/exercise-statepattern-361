package kz.nu.edu.cs.exercise;

public class State1 extends State {

  public State1(StateContext sc) {
    this.accept = false;
    this.sc = sc;
  }
  
  @Override
  public void actionA() {
    sc.setCurrentState(sc.state2);
  }
  
  @Override
  public void actionB() {
    sc.setCurrentState(sc.state1);
  }
}  
   
