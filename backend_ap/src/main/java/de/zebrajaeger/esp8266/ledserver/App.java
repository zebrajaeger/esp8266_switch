package de.zebrajaeger.esp8266.ledserver;

import com.google.common.io.Resources;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.io.IOException;
import java.net.URL;
import java.nio.charset.StandardCharsets;

@SpringBootApplication
@RestController
@RequestMapping("api")
public class App {

    public static void main(String[] args) {
        SpringApplication.run(App.class, args);
    }

    private CurrentNetwork currentNetwork = new CurrentNetwork("9C:C7:A6:42:F9:DF", "foobar");

    @GetMapping("scan")
    public ResponseEntity scan() throws IOException {
        URL url = Resources.getResource("scan.json");
        String text = Resources.toString(url, StandardCharsets.UTF_8);
        return new ResponseEntity(text, HttpStatus.OK);
    }

    @GetMapping("config/network")
    public CurrentNetwork getNetwork() {
        return currentNetwork;
    }

    @PostMapping("config/network")
    public CurrentNetwork setNetwork(@RequestBody CurrentNetwork value) {
        currentNetwork = value;
        return currentNetwork;
    }
}
