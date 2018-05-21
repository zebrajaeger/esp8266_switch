import {Component, OnInit, ViewEncapsulation} from '@angular/core';
import {WifiService} from "./service/WifiService";
import {WifiNetwork} from "./service/WifiNetwork";
import {ConfigService} from "./service/ConfigService";

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css'],
  encapsulation: ViewEncapsulation.None
})
export class AppComponent implements OnInit {

  networks: Array<WifiNetwork>;
  selectedBSSID: String;
  password: String;

  passwordDialogVisible: boolean;
  tempPassword: String;

  constructor(private wifiService: WifiService, private configService: ConfigService) {
  }

  ngOnInit(): void {
    this.passwordDialogVisible = false;
    this.wifiService.getNetworks().subscribe(networks => {
      this.networks = networks;

      this.configService.getCurrentNetwork().subscribe(currentNetwork => {
        this.select(currentNetwork.BSSID, currentNetwork.password);
      });
    });
  }

  select(bssid: String, password: String): boolean {
    for (let network of this.networks) {
      if (network.BSSID == bssid) {
        this.selectedBSSID = bssid;
        this.password = password;
        return true;
      }
    }
    return false;
  }

  onChooseNetwork(index: number) {
    this.selectedBSSID = this.networks[index].BSSID;
    this.passwordDialogVisible = true;
  }


  onPasswordDialogOk() {
    this.passwordDialogVisible = false;
    this.configService.setCurrentNetwork(this.selectedBSSID, this.tempPassword).subscribe( currentNetwork => {
      this.select(currentNetwork.BSSID, currentNetwork.password);
    });
    this.tempPassword = "";
  }

  onPasswordDialogCancel() {
    this.passwordDialogVisible = false;
    this.selectedBSSID = null;
  }
}
