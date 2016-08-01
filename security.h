/*
 * Copyright (c) 2015 ARM Limited. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef __SECURITY_H__
#define __SECURITY_H__
 
#include <inttypes.h>
 
#define MBED_DOMAIN "3209484e-dee6-4d0b-807e-4a66fae754d1"
#define MBED_ENDPOINT_NAME "8a691a8a-3bc8-4164-a2b2-00a8e3a7f775"
 
const uint8_t SERVER_CERT[] = "-----BEGIN CERTIFICATE-----\r\n"
"MIIBmDCCAT6gAwIBAgIEVUCA0jAKBggqhkjOPQQDAjBLMQswCQYDVQQGEwJGSTEN\r\n"
"MAsGA1UEBwwET3VsdTEMMAoGA1UECgwDQVJNMQwwCgYDVQQLDANJb1QxETAPBgNV\r\n"
"BAMMCEFSTSBtYmVkMB4XDTE1MDQyOTA2NTc0OFoXDTE4MDQyOTA2NTc0OFowSzEL\r\n"
"MAkGA1UEBhMCRkkxDTALBgNVBAcMBE91bHUxDDAKBgNVBAoMA0FSTTEMMAoGA1UE\r\n"
"CwwDSW9UMREwDwYDVQQDDAhBUk0gbWJlZDBZMBMGByqGSM49AgEGCCqGSM49AwEH\r\n"
"A0IABLuAyLSk0mA3awgFR5mw2RHth47tRUO44q/RdzFZnLsAsd18Esxd5LCpcT9w\r\n"
"0tvNfBv4xJxGw0wcYrPDDb8/rjujEDAOMAwGA1UdEwQFMAMBAf8wCgYIKoZIzj0E\r\n"
"AwIDSAAwRQIhAPAonEAkwixlJiyYRQQWpXtkMZax+VlEiS201BG0PpAzAiBh2RsD\r\n"
"NxLKWwf4O7D6JasGBYf9+ZLwl0iaRjTjytO+Kw==\r\n"
"-----END CERTIFICATE-----\r\n";
 
const uint8_t CERT[] = "-----BEGIN CERTIFICATE-----\r\n"
"MIIBzzCCAXOgAwIBAgIEIyrV+zAMBggqhkjOPQQDAgUAMDkxCzAJBgNVBAYTAkZ\r\n"
"JMQwwCgYDVQQKDANBUk0xHDAaBgNVBAMME21iZWQtY29ubmVjdG9yLTIwMTYwHh\r\n"
"cNMTYwNzE4MDMxODA3WhcNMTYxMjMxMDYwMDAwWjCBoTFSMFAGA1UEAxNJMzIwO\r\n"
"TQ4NGUtZGVlNi00ZDBiLTgwN2UtNGE2NmZhZTc1NGQxLzhhNjkxYThhLTNiYzgt\r\n"
"NDE2NC1hMmIyLTAwYThlM2E3Zjc3NTEMMAoGA1UECxMDQVJNMRIwEAYDVQQKEwl\r\n"
"tYmVkIHVzZXIxDTALBgNVBAcTBE91bHUxDTALBgNVBAgTBE91bHUxCzAJBgNVBA\r\n"
"YTAkZJMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAE3flHeHXhxyaeIcrmiB4IF\r\n"
"GPQM4Cwek642sB1rk371F24EwEDDpARAu0qBMczEMZdnMkllG7BepnXwna68gxL\r\n"
"DjAMBggqhkjOPQQDAgUAA0gAMEUCIQC0cw/N2M/kzNhU2m3fBt4ySGpLgEmsgQS\r\n"
"J1ZjhygOQhwIgREbD7aJ7oYNShDVaR538X2fg5HTl6Et1gY8BLvRJJqo=\r\n"
"-----END CERTIFICATE-----\r\n";
 
const uint8_t KEY[] = "-----BEGIN PRIVATE KEY-----\r\n"
"MIGHAgEAMBMGByqGSM49AgEGCCqGSM49AwEHBG0wawIBAQQgMKBlUT0Em7HisBHe\r\n"
"s0e6xl0RZZvYqUHo7JmtjzGE9VahRANCAATd+Ud4deHHJp4hyuaIHggUY9AzgLB6\r\n"
"TrjawHWuTfvUXbgTAQMOkBEC7SoExzMQxl2cySWUbsF6mdfCdrryDEsO\r\n"
"-----END PRIVATE KEY-----\r\n";
 
#endif //__SECURITY_H__