package kz.edu.nu.cs.exercise;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import org.junit.Before;
import org.junit.Test;

public class TestStatePattern {

    StateContext sc;

    @Before
    public void setUp() {
        sc = new StateContext();
    }
    
    /*
     * Test Sequence: A
     */
    @Test
    public void test_1() {
        sc.actionA();
        assertFalse("Test Sequence A", sc.inAcceptState());
    }

    /*
     * Test Sequence: AA
     */
    @Test
    public void test_2() {
        sc.actionA();
        sc.actionA();
        assertTrue("Test Sequence AA", sc.inAcceptState());
    }
    
    /*
     * Test Sequence: A (check state)
     */
    @Test
    public void test_3() {
        sc.actionA();
        assertTrue("Test Sequence: A (check state)", sc.getCurrentState().equals(sc.state2));
    }
    
    /*
     * Test Sequence: AAB (check state)
     */
    @Test
    public void test_4() {
        sc.actionA();
        sc.actionA();
        sc.actionB();
        assertTrue("Test Sequence: AAB (check state)", sc.getCurrentState().equals(sc.state2));
    }
    
    /*
     * Test Sequence: AABB (check state)
     */
    @Test
    public void test_5() {
        sc.actionA();
        sc.actionA();
        sc.actionB();
        sc.actionB();
        assertTrue("Test Sequence: AABB (check state)", sc.getCurrentState().equals(sc.state1));
    }
    
    /*
     * Test Sequence: AAA
     */
    @Test
    public void test_6() {
        sc.actionA();
        sc.actionA();
        sc.actionA();
        assertTrue("Test Sequence: AAA", sc.inAcceptState());
    }
}
