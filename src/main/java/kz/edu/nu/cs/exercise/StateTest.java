package kz.edu.nu.cs.exercise;

public class StateTest {
	public static void main(String[] args) {
		StateContext sc = new StateContext();
		
		sc.actionA();
		sc.actionA();
		sc.actionB();
		
//		Boolean b =
		sc.inAcceptState();
//		System.out.println(b);
	}
}
