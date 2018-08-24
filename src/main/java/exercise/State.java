package exercise;

public abstract class State {
    protected StateContext sc;
    protected boolean accept = false;

    public void actionA() 
    {
    }

    public void actionB() 
    {
    }

    public boolean isAccept() 
    {
        return this.accept;
    }
    
}
