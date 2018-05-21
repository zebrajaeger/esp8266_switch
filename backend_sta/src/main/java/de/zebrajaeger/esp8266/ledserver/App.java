package de.zebrajaeger.esp8266.ledserver;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
@RequestMapping("api")
public class App {

    public static void main(String[] args) {
        SpringApplication.run(App.class, args);
    }

    @Autowired
    private LedService ledService;

    @GetMapping("led")
    public ResponseEntity ledState() {
        LedData ledData = ledService.getLedData();
        return createResult(ledData);
    }

    private ResponseEntity createResult(LedData ledData) {
//        StringBuilder sb = new StringBuilder();
//        sb.append("{\"state\":");
//        sb.append(ledData.isState() ? "1" : "0");
//        sb.append("}");
//        return new ResponseEntity(sb.toString(), HttpStatus.OK);

        StringBuilder sb = new StringBuilder();
        sb.append("{\"state\":");
        sb.append(ledData.isState() ? "\"true\"" : "\"false\"");
        sb.append("}");
        return new ResponseEntity(sb.toString(), HttpStatus.OK);

//        return new ResponseEntity(ledData, HttpStatus.OK);
    }

    @GetMapping("led/{state}")
    public ResponseEntity ledState(@PathVariable("state") boolean value) {
        LedData ledData = ledService.getLedData();
        ledData.setState(value);
        return createResult(ledData);
    }
}
