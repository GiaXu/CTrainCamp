package com.practice.gui;

public final class WindowStates
{
    public enum State{
        STATE_LOGIN,
        STATE_SIGNUP,
        STATE_WORKING,
        STATE_QUIT
    }

    public static State state = State.STATE_LOGIN;
}
