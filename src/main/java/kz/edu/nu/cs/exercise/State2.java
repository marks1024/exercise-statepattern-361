package kz.nu.edu.cs.exercise;

public class State2 extends State {

  public State2(StateContext sc) {
    this.accept = false;
    this.sc = sc;
  }
  
  @Override
  public void actionA() {
    sc.setCurrentState(sc.state3);
  }
  
  @Override
  public void actionB() {
    sc.setCurrentState(sc.state1);
  }
}  
   
