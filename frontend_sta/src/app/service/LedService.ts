import {Injectable} from '@angular/core';
import {HttpClient} from '@angular/common/http';

import {LedData} from "./LedData";
import {Observable} from "rxjs/index";

@Injectable()
export class LedService {
  constructor(private http: HttpClient) {
  }

  getLedState() : Observable<LedData> {
    return this.http.get<LedData>('api/led/');
  }

  setLedState(value: boolean) : Observable<LedData> {
    return this.http.get<LedData>('api/led/' + value);
  }
}
