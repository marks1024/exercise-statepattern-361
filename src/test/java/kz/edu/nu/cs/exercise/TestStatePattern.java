package kz.edu.nu.cs.exercise;

import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

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
        assertEquals("Test Sequence: A (check state)", sc.getCurrentState(), sc.state2);
    }

    /*
     * Test Sequence: AAB (check state)
     */
    @Test
    public void test_4() {
        sc.actionA();
        sc.actionA();
        sc.actionB();
        assertEquals("Test Sequence: AAB (check state)", sc.getCurrentState(), sc.state2);
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
        assertEquals("Test Sequence: AABB (check state)", sc.getCurrentState(), sc.state1);
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
