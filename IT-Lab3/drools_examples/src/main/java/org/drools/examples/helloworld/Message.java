package org.drools.examples.helloworld;

public class Message {
    public static final int HELLO = 0;
    public static final int GOODBYE = 1;
    public static final int GOOD_MORNING = 2;

    private int status;
    private String message;

    public Message() {
    }

    public String getMessage() {
        return this.message;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    public int getStatus() {
        return this.status;
    }

    public void setStatus(int status) {
        this.status = status;
    }
}
