package de.zebrajaeger.esp8266.ledserver;

import org.springframework.stereotype.Service;

@Service
public class LedServiceImpl implements LedService{
    private LedData ledData = new LedData(false);

    @Override
    public LedData getLedData() {
        return ledData;
    }
}
