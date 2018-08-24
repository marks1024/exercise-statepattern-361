package kz.edu.nu.cs.exercise;

public class Test {

	public static void main ( String [] args ) {
		StateContext sc = new StateContext ();
		sc . actionA ();
		sc . actionA ();
//		sc . actionB ();
		// Is machine in an accept state
		// after receiving AAB
		System.out.println(sc.inAcceptState());
//		sc . inAcceptState ();
	}

}
