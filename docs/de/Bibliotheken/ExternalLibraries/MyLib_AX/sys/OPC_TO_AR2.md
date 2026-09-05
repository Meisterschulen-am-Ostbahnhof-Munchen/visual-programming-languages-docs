# OPC_TO_AR2

![OPC_TO_AR2_network](./OPC_TO_AR2_network.svg)

* * * * * * * * * *

## Einleitung

`OPC_TO_AR2` ist der reine OPC-UA-Zwilling von [`NumericValue_TO_AR2`](./NumericValue_TO_AR2.md) - kein VT-Eingabefeld beteiligt. Ein remote geschriebener Wert wird per `AR_SUBSCRIBE_1` abonniert und als AR2-Adapter (`VALUEO`) an einen Consumer weitergereicht (z. B. `CALIBRATE.ZERO`/`.SPAN`). Was der Consumer zurueckechot (aktueller/persistierter Wert) wird per `AR_PUBLISH_1` auf dieselbe Remote-Adresse zurueckgemeldet.

## Technische Besonderheiten

- `AR_PUBLISH_1` wird von `AR_SUBSCRIBE_1.INITO` getriggert, damit der Boot-Wert sofort publiziert wird, nicht erst bei der ersten Aenderung.

## Zusammenfassung

Rein remote (OPC-UA) betriebene AR2-Bruecke ohne jeden VT-Bezug - fuer Consumer, die ausschliesslich per Leitwarte parametriert werden.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
