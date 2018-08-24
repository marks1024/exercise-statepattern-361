package kz.nu.edu.cs.exercise;

public class State3 extends State {

  public State3(StateContext sc) {
    this.accept = true;
    this.sc = sc;
  }
  
  @Override
  public void actionA() {
    sc.setCurrentState(sc.state3);
  }
  
  @Override
  public void actionB() {
    sc.setCurrentState(sc.state2);
  }
}  
   
