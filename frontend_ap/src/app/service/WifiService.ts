import {Injectable} from '@angular/core';
import {HttpClient} from '@angular/common/http';

import {WifiNetwork} from "./WifiNetwork";
import {Observable} from "rxjs/index";

@Injectable()
export class WifiService {
  constructor(private http: HttpClient) {
  }

  getNetworks() : Observable<WifiNetwork[]> {
    return this.http.get<WifiNetwork[]>('api/scan/');
  }
}
