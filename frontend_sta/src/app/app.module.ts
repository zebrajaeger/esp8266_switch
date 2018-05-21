import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { HttpClientModule } from '@angular/common/http';

import {InputSwitchModule} from 'primeng/inputswitch';

import { AppComponent } from './app.component';
import {LedService} from "./service/LedService";

@NgModule({
  declarations: [
    AppComponent
  ],
  imports: [
    BrowserModule,
    HttpClientModule,
    FormsModule,

    InputSwitchModule
  ],
  providers: [
    LedService
  ],
  bootstrap: [AppComponent]
})
export class AppModule { }
