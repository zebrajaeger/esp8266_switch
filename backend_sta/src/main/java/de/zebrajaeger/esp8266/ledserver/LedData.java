package de.zebrajaeger.esp8266.ledserver;

public class LedData {
    private boolean state;

    public LedData(boolean state) {
        this.state = state;
    }

    public boolean isState() {
        return state;
    }

    public void setState(boolean state) {
        this.state = state;
    }
}
