package de.zebrajaeger.esp8266.ledserver;

import com.fasterxml.jackson.annotation.JsonProperty;

public class CurrentNetwork {
    private String BSSID;
    private String password;

    public CurrentNetwork() {
    }

    public CurrentNetwork(String BSSID, String password) {
        this.BSSID = BSSID;
        this.password = password;
    }

    @JsonProperty("BSSID")
    public String getBSSID() {
        return BSSID;
    }

    public void setBSSID(String BSSID) {
        this.BSSID = BSSID;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }
}
