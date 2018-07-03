## THIS MODULE IS CURRENTLY UNDER DEVELOPMENT
---

---
# README
# LoRaWAN detector

## Description
This detector serves for LoRaWAN monitoring air time of individual sensors. The detector can decode payload based on Network Sesion Key and Application Sesion Key. 

The input of this detector is a fields contain size payload SIZE, spreding factor SF, band width BAD_WIDTH, code rate CODE_RATE, time stamp record TIMESTAMP and  payload from message PHY_PAYLOAD. This values are captured from LoRaWAN packet.

## Interfaces
- Input: One UniRec interface
  - Template must contain fields SIZE, SF, BAD_WIDTH, CODE_RATE, TIMESTAMP and  PHY_PAYLOAD.
- Output: One UniRec interface
  - Optional fields NWK_SKEY and APP_SKEY, which are enabling ABP decryption of the LoRaWAN payload.
  
## Parameters
### Module specific parameters
- `-d  --dutycycle <double>`           Defines time between packet subsequence starts, default value duty cycle is 0.10%.
- `-e  --header <int>`         Defines explicit header 1/0 (true/false), default value 1 (true).
- `-r  --data-rate <int>`      Low data rate optimization 1/0 (true/false)
- `-p  --preamble <int>`       Preamble symbol is defined for all regions in LoRaWAN 1.0 standard is 8, this is a default value.
- `-d  --dutycycle <double>`   Defines time between packet subsequence starts, default value dutycycle is 0.10. Dutycycle is expressed as a percentage.


### Common TRAP parameters
- `-h [trap,1]`      Print help message for this module / for libtrap specific parameters.
- `-i IFC_SPEC`      Specification of interface types and their parameters.
- `-v`               Be verbose.
- `-vv`              Be more verbose.
- `-vvv`             Be even more verbose.
