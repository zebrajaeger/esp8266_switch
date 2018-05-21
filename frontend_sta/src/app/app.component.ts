import {Component, OnInit} from '@angular/core';
import {LedService} from "./service/LedService";

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent implements OnInit {
  title = 'app';
  private _checked: boolean;

  constructor(private ledService: LedService) {
  }

  ngOnInit(): void {
    this.ledService.getLedState().subscribe(ledData => {
      this.checked = (ledData.state == 'true');
    });
  }

  get checked(): boolean {
    return this._checked;
  }

  set checked(value: boolean) {
    this.ledService.setLedState(value).subscribe(ledData => {
      this._checked = (ledData.state == 'true');
    });
  }
}
