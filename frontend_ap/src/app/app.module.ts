import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { HttpClientModule } from '@angular/common/http';

import {AccordionModule} from 'primeng/accordion';
import {ButtonModule} from 'primeng/button';
import {DialogModule} from 'primeng/dialog';
import {PasswordModule} from 'primeng/password';

import { AppComponent } from './app.component';
import {WifiService} from "./service/WifiService";
import {BrowserAnimationsModule} from "@angular/platform-browser/animations";
import {ConfigService} from "./service/ConfigService";

@NgModule({
  declarations: [
    AppComponent
  ],
  imports: [
    BrowserModule,
    HttpClientModule,
    FormsModule,
    BrowserAnimationsModule,

    AccordionModule,
    ButtonModule,
    DialogModule,
    PasswordModule
  ],
  providers: [
    ConfigService,
    WifiService
  ],
  bootstrap: [AppComponent]
})
export class AppModule { }
