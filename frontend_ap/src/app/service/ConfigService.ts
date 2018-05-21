import {Injectable} from '@angular/core';
import {HttpClient} from '@angular/common/http';

import {WifiNetwork} from "./WifiNetwork";
import {Observable} from "rxjs/index";
import {CurrentNetwork} from "./CurrentNetwork";

@Injectable()
export class ConfigService {
  constructor(private http: HttpClient) {
  }

  getCurrentNetwork() : Observable<CurrentNetwork> {
    return this.http.get<CurrentNetwork>('api/config/network');
  }

  setCurrentNetwork(BSSID : String, password: String) : Observable<CurrentNetwork> {
    let cn : CurrentNetwork = <CurrentNetwork>{};
    cn.BSSID = BSSID;
    cn.password = password;
    return this.http.post<CurrentNetwork>('api/config/network', cn);
  }
}
